/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "Entity.hpp"

namespace con::priv
{
// Update before or after Entities? 
class EntityStorage final : 
	public IUpdatable
{
public:
	std::vector<std::unique_ptr<Entity>> entities;

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


private:
	inline static const sf::Time CLEANUP_INTERVAL = sf::seconds( 2 );
	sf::Clock cleanupClock;

	void cleanup();
};
}