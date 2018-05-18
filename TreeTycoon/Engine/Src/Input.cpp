/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "EnginePCH.hpp"

#include "Input.hpp"
#include "Window.hpp"

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
	return sf::Mouse::getPosition( Global.GameWindow._getSFMLWindow() );
}

void InputClass::setAdditionalEventDispatcher( const std::function<void( sf::Event )>& aed )
{
	additionalEventDispatcher = aed;
}

void InputClass::resetAdditionalEventDispatcher()
{
	additionalEventDispatcher = decltype( additionalEventDispatcher ){};
}

void InputClass::_dispatchEvent( sf::Event event )
{
	using EventType = sf::Event::EventType;
	static auto keyToInt = []( auto key ) {
		return ConvertTo<uint8_t>( key );
	};

	if ( event.type == EventType::KeyReleased )
		keyboardKeys.at( keyToInt( event.key.code ) ) = KeyState::Up;
	else if ( event.type == EventType::KeyPressed )
		keyboardKeys.at( keyToInt( event.key.code ) ) = KeyState::Down;
	else if ( event.type == EventType::MouseButtonReleased )
		mouseButtons.at( keyToInt( event.mouseButton.button ) ) = KeyState::Up;
	else if ( event.type == EventType::MouseButtonPressed )
		mouseButtons.at( keyToInt( event.mouseButton.button ) ) = KeyState::Down;

	additionalEventDispatcher( event );
}

void InputClass::_clearStates()
{
	keyboardKeys.fill( KeyState::None );
	mouseButtons.fill( KeyState::None );
}
}