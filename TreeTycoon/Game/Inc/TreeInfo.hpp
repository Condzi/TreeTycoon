/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

struct TreeInfo final
{
	std::string texturePath;
	std::string name;
	std::string type;
	std::string fruitType;
	int16_t seedPrice = 0;
	int16_t maxHeight = 0;
	float32_t growingSpeed = 0;

	// "tree_" + name + "_" + type
	std::string textureName;
};