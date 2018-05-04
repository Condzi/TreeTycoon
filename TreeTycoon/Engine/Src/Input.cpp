/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "EnginePCH.hpp"

#include "Input.hpp"

namespace con
{
inline priv::InputClass Input{};
}

namespace con::priv
{
bool InputClass::isUp( KeyboardKey key ) const
{
	return keyboardKeys[ConvertTo<uint8_t>( key )] == KeyState::Up;
}

bool InputClass::isDown( KeyboardKey key ) const
{
	return keyboardKeys[ConvertTo<uint8_t>( key )] == KeyState::Down;
}

bool InputClass::isHeld( KeyboardKey key ) const
{
	return sf::Keyboard::isKeyPressed( key );
}

bool InputClass::isUp( MouseButton button ) const
{
	return mouseButtons[ConvertTo<uint8_t>( button )] == KeyState::Up;
}

bool InputClass::isDown( MouseButton button ) const
{
	return mouseButtons[ConvertTo<uint8_t>( button )] == KeyState::Down;
}

bool InputClass::isHeld( MouseButton button ) const
{
	return sf::Mouse::isButtonPressed( button );
}

Vec2i InputClass::getMousePosition() const
{
	// Use Window.getSFMLWindow().
	throw std::exception{ "not implemented" };
	return {};
}

void InputClass::_dispatchEvent( const sf::Event& event )
{
	using EventType = sf::Event::EventType;
	static auto keyToInt = []( auto key ) {
		return ConvertTo<uint8_t>( key );
	};

	if ( event.type == EventType::KeyReleased )
		keyboardKeys[keyToInt( event.key.code )] = KeyState::Up;
	else if ( event.type == EventType::KeyPressed )
		keyboardKeys[keyToInt( event.key.code )] = KeyState::Down;
	else if ( event.type == EventType::MouseButtonReleased )
		mouseButtons[keyToInt( event.mouseButton.button )] = KeyState::Up;
	else if ( event.type == EventType::MouseButtonPressed )
		mouseButtons[keyToInt( event.mouseButton.button )] = KeyState::Down;
}

void InputClass::_clearStates()
{
	keyboardKeys.fill( KeyState::None );
	mouseButtons.fill( KeyState::None );
}
}