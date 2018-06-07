/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "Debug.hpp"

namespace con
{
class INIFile :
	public ILogger
{
public:
	bool load( const std::string& path );
	// If empty then saves to path from which was opened before
	void save( const std::string& path = "" );
	void clear();

	std::vector<std::string> getAllSectionsNames() const;
	std::optional<std::string> getValue( const std::string& section, const std::string& name );
	void setValue( const std::string& section, const std::string& name, const std::string& value );

private:
	struct NameValuePair final
	{
		std::string name{}, value{};
	};

	std::string pathToFile{};
	std::map<std::string, std::vector<NameValuePair>> sections;

	void parse( const std::vector<std::string>& data );
	bool isComment( std::string& line );
	void removeEmptyFrontSpace( std::string& str );
	void removeEmptyBackSpace( std::string& str );
	bool isSpaceOrTab( char c ) const;
	bool isSection( std::string& line );
	std::optional<std::string> parseSection( std::string& line );
	NameValuePair parseAsNameValuePair( std::string& line );

	void serialize( std::vector<std::string>& target );

	std::string loggerName() const override
	{
		return ConvertTo<std::string>( "INI(", pathToFile, ")" );
	}
};
}
