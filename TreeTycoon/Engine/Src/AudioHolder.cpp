/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "EnginePCH.hpp"
#include "Debug.hpp"

#include "AudioHolder.hpp"

namespace con::priv
{
bool SoundHolder::load( const std::string& path, const std::string& name )
{
	if ( sf::SoundBuffer buffer; buffer.loadFromFile( path ) ) {
		buffers[name] = std::move( buffer );
		return true;
	} else {
		log( LogPriority::Error, "can't load \"", name, "\" from \"", path, "\"." );
		return false;
	}
}

void SoundHolder::play( const std::string& name )
{
	if ( auto* player = findFreeSoundPlayer(); player )
		if ( auto* buffer = findSoundBuffer( name ); buffer )
			assignSoundPlayer( *player, *buffer );
}

void SoundHolder::setVolume( uint8_t value )
{
	volume = value;
}

sf::SoundBuffer* SoundHolder::findSoundBuffer( const std::string& name )
{
	if ( auto it = buffers.find( name ); it != buffers.end() )
		return &it->second;
	else {
		log( LogPriority::Warning, "can't find \"", name, "\"." );
		return nullptr;
	}
}

sf::Sound* SoundHolder::findFreeSoundPlayer()
{
	auto it = std::find_if( players.begin(), players.end(), []( sf::Sound& player ) {
		return player.getStatus() == sf::Sound::Status::Stopped;
	} );

	if ( it != players.end() )
		return &( *it );
	else {
		log( LogPriority::Warning, "no free sound players (max is", PLAYERS_LIMIT, ")." );
		return nullptr;
	}
}

void SoundHolder::assignSoundPlayer( sf::Sound& player, sf::SoundBuffer& buffer )
{
	player.stop();
	player.setVolume( ConvertTo<float>( volume ) );
	player.setBuffer( buffer );
	player.play();
}

void MusicHolder::add( const std::string& path, const std::string& name )
{
	music[name] = path;
}

void MusicHolder::play( const std::string& name )
{
	if ( auto* path = findPath( name ); path )
		if ( player.openFromFile( *path ) ) {
			player.setVolume( ConvertTo<float>( volume ) );
			player.play();
		} else
			log( LogPriority::Error, "can't load \"", name, "\" from \"", *path, "\"." );
}

void MusicHolder::setVolume( uint8_t value )
{
	volume = value;
}

bool MusicHolder::isPlaying()
{
	return player.getStatus() == sf::Music::Status::Playing;
}

sf::Music& MusicHolder::getPlayer()
{
	return player;
}

std::string* MusicHolder::findPath( const std::string& name )
{
	if ( auto it = music.find( name ); it != music.end() )
		return &it->second;
	else {
		log( LogPriority::Warning, "can't find \"", name, "\"." );
		return nullptr;
	}
}
}