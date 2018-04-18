/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "EnginePCH.hpp"
#include "Debug.hpp"

namespace con::priv
{
template <typename TAsset>
class BasicAssetHolder :
	public ILogger
{
public:
	bool load( const std::string& path, const std::string& name )
	{
		if ( TAsset asset; asset.loadFromFile( path ) ) {
			assets[name] = std::move( asset );
			return true;
		}
		else {
			log( LogPriority::Error, "can't load \"", name, "\" from \"", path, "\"." );
			return false;
		}
	}

	const TAsset& get( const std::string& name )
	{
		if ( auto it = assets.find( name ); it != assets.end() )
			return it->second;
		else {
			log( LogPriority::Warning, "can't find \"", name, "\"." );
			return default;
		}
	}

	void _setDefault( TAsset&& asset )
	{
		default = std::move( asset );
	}

	const TAsset& getDefault() const
	{
		return default;
	}

private:
	TAsset default;
	std::unordered_map<std::string, TAsset> assets;
};

class TextureHolder final :
	public BasicAssetHolder<sf::Texture>
{
private:
	std::string loggerName() const override
	{
		return "Texture Holder";
	}
};

class FontHolder final :
	public BasicAssetHolder<sf::Font>
{
private:
	std::string loggerName() const override
	{
		return "Font Holder";
	}
};
}