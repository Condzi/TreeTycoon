/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "GamePCH.hpp"

#include "GlobalGameData.hpp"
#include "TreeInfosStorage.hpp"
#include "PlotsStorage.hpp"

GlobalGameDataClass::GlobalGameDataClass() :
	TreeInfos( *( new TreeInfosStorage ) ),
	Plots( *( new PlotsStorage ) )
{}

inline GlobalGameDataClass GlobalGameData{};
