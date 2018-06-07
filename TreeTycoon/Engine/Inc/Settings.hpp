/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "INIFile.hpp"

namespace con::priv
{
class SettingsClass final :
	public INIFile
{
public:
	~SettingsClass()
	{
		save();
	}
};
}