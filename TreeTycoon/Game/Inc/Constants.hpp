/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include <cinttypes>

namespace constants
{
constexpr int32_t TREE_TEXTURE_WIDTH = 32;
constexpr int32_t TREE_TEXTURE_HEIGHT = 32;
constexpr int32_t TREE_TEXTURE_REAL_HEIGHT = 48;
constexpr int32_t TREE_TEXTURE_HEIGHT_DIFF = TREE_TEXTURE_REAL_HEIGHT - TREE_TEXTURE_HEIGHT;

constexpr const char* TREES_CONFIG_PATH = "Data/Trees/tree_config.ini";
constexpr const char* PLOTS_CONFIG_PATH = "Data/Plots/plot_config.ini";
}