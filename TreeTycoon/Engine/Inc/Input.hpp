/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "IUpdatable.hpp"

namespace con
{
using KeyboardKey = sf::Keyboard::Key;
using MouseButton = sf::Mouse::Button;
}

namespace con::priv
{
class InputClass final
{
	enum class KeyState : int8_t
	{
		None,
		Up,
		Down
	};

public:
	bool isUp( KeyboardKey key ) const;
	bool isDown( KeyboardKey key ) const;
	bool isHeld( KeyboardKey key ) const;

	bool isUp( MouseButton button ) const;
	bool isDown( MouseButton button ) const;
	bool isHeld( MouseButton button ) const;

	Vec2i getMousePosition() const;

	void _dispatchEvents();

private:
	std::array<KeyState, KeyboardKey::KeyCount> keyboardKeys{ KeyState::None };
	std::array<KeyState, MouseButton::ButtonCount> mouseButtons{ KeyState::None };

	void clearStates();
};
}