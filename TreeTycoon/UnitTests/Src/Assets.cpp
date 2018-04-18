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
	static constexpr const char* TEST_INI_PATH = "test.ini";

	{
		con::INIReader ini;
		ini.setValue( "SECTION_A", "name1", "val1" );
		ini.setValue( "SECTION_A", "name2", "val2" );

		ini.setValue( "SECTION_B", "name1", "val1" );
		ini.setValue( "SECTION_B", "name2", "val2" );

		ini.save( TEST_INI_PATH );
	}

	{
		con::INIReader ini;
		REQUIRE( ini.load( TEST_INI_PATH ) == true );
		REQUIRE( ini.getValue( "SECTION_A", "name1" ).has_value() );
		REQUIRE( ini.getValue( "SECTION_A", "name1" ).value_or( "(err)" ) == "val1" );
		REQUIRE( ini.getValue( "SECTION_A", "name2" ).has_value() );
		REQUIRE( ini.getValue( "SECTION_A", "name2" ).value_or( "(err)" ) == "val2" );

		REQUIRE( ini.getValue( "SECTION_B", "name1" ).has_value() );
		REQUIRE( ini.getValue( "SECTION_B", "name1" ).value_or( "(err)" ) == "val1" );
		REQUIRE( ini.getValue( "SECTION_B", "name2" ).has_value() );
		REQUIRE( ini.getValue( "SECTION_B", "name2" ).value_or( "(err)" ) == "val2" );
	}

	std::experimental::filesystem::remove( TEST_INI_PATH );
}


TEST_CASE( "Basic Asset Holder (sf::Texture)", "[Assets]" )
{
	static constexpr const char* TEST_IMG_PATH = "test.png";

	{
		sf::Image testImg;
		testImg.create( 32, 32, sf::Color::Green );
		testImg.saveToFile( TEST_IMG_PATH );
	}

	{
		REQUIRE( con::Assets.Texture.load( TEST_IMG_PATH, "test" ) == true );
		// green vs red
		REQUIRE( con::Assets.Texture.get( "test" ).copyToImage().getPixel( 0, 0 ) != con::Assets.Texture.getDefault().copyToImage().getPixel( 0, 0 ) );
	}

	std::experimental::filesystem::remove( TEST_IMG_PATH );
}

