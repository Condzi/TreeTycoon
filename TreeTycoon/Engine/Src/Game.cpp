/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "EnginePCH.hpp"

#include "Game.hpp"
#include "Updater.hpp"
#include "Window.hpp"
#include "Assets.hpp"

namespace con::priv
{
void GameClass::run()
{
	if ( !loadSettings() || !validateSettings() )
		makeDefaultSettings();

	configureFromSettings();

	sf::Clock fpsClock;
	while ( !ExitGame ) {
		GameWindow._pollEvents();
		Updater.update();
		FrameTime = fpsClock.restart();
	}
}

bool GameClass::loadSettings()
{
	return Assets.Settings._load( "settings.ini" );
}

bool GameClass::validateSettings()
{
	auto& settings = Assets.Settings;

	if ( !settings.get( "WINDOW", "WIDTH" ).has_value() )
		log( LogPriority::Error, "Missing WINDOW WIDTH setting." );
	else if ( !settings.get( "WINDOW", "HEIGHT" ).has_value() )
		log( LogPriority::Error, "Missing WINDOW HEIGHT setting." );
	else if ( !settings.get( "WINDOW", "FPS" ).has_value() )
		log( LogPriority::Error, "Missing WINDOW FPS setting." );
	else
		return true;

	return false;
}

void GameClass::makeDefaultSettings()
{
	auto& settings = Assets.Settings;

	settings.set( "WINDOW", "WIDTH", "800" );
	settings.set( "WINDOW", "HEIGHT", "600" );
	settings.set( "WINDOW", "FPS", "60" );
}

void GameClass::configureFromSettings()
{
	auto& settings = Assets.Settings;

	auto winWidth = ConvertTo<uint32_t>( settings.get( "WINDOW", "WIDTH" ).value() );
	auto winHeight = ConvertTo<uint32_t>( settings.get( "WINDOW", "HEIGHT" ).value() );
	auto fps = ConvertTo<uint32_t>( settings.get( "WINDOW", "FPS" ).value() );

	GameWindow._create( { winWidth, winHeight }, fps );
}
}