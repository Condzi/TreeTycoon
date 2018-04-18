/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "IUpdatable.hpp"

namespace con
{
class Scene;

// in update() check `if(getState() == State::Disable) return;` to not update disabled entities, if you don't want to. Because 
// you may want. 
class Entity :
	public IUpdatable
{
public:
	enum class State : int8_t
	{
		Enabled,
		Disabled,
		ToKill,
		Dead
	};

	sf::Vector2f position;
	// position will be treated in range <0,1> if true
	bool useAbsolutePositioning = false;
	std::string tag;

	void kill() const;
	void disable();
	void enable();

	int16_t getPriority() const override final
	{
		return -1;
	}

	State getSatate() const;
	Scene& getParentScene();

	virtual void onSpawn() {}
	virtual void onKill() {}
	virtual void onEnable() {}
	virtual void onDisable() {}

	void _setParentScene( Scene& scene );

private:
	State state = State::Enabled;
	Scene* parentScene = nullptr;
	inline static int32_t UNIQUE_ID_COUNTER = 0;
	const int32_t uniqueID = UNIQUE_ID_COUNTER++;
};
}