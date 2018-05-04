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

	REQUIRE_FALSE( con::Input.isUp( con::KeyboardKey::A ) );
	REQUIRE_FALSE( con::Input.isUp( con::MouseButton::Left ) );
	REQUIRE_FALSE( con::Input.isDown( con::KeyboardKey::B ) );
	REQUIRE_FALSE( con::Input.isDown( con::MouseButton::Right ) );

	con::Input._dispatchEvent( upKey );
	con::Input._dispatchEvent( downKey );
	con::Input._dispatchEvent( upButton );
	con::Input._dispatchEvent( downButton );

	REQUIRE( con::Input.isUp( con::KeyboardKey::A ) );
	REQUIRE( con::Input.isUp( con::MouseButton::Left ) );
	REQUIRE( con::Input.isDown( con::KeyboardKey::B ) );
	REQUIRE( con::Input.isDown( con::MouseButton::Right ) );

	con::Input._clearStates();

	REQUIRE_FALSE( con::Input.isUp( con::KeyboardKey::A ) );
	REQUIRE_FALSE( con::Input.isUp( con::MouseButton::Left ) );
	REQUIRE_FALSE( con::Input.isDown( con::KeyboardKey::B ) );
	REQUIRE_FALSE( con::Input.isDown( con::MouseButton::Right ) );
}