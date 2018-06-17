/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "Entity.hpp"

namespace con::priv
{
class EntityStorage final :
	public IUpdatable,
	public ILogger
{
public:
	inline static const sf::Time CLEANUP_INTERVAL = sf::seconds( 2 );
	static constexpr size_t ENTITIES_COUNT = 512;

	template <typename TEntity, typename ...TArgs>
	TEntity& spawn( TArgs&& ...args )
	{
		static_assert( std::is_base_of_v<Entity, TEntity> );

		auto& created = getFreeSlot();
		created = std::make_unique<TEntity>( std::forward<TArgs>( args )... );
		created->onSpawn();

		return dynamic_cast<TEntity&>( *created.get() );
	}

	int8_t getUpdatePriority() const override
	{
		return ConvertTo<int8_t>( UpdatePriority::Entity );
	}

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
			if ( uPtr )
				vecToReturn.emplace_back( uPtr.get() );

		return vecToReturn;
	}

private:
	std::vector<std::unique_ptr<Entity>> entities{ ENTITIES_COUNT };
	sf::Clock cleanupClock;

	std::string loggerName() const override
	{
		return "Entity Storage";
	}

	void cleanup();
	void update() override;
	std::unique_ptr<Entity>& getFreeSlot();
};
}