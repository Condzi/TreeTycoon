/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include <algorithm>
#include <array>
#include <cinttypes>
#include <cctype>
#include <fstream>
#include <filesystem>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <optional>
#include <string>
#include <sstream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Global.hpp"

using float32_t = float;
using float64_t = double;

template <typename T>
using Vec2 = sf::Vector2<T>;
using Vec2i = Vec2<int32_t>;
using Vec2u = Vec2<uint32_t>;
using Vec2f = Vec2<float32_t>;

namespace con
{
enum class UpdatePriority : int8_t
{
	Drawable,
	Entity,
	SystemStorage,
	EntityStorage,
	SceneStack,
	Renderer
};
}
