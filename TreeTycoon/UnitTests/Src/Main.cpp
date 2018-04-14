/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#define CATCH_CONFIG_RUNNER
#include "Catch.hpp"

int square( int val )
{
	return val * 2; // obvious error.
}

TEST_CASE( "Square of '2' (pass)", "[single-file]" )
{
	REQUIRE( square( 2 ) == 4 );
}

TEST_CASE( "Square of '3' (fail)", "[single-file]" )
{
	REQUIRE( square( 3 ) == 9 );
}

// Definig own main because console closes immidietly after tests.
int main( int argc, char* argv[] )
{
	auto result = Catch::Session().run( argc, argv );

	std::cin.get();

	return result;
}