/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

namespace con
{
class IUpdatable
{
public:
	IUpdatable();
	~IUpdatable();

	virtual int16_t getUpdatePriority() const = 0;
	virtual void update() = 0;
};
}