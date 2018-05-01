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
	RULE_OF_FIVE_NO_CTOR( System );

	// Remember to write using con::System::System in class declaration!
	System( int16_t updatePriorirty_ );

	virtual void onStart() {}
	virtual void onStop() {}
	virtual void onUpdate() {}

	void setUpdatePriority( int16_t val );
	int16_t getUpdatePriority() const;

	void _setScene( Scene& scene );

protected:
	Scene* parentScene = nullptr;

private:
	int16_t updatePriority = 0;
};
}