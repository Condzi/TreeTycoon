/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

struct TreeStats final
{
	int16_t growingState = 0;
	int16_t height = 0;
	int16_t water = 0;
	int16_t fruits = 0;
	int16_t fertelizationBoost = 0;
	int16_t health = 0;
	std::bitset<1> randomEventsFlags;

	int16_t value() const
	{
		return ( growingState * height ) / ( randomEventsFlags.count() + 1 );
	}

	void calculateFruits()
	{
		fruits = ( height * fertelizationBoost * ( health / 100 ) )/( ( water + 1 ) / 10 );
	}
};