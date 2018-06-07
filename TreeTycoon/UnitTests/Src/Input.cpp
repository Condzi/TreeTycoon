/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Catch.hpp"

#include <Input.hpp>

TEST_CASE( "Input", "[Input]" )
{
	REQUIRE_FALSE( con::Global.Input.isUp( con::KeyboardKey::A ) );
	REQUIRE_FALSE( con::Global.Input.isUp( con::MouseButton::Left ) );
	REQUIRE_FALSE( con::Global.Input.isDown( con::KeyboardKey::B ) );
	REQUIRE_FALSE( con::Global.Input.isDown( con::MouseButton::Right ) );
}