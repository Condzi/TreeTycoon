/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "Utility.hpp"

namespace con
{
class Scene;

class System
{
public:
	RULE_OF_FIVE( System );
	virtual ~System() = default;

	virtual void onUpdate() {}

	void _setUpdatePriority( int16_t val );
	int16_t _getUpdatePriority() const;
	void _setScene( Scene& scene );

protected:
	Scene* parentScene = nullptr;

private:
	int16_t updatePriority = 0;
};
}