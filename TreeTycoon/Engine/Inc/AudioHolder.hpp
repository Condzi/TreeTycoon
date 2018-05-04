/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

namespace con::priv
{
class IAudioHolder :
	public ILogger
{
public:
	virtual ~IAudioHolder() = default;

	virtual void play( const std::string& name ) = 0;
	// <0,100>
	virtual void setVolume( uint8_t value ) = 0;
};

class SoundHolder final :
	public IAudioHolder
{
public:
	bool load( const std::string& path, const std::string& name );
	void play( const std::string& name ) override;
	void setVolume( uint8_t value ) override;

private:
	uint8_t volume = 100;
	static constexpr size_t PLAYERS_LIMIT = 32;
	std::array<sf::Sound, PLAYERS_LIMIT> players;
	std::unordered_map<std::string, sf::SoundBuffer> buffers;

	sf::SoundBuffer* findSoundBuffer( const std::string& name );
	sf::Sound* findFreeSoundPlayer();
	void assignSoundPlayer( sf::Sound& player, sf::SoundBuffer& buffer );

	std::string loggerName() const override
	{
		return "Sound Holder";
	}
};

class MusicHolder final :
	public IAudioHolder
{
public:
	void add( const std::string& path, const std::string& name );
	void play( const std::string& name ) override;
	void setVolume( uint8_t value ) override;
	
	bool isPlaying();
	sf::Music& getPlayer();

private:
	uint8_t volume = 100;
	sf::Music player;
	// <name, path>
	std::unordered_map<std::string, std::string> music;

	std::string loggerName() const override
	{
		return "Music Holder";
	}

	std::string* findPath( const std::string& name );
};
}