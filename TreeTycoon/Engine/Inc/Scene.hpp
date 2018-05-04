/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "EntityStorage.hpp"
#include "SystemStorage.hpp"

namespace con
{
class Scene :
	public ILogger
{
public:
	RULE_OF_FIVE( Scene );
	virtual ~Scene() = default;

	enum class Status : int8_t
	{
		Enabled,
		Disabled,
		Unloaded
	};

	std::string tag;

	virtual void onPush() {}
	virtual void onPop() {}
	virtual void onEnable() {}
	virtual void onDisable() {}
	virtual void onUpdate() {}

	template <typename TEntity, typename ...TArgs>
	TEntity& spawn( TArgs&& ...args )
	{
		return entities.spawn<TEntity>( std::forward<TArgs>( args )... );
	}

	template <typename TEntity>
	std::vector<TEntity*> getAllEntitiesOfType()
	{
		return entities.getAllEntitiesOfType<TEntity>();
	}

	template <typename TLambda>
	void forEachEntity( TLambda&& lambda )
	{
		auto entitiesVec = getAllEntitiesOfType<Entity>();
		for ( auto* entityPtr : entitiesVec )
			lambda( *entityPtr );
	}

	template <typename TEntity, typename TLambda>
	void forEachEntityOfType( TLambda&& lambda )
	{
		forEachEntity( [&]( Entity& entity ) {
			if ( auto* casted = dynamic_cast<TEntity*>( &entity ); casted )
				lambda( *casted );
		} );
	}

	template <typename TSystem, typename ...TArgs>
	TSystem& addSystem( int16_t updatePriority, TArgs&& ...args )
	{
		return systems.addSystem<TSystem>( updatePriority, std::forward<TArgs>( args )... );
	}

	void _enable();
	void _disable();
	void _update();

private:
	Status status = Status::Enabled;
	priv::EntityStorage entities;
	priv::SystemStorage systems{ this };

	std::string loggerName() const override final;
	void disableEntities();
	void enableEntities();
};
}