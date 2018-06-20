/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "GamePCH.hpp"

#include "PlotsStorage.hpp"

PlotsStorage::PlotsStorage( World& world_ ) :
	world( world_ )
{}

void PlotsStorage::load()
{
	std::vector<PlotInfo> infos;
	if ( loadConfig( infos ) )
		initializePlots( infos );
}

std::optional<Plot* const> PlotsStorage::findPlot( const std::string& name )
{
	return findPlot( std::hash<std::string>{}( name ) );
}

std::optional<Plot* const> PlotsStorage::findPlot( size_t hash )
{
	auto result = std::find_if( plots.begin(), plots.begin(), [&]( TreeInfo& info ) {
		return info.nameHash == hash;
	} );

	if ( result == plots.end() ) {
		log( con::LogPriority::Error, "Missing Plot." );
		return {};
	}

	return &( *result );
}

std::vector<Plot*> PlotsStorage::getAllPlots()
{
	std::vector<Plot*> vec;

	for ( auto& plot : plots )
		vec.emplace_back( &plot );

	return vec;
}

bool PlotsStorage::loadConfig( std::vector<PlotInfo>& infos )
{
	if constexpr ( con::IS_DEBUG )
	{
		static bool alreadyCalled = false;
		if ( alreadyCalled )
			log( con::LogPriority::Error, "Calling loadConfig() more than once. Dangling pointers may occur." );

		alreadyCalled = true;
	}

	infos.clear();

	con::INIFile ini;
	if ( !ini.load( constants::PLOTS_CONFIG_PATH ) )
		return false;

	auto plotNames = ini.getAllSectionsNames();
	infos.reserve( plotNames.size() );

	log( con::LogPriority::Info, "Begin loading plot data..." );

	std::hash<std::string> hashingFunction;

	for ( auto& plotName : plotNames ) {
		auto& info = infos.emplace_back();

		auto getValue = [&]( const char* name ) {
			return ini.getValue( plotName, name );
		};

		info.name = getValue( "NAME" ).value_or( "missing" );
		info.nameHash = hashingFunction( info.name );
		info.emptyPrice = con::ConvertTo<int16_t>( getValue( "EMPTY_PRICE" ).value_or( "-1" ) );
		info.sizeX = con::ConvertTo<int16_t>( getValue( "SIZE_X" ).value_or( "0" ) );
		info.sizeY = con::ConvertTo<int16_t>( getValue( "SIZE_Y" ).value_or( "0" ) );

		log( con::LogPriority::Info, "=====" );
		log( con::LogPriority::Info, "name = ", info.name );
		log( con::LogPriority::Info, "emptyPrice = ", info.emptyPrice );
		log( con::LogPriority::Info, "sizeX = ", info.sizeX );
		log( con::LogPriority::Info, "sizeY = ", info.sizeY );
	}

	log( con::LogPriority::Info, "Loading plots data ended. (", infos.size(), " plots loaded)" );

	return true;
}

void PlotsStorage::initializePlots( const std::vector<PlotInfo>& infos )
{
	plots.resize( infos.size() );

	con::iteratePararell( plots.begin(), plots.end(), infos.cbegin(), infos.cend(), [&]( Plot& plot, const PlotInfo& info ) {
		plot = Plot( world, info );
	} );
}
