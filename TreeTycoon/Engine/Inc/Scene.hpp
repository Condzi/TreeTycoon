/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "EntityStorage.hpp"
#include "System.hpp"

namespace con
{
class Scene :
	public ILogger
{
public:
	enum class Status : int8_t
	{
		Enabled,
		Disabled,
		Unloaded
	};

	std::string tag;

	virtual void onLoad() {}
	virtual void onUnload() {}
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
			if ( auto* casted = dynamic_cast<TEntity*>( entity ); casted )
				lambda( *casted );
		} )
	}

	void _enable();
	void _disable();

private:
	Status status = Status::Enabled;
	priv::EntityStorage entities;

	std::string loggerName() const override final;
	void disableEntities();
	void enableEntities();
};
}