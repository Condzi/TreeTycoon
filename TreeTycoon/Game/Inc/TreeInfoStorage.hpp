/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "TreeInfo.hpp"

class TreeInfoStorage final :
	public con::ILogger
{
public:
	void load();

	std::optional<const TreeInfo* const> findTree( const std::string& name );

private:
	std::vector<TreeInfo> infos;

	bool loadConfig();
	void loadTextures();

	std::string loggerName() const override
	{
		return "Tree Info Storage";
	}
};