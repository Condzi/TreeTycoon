/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "BasicAssetHolder.hpp"
#include "AudioHolder.hpp"
#include "Settings.hpp"

namespace con::priv
{
class AssetsClass final
{
public:
	AssetsClass();

	TextureHolder Texture;
	FontHolder Font;
	SoundHolder Sound;
	MusicHolder Music;
	SettingsClass Settings;
};
}

namespace con
{
extern con::priv::AssetsClass Assets;
}