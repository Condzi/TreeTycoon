/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Catch.hpp"

#include <Input.hpp>

TEST_CASE( "Input", "[Input]" )
{
	sf::Event upKey, downKey, upButton, downButton;
	upKey.type = sf::Event::EventType::KeyReleased;
	upKey.key.code = con::KeyboardKey::A;
	downKey.type = sf::Event::EventType::KeyPressed;
	downKey.key.code = con::KeyboardKey::B;

	upButton.type = sf::Event::EventType::MouseButtonReleased;
	upButton.mouseButton.button = con::MouseButton::Left;
	downButton.type = sf::Event::EventType::MouseButtonPressed;
	downButton.mouseButton.button = con::MouseButton::Right;

	REQUIRE_FALSE( con::Global.Input.isUp( con::KeyboardKey::A ) );
	REQUIRE_FALSE( con::Global.Input.isUp( con::MouseButton::Left ) );
	REQUIRE_FALSE( con::Global.Input.isDown( con::KeyboardKey::B ) );
	REQUIRE_FALSE( con::Global.Input.isDown( con::MouseButton::Right ) );

	con::Global.Input._dispatchEvent( upKey );
	con::Global.Input._dispatchEvent( downKey );
	con::Global.Input._dispatchEvent( upButton );
	con::Global.Input._dispatchEvent( downButton );

	REQUIRE( con::Global.Input.isUp( con::KeyboardKey::A ) );
	REQUIRE( con::Global.Input.isUp( con::MouseButton::Left ) );
	REQUIRE( con::Global.Input.isDown( con::KeyboardKey::B ) );
	REQUIRE( con::Global.Input.isDown( con::MouseButton::Right ) );

	con::Global.Input._clearStates();

	REQUIRE_FALSE( con::Global.Input.isUp( con::KeyboardKey::A ) );
	REQUIRE_FALSE( con::Global.Input.isUp( con::MouseButton::Left ) );
	REQUIRE_FALSE( con::Global.Input.isDown( con::KeyboardKey::B ) );
	REQUIRE_FALSE( con::Global.Input.isDown( con::MouseButton::Right ) );
}