/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "EnginePCH.hpp"

#include "INIFile.hpp"

namespace con
{
bool INIFile::load( const std::string& path )
{
	pathToFile = path;
	std::ifstream file( pathToFile );

	if ( !file ) {
		log( LogPriority::Error, "can't open file." );
		return false;
	}

	std::vector<std::string> rawData;
	std::string line;
	while ( !file.eof() ) {
		std::getline( file, line );
		if ( line.empty() )
			continue;

		rawData.emplace_back( line );
	}

	parse( rawData );

	return true;
}

void INIFile::save( const std::string& path )
{
	std::vector<std::string> serializeData;
	serialize( serializeData );

	if ( !path.empty() )
		this->pathToFile = path;

	std::ofstream file( this->pathToFile );
	std::copy( serializeData.begin(), serializeData.end(), std::ostream_iterator<std::string>( file, "\n" ) );
}

void INIFile::clear()
{
	sections.clear();
}

std::vector<std::string> INIFile::getAllSectionsNames() const
{
	std::vector<std::string> vec;
	vec.reserve( sections.size() );

	for ( auto& section : sections )
		vec.emplace_back( section.first );

	return vec;
}

std::optional<std::string> INIFile::getValue( const std::string& section, const std::string& name )
{
	if ( auto sectionsIt = sections.find( section ); sectionsIt != sections.cend() ) {
		auto vec = sectionsIt->second;
		auto vecIt = std::find_if( vec.begin(), vec.end(), [&name]( auto& pair ) {
			return pair.name == name;
		} );

		if ( vecIt != vec.end() )
			return vecIt->value;
		else
			log( LogPriority::Error, "can't find \"", name, "\" in \"", section, "\" section." );
	} else {
		log( LogPriority::Error, "can't find \"", section, "\" section." );
	}
	return {};
}

void INIFile::setValue( const std::string& section, const std::string& name, const std::string& value )
{
	sections[section].emplace_back( NameValuePair{ name, value } );
}

void INIFile::parse( const std::vector<std::string>& data )
{
	clear();
	std::string section{};

	for ( auto line : data ) {
		if ( isComment( line ) )
			continue;

		removeEmptyFrontSpace( line );
		removeEmptyBackSpace( line );

		if ( isSection( line ) ) {
			if ( auto sec = parseSection( line ); sec.has_value() )
				section = sec.value();
		} else
			sections[section].emplace_back( parseAsNameValuePair( line ) );
	}
}

bool INIFile::isComment( std::string& line )
{
	return line.front() == ';';
}

void INIFile::removeEmptyFrontSpace( std::string& str )
{
	while ( isSpaceOrTab( str.front() ) )
		str.erase( str.begin() );
}

void INIFile::removeEmptyBackSpace( std::string& str )
{
	while ( isSpaceOrTab( str.back() ) )
		str.pop_back();
}

bool INIFile::isSpaceOrTab( char c ) const
{
	return c == ' ' || c == '\t';
}

bool INIFile::isSection( std::string& line )
{
	return line.find_first_of( '=' ) == std::string::npos;
}

std::optional<std::string> INIFile::parseSection( std::string& line )
{
	if ( !( line.front() == '[' && line.back() == ']' ) ) {
		log( LogPriority::Error, "missing bracket." );
		return {};
	}

	return line.substr( 1, line.size() - 2 );
}

INIFile::NameValuePair INIFile::parseAsNameValuePair( std::string& line )
{
	NameValuePair pair;
	auto& name = pair.name;
	auto& value = pair.value;
	name = line.substr( 0, line.find_first_of( '=' ) );
	value = line.substr( line.find_first_of( '=' ) + 1 );

	removeEmptyBackSpace( name );
	removeEmptyFrontSpace( value );

	return pair;
}

void INIFile::serialize( std::vector<std::string>& target )
{
	target.clear();

	for ( auto& it : sections ) {
		target.emplace_back( ConvertTo<std::string>( "[", it.first, "]" ) );

		for ( auto& pair : it.second )
			target.emplace_back( ConvertTo<std::string>( pair.name, " = ", pair.value ) );

		target.emplace_back( "\n" );
	}
}
}