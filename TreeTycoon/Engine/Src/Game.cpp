/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "EnginePCH.hpp"

#include "Game.hpp"
#include "Updater.hpp"
#include "Input.hpp"
#include "Assets.hpp"

namespace con::priv
{
void GameClass::run()
{
	if ( !loadSettings() || !validateSettings() )
		makeDefaultSettings();

	configureFromSettings();

	sf::Clock fpsClock;
	while ( !Global.ExitGame ) {
		Global.Input._dispatchEvents();
		Global._Updater.update();

		Global.FrameTime = fpsClock.restart();
	}
}

bool GameClass::loadSettings()
{
	return Global.Assets.Settings.load( "settings.ini" );
}

bool GameClass::validateSettings()
{
	auto& settings = Global.Assets.Settings;

	if ( !settings.getValue( "WINDOW", "WIDTH" ).has_value() )
		log( LogPriority::Error, "Missing WINDOW WIDTH setting." );
	else if ( !settings.getValue( "WINDOW", "HEIGHT" ).has_value() )
		log( LogPriority::Error, "Missing WINDOW HEIGHT setting." );
	else if ( !settings.getValue( "WINDOW", "FPS" ).has_value() )
		log( LogPriority::Error, "Missing WINDOW FPS setting." );
	else
		return true;

	return false;
}

void GameClass::makeDefaultSettings()
{
	auto& settings = Global.Assets.Settings;

	settings.setValue( "WINDOW", "WIDTH", "1280" );
	settings.setValue( "WINDOW", "HEIGHT", "720" );
	settings.setValue( "WINDOW", "FPS", "60" );
}

void GameClass::configureFromSettings()
{
	auto& settings = Global.Assets.Settings;

	auto winWidth = ConvertTo<uint32_t>( settings.getValue( "WINDOW", "WIDTH" ).value() );
	auto winHeight = ConvertTo<uint32_t>( settings.getValue( "WINDOW", "HEIGHT" ).value() );
	auto fps = ConvertTo<uint32_t>( settings.getValue( "WINDOW", "FPS" ).value() );

	Global.GameWindow.create( { winWidth, winHeight }, "game" );
	Global.GameWindow.setFramerateLimit( fps );
}
}