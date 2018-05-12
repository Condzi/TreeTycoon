/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "IUpdatable.hpp"
#include "Debug.hpp"

namespace con
{
class Scene;

class Entity :
	public IUpdatable,
	public ILogger
{
public:
	RULE_OF_FIVE( Entity );
	virtual ~Entity() = default;

	enum class Status : int8_t
	{
		Enabled,
		Disabled,
		Dead
	};

	Vec2f position;
	// position will be treated in range <0,1> if true
	bool useAbsolutePositioning = false;
	std::string tag = "UnnamedEntity";

	void kill();
	void disable();
	void enable();

	int8_t getUpdatePriority() const final
	{
		return ConvertTo<int8_t>( UpdatePriority::Entity );
	}

	Status getStatus() const;
	Scene& getParentScene();
	int32_t getUniqueID();

	virtual void onSpawn() {}
	virtual void onKill() {}
	virtual void onEnable() {}
	virtual void onDisable() {}
	virtual void onUpdate() {}

	void _setParentScene( Scene& scene );

private:
	Status status = Status::Enabled;
	Scene* parentScene = nullptr;
	inline static int32_t UNIQUE_ID_COUNTER = 0;
	const int32_t uniqueID = UNIQUE_ID_COUNTER++;

	void update() override final;
	std::string loggerName() const override final;
};
}