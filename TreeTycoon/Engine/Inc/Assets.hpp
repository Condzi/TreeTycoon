/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "BasicAssetHolder.hpp"
#include "AudioHolder.hpp"

namespace con::priv
{
class AssetsClass
{
public:
	TextureHolder Texture;
	FontHolder Font;
	SoundHolder Sound;
	MusicHolder Music;
};
}