/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "Entity.hpp"

namespace con::priv
{
class EntityStorage final :
	public IUpdatable
{
public:
	template <typename TEntity, typename ...TArgs>
	TEntity& spawn( TArgs&& ...args )
	{
		static_assert( std::is_base_of_v<Entity, TEntity> );

		auto& created = entities.emplace_back( std::make_unique<TEntity>( std::forward<TArgs>( args )... ) );
		created->onSpawn();

		return dynamic_cast<TEntity&>( *created.get() );
	}

	int16_t getUpdatePriority() const override
	{
		return -2;
	}

	void update() override;

	template <typename TEntity>
	std::vector<TEntity*> getAllEntitiesOfType()
	{
		std::vector<TEntity*> vecToReturn;

		for ( auto& uPtr : entities )
			if ( auto e = dynamic_cast<TEntity*>( uPtr.get() ); e )
				vecToReturn.emplace_back( e );

		return vecToReturn;
	}

	template <>
	std::vector<Entity*> getAllEntitiesOfType()
	{
		std::vector<Entity*> vecToReturn;
		for ( auto& uPtr : entities )
			vecToReturn.emplace_back( uPtr.get() );

		return vecToReturn;
	}

private:
	inline static const sf::Time CLEANUP_INTERVAL = sf::seconds( 2 );

	std::vector<std::unique_ptr<Entity>> entities;
	sf::Clock cleanupClock;

	void cleanup();
};
}