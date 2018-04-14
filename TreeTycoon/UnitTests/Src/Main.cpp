/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#define CATCH_CONFIG_RUNNER
#include "Catch.hpp"

// Definig own main because console closes immediately after tests.
int main( int argc, char* argv[] )
{
	auto result = Catch::Session().run( argc, argv );

	std::cin.get();

	return result;
}