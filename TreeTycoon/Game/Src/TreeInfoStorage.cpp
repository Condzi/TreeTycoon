/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "GamePCH.hpp"

#include "TreeInfoStorage.hpp"

void TreeInfoStorage::load()
{
	if ( !loadConfig() )
		return;

	loadTextures();
}

std::optional<const TreeInfo const*> TreeInfoStorage::findTree( const std::string& name )
{
	auto result = std::find_if( infos.begin(), infos.end(), [&]( TreeInfo& info ) {
		return info.name == name;
	} );

	if ( result == infos.end() ) {
		log( con::LogPriority::Error, "Couldn't find \"", name, "\"." );
		return {};
	}

	return &( *result );
}

bool TreeInfoStorage::loadConfig()
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
	if ( !ini.load( constants::TREE_CONFIG_PATH ) )
		return false;

	auto treeNames = ini.getAllSectionsNames();

	log( con::LogPriority::Info, "Begin loading tree data..." );

	for ( auto& treeName : treeNames ) {
		auto& info = infos.emplace_back();

		auto getValue = [&]( const char* name ) {
			return ini.getValue( treeName, name );
		};

		info.name = getValue( "NAME" ).value_or( "missing" );
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

	log( con::LogPriority::Info, "Loading tree data ended. (", infos.size(), " trees loaded)" );

	return true;
}

void TreeInfoStorage::loadTextures()
{
	for ( auto& info : infos )
		con::Global.Assets.Texture.load( info.texturePath, info.textureName );
}
