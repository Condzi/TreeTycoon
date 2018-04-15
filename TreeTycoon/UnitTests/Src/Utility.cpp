/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Catch.hpp"

#include <Utility.hpp>

TEST_CASE( "Type Conversions", "[Utility]" )
{
	int8_t int8Val = 1;
	uint8_t uint8Val = 2;
	int16_t int16Val = 3;
	uint16_t uint16Val = 4;
	int32_t int32Val = 5;
	uint32_t uint32Val = 6;
	int64_t int64Val = 7;
	uint64_t uint64Val = 8;
	float32_t float32Val = 9.5f;
	float64_t float64Val = 10.55;
	bool boolVal = false;

	std::string int8str = "1";
	std::string uint8str = "2";
	std::string int16str = "3";
	std::string uint16str = "4";
	std::string int32str = "5";
	std::string uint32str = "6";
	std::string int64str = "7";
	std::string uint64str = "8";
	std::string float32str = "9.5";
	std::string float64str = "10.55";
	std::string boolstr = "false";

	SECTION( "Convering from number to string" )
	{
		REQUIRE( con::ConvertTo<std::string>( int8Val ) == int8str );
		REQUIRE( con::ConvertTo<std::string>( uint8Val ) == uint8str );
		REQUIRE( con::ConvertTo<std::string>( int16Val ) == int16str );
		REQUIRE( con::ConvertTo<std::string>( uint16Val ) == uint16str );
		REQUIRE( con::ConvertTo<std::string>( int32Val ) == int32str );
		REQUIRE( con::ConvertTo<std::string>( uint32Val ) == uint32str );
		REQUIRE( con::ConvertTo<std::string>( int64Val ) == int64str );
		REQUIRE( con::ConvertTo<std::string>( uint64Val ) == uint64str );
		REQUIRE( con::ConvertTo<std::string>( float32Val ) == float32str );
		REQUIRE( con::ConvertTo<std::string>( float64Val ) == float64str );
		REQUIRE( con::ConvertTo<std::string>( boolVal ) == boolstr );
	}

	SECTION( "Convering from string to number" )
	{
		REQUIRE( con::ConvertTo<int8_t>( int8str ) == int8Val );
		REQUIRE( con::ConvertTo<uint8_t>( uint8str ) == uint8Val );
		REQUIRE( con::ConvertTo<int8_t>( int16str ) == int16Val );
		REQUIRE( con::ConvertTo<uint8_t>( uint16str ) == uint16Val );
		REQUIRE( con::ConvertTo<int8_t>( int32str ) == int32Val );
		REQUIRE( con::ConvertTo<uint8_t>( uint32str ) == uint32Val );
		REQUIRE( con::ConvertTo<int8_t>( int64str ) == int64Val );
		REQUIRE( con::ConvertTo<uint8_t>( uint64str ) == uint64Val );
		REQUIRE( con::ConvertTo<float32_t>( float32str ) == float32Val );
		REQUIRE( con::ConvertTo<float64_t>( float64str ) == float64Val );
		REQUIRE( con::ConvertTo<bool>( boolstr ) == boolVal );
	}

	SECTION( "Converting multiple arguments to string" )
	{
		std::string str = ". :)";
		REQUIRE( con::ConvertTo<std::string>( "Something = ", 123, str ) == std::string( "Something = 123. :)" ) );
	}
}

TEST_CASE( "Random Number Generator", "[Utility]" )
{
	SECTION( "int, int" )
	{
		REQUIRE_NOTHROW( con::Random( 1, 2 ) );
		REQUIRE_THROWS( con::Random( 2, 1 ) );
	}

	SECTION( "float, int" )
	{
		REQUIRE_NOTHROW( con::Random( 1.0f, 2 ) );
		REQUIRE_THROWS( con::Random( 2.0f, 1 ) );
	}

	SECTION( "double, int" )
	{
		REQUIRE_NOTHROW( con::Random( 1.0, 2 ) );
		REQUIRE_THROWS( con::Random( 2.0, 1 ) );
	}
}