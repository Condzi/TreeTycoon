/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include <filesystem>
// for sleep
#include <thread>

#include "Catch.hpp"

#include <Assets.hpp>
#include <INIFile.hpp>

TEST_CASE( "INI File Reader (aka Settings)", "[Assets]" )
{
	static constexpr const char* TEST_INI_PATH = "Data/test.ini";

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
	static constexpr const char* TEST_IMG_PATH = "Data/test.png";

	{
		sf::Image testImg;
		testImg.create( 32, 32, sf::Color::Green );
		testImg.saveToFile( TEST_IMG_PATH );
	}

	auto& texture = con::Assets.Texture;

	{
		REQUIRE( texture.load( TEST_IMG_PATH, "test" ) == true );
		// green vs red
		REQUIRE( texture.get( "test" ).copyToImage().getPixel( 0, 0 ) != texture.getDefault().copyToImage().getPixel( 0, 0 ) );
	}

	std::experimental::filesystem::remove( TEST_IMG_PATH );
}

TEST_CASE( "IAudioHolder (sf::Sound)", "[Assets]" )
{
	static constexpr const char* TEST_SOUND_PATH = "Data/test.wav";

	auto& sound = con::Assets.Sound;

	REQUIRE( sound.load( TEST_SOUND_PATH, "test" ) == true );
	sound.setVolume( 50 );
	sound.play( "test" );
	std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
	sound.setVolume( 10 );
	sound.play( "test" );
	std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
	sound.setVolume( 100 );
	sound.play( "test" );
}
