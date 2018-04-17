/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include <filesystem>

#include "Catch.hpp"

#include <Assets.hpp>
#include <INIFile.hpp>

TEST_CASE( "INI File Reader", "[Assets]" )
{
	{
		con::INIReader ini;
		ini.setValue( "SECTION_A", "name1", "val1" );
		ini.setValue( "SECTION_A", "name2", "val2" );

		ini.setValue( "SECTION_B", "name1", "val1" );
		ini.setValue( "SECTION_B", "name2", "val2" );

		ini.save( "test.ini" );
	}

	{
		con::INIReader ini;
		REQUIRE( ini.load( "test.ini" ) == true );
		REQUIRE( ini.getValue( "SECTION_A", "name1" ).has_value() );
		REQUIRE( ini.getValue( "SECTION_A", "name1" ).value_or( "(err)" ) == "val1" );
		REQUIRE( ini.getValue( "SECTION_A", "name2" ).has_value() );
		REQUIRE( ini.getValue( "SECTION_A", "name2" ).value_or( "(err)" ) == "val2" );

		REQUIRE( ini.getValue( "SECTION_B", "name1" ).has_value() );
		REQUIRE( ini.getValue( "SECTION_B", "name1" ).value_or( "(err)" ) == "val1" );
		REQUIRE( ini.getValue( "SECTION_B", "name2" ).has_value() );
		REQUIRE( ini.getValue( "SECTION_B", "name2" ).value_or( "(err)" ) == "val2" );
	}
	std::experimental::filesystem::remove( "test.ini" );
}