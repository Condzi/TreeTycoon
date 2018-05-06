/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "Debug.hpp"

namespace con::priv
{
class GameClass final :
	public ILogger
{
public:
	void run();

private:
	bool loadSettings();
	bool validateSettings();
	void makeDefaultSettings();
	void configureFromSettings();

	std::string loggerName() const override
	{
		return "Game";
	}
};
}

namespace con
{
extern priv::GameClass Game;
extern sf::Time FrameTime;
extern bool ExitGame;
}