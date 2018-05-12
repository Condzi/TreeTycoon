/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Catch.hpp"

#include "Window.hpp"

using namespace con;

TEST_CASE( "GameWindowClass", "[Visual]" )
{
	priv::GameWindowClass window;
	window._create( { 200,200 }, 0 );

	REQUIRE( window._getSFMLWindow().getSize().x == 200 );
	REQUIRE( window._getSFMLWindow().getSize().y == 200 );


	SECTION( "Pixel to absolute" )
	{
		auto a = window.convertPixelToAbsolute( { 200,200 } );
		auto b = window.convertPixelToAbsolute( { 0,0 } );

		REQUIRE( a.x == 1 );
		REQUIRE( a.y == 1 );

		REQUIRE( b.x == 0 );
		REQUIRE( b.y == 0 );

	}

	SECTION( "Absolute to pixel" )
	{
		auto a = window.convertAbsoluteToPixel( { 1,1 } );
		auto b = window.convertAbsoluteToPixel( { 0,0 } );

		REQUIRE( a.x == 200 );
		REQUIRE( a.y == 200 );

		REQUIRE( b.x == 0 );
		REQUIRE( b.y == 0 );
	}
}