/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "INIFile.hpp"

namespace con::priv
{
class SettingsClass final
{
public:
	~SettingsClass()
	{
		iniFile.save();
	}
	
	bool _load( const std::string& path )
	{
		return iniFile.load( path );
	}

	std::optional<std::string> get( const std::string& section, const std::string& name )
	{
		return iniFile.getValue( section, name );
	}
	void set( const std::string& section, const std::string& name, const std::string& value )
	{
		iniFile.setValue( section, name, value );
	}

private:
	INIReader iniFile;
};
}