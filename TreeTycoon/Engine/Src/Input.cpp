/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "EnginePCH.hpp"

#include "Input.hpp"

#include "GUI.hpp"

namespace con::priv
{
bool InputClass::isUp( KeyboardKey key ) const
{
	return keyboardKeys.at( ConvertTo<uint8_t>( key ) ) == KeyState::Up;
}

bool InputClass::isDown( KeyboardKey key ) const
{
	return keyboardKeys.at( ConvertTo<uint8_t>( key ) ) == KeyState::Down;
}

bool InputClass::isHeld( KeyboardKey key ) const
{
	return sf::Keyboard::isKeyPressed( key ) && Global.GameWindow.hasFocus();
}

bool InputClass::isUp( MouseButton button ) const
{
	return mouseButtons.at( ConvertTo<uint8_t>( button ) ) == KeyState::Up;
}

bool InputClass::isDown( MouseButton button ) const
{
	return mouseButtons.at( ConvertTo<uint8_t>( button ) ) == KeyState::Down;
}

bool InputClass::isHeld( MouseButton button ) const
{
	return sf::Mouse::isButtonPressed( button ) && Global.GameWindow.hasFocus();
}

Vec2i InputClass::getMousePosition() const
{
	return sf::Mouse::getPosition( Global.GameWindow );
}

void InputClass::_dispatchEvents()
{
	using EventType = sf::Event::EventType;
	static auto keyToInt = []( auto key ) {
		return ConvertTo<uint8_t>( key );
	};

	clearStates();

	sf::Event event;
	while ( Global.GameWindow.pollEvent( event ) ) {
		if ( event.type == EventType::Closed )
			Global.ExitGame = true;
		else if ( event.type == EventType::KeyReleased )
			keyboardKeys.at( keyToInt( event.key.code ) ) = KeyState::Up;
		else if ( event.type == EventType::KeyPressed )
			keyboardKeys.at( keyToInt( event.key.code ) ) = KeyState::Down;
		else if ( event.type == EventType::MouseButtonReleased )
			mouseButtons.at( keyToInt( event.mouseButton.button ) ) = KeyState::Up;
		else if ( event.type == EventType::MouseButtonPressed )
			mouseButtons.at( keyToInt( event.mouseButton.button ) ) = KeyState::Down;
		else if ( event.type == EventType::Resized ) {
			auto width = ConvertTo<float32_t>( event.size.width );
			auto height = ConvertTo<float32_t>( event.size.height );

			sf::View updatedView( RectF( 0, 0, width, height ) );
			Global.GameWindow.setView( updatedView );
			Global.GUI.setView( updatedView );
		}

		Global.GUI.handleEvent( event );
	}
}

void InputClass::clearStates()
{
	keyboardKeys.fill( KeyState::None );
	mouseButtons.fill( KeyState::None );
}
}