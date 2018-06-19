/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "GamePCH.hpp"

#include "TreeInfosStorage.hpp"

void TreeInfosStorage::load()
{
	if ( loadConfig() )
		loadTextures();
}

std::optional<const TreeInfo* const> TreeInfosStorage::findTreeInfo( const std::string& name )
{
	return findTreeInfo( std::hash<std::string>{}( name ) );
}

std::optional<const TreeInfo* const> TreeInfosStorage::findTreeInfo( size_t hash )
{
	auto result = std::find_if( infos.begin(), infos.end(), [&]( TreeInfo& info ) {
		return info.nameHash == hash;
	} );

	if ( result == infos.end() ) {
		log( con::LogPriority::Error, "Missing TreeInfo." );
		DebugBreak();
		return {};
	}

	return &( *result );
}

std::vector<const TreeInfo*> TreeInfosStorage::getAllTreeInfos()
{
	std::vector<const TreeInfo*> vec;

	for ( auto& info : infos )
		vec.emplace_back( &info );

	return vec;
}

bool TreeInfosStorage::loadConfig()
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
	if ( !ini.load( constants::TREES_CONFIG_PATH ) )
		return false;

	auto treeNames = ini.getAllSectionsNames();
	infos.reserve( treeNames.size() );

	log( con::LogPriority::Info, "Begin loading trees data..." );

	std::hash<std::string> hashingFunction;

	for ( auto& treeName : treeNames ) {
		auto& info = infos.emplace_back();

		auto getValue = [&]( const char* name ) {
			return ini.getValue( treeName, name );
		};

		info.name = getValue( "NAME" ).value_or( "missing" );
		info.nameHash = hashingFunction( info.name );
		info.texturePath = getValue( "TEXTURE_PATH" ).value_or( "missing" );
		info.type = getValue( "TYPE" ).value_or( "missing" );
		info.fruitType = getValue( "FRUIT_TYPE" ).value_or( "missing" );
		info.seedPrice = con::ConvertTo<int16_t>( getValue( "SEED_PRICE" ).value_or( "-1" ) );
		info.maxHeight = con::ConvertTo<int16_t>( getValue( "MAX_HEIGHT" ).value_or( "-1" ) );
		info.growingSpeed = con::ConvertTo<float32_t>( getValue( "GROWING_SPEED" ).value_or( "-1" ) );

		info.textureName = con::ConvertTo<std::string>( "tree_", info.name, "_", info.type );

		log( con::LogPriority::Info, "=====" );
		log( con::LogPriority::Info, "name = ", info.name );
		log( con::LogPriority::Info, "texturePath = ", info.texturePath );
		log( con::LogPriority::Info, "type = ", info.type );
		log( con::LogPriority::Info, "fruitType = ", info.fruitType );
		log( con::LogPriority::Info, "seedPrice = ", info.seedPrice );
		log( con::LogPriority::Info, "maxHeight = ", info.maxHeight );
		log( con::LogPriority::Info, "growingSpeed = ", info.growingSpeed );
		log( con::LogPriority::Info, "textureName = ", info.textureName );
	}

	log( con::LogPriority::Info, "Loading trees data ended. (", infos.size(), " trees loaded)" );

	return true;
}

void TreeInfosStorage::loadTextures()
{
	for ( auto& info : infos )
		con::Global.Assets.Texture.load( info.texturePath, info.textureName );
}
