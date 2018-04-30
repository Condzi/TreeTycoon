/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Catch.hpp"

#include <EntityStorage.hpp>
#include <Updater.hpp>
// for sleep
#include <thread>

int testEntityVar = 0;

class ExampleEntity final :
	public con::Entity
{
public:
	void onSpawn() override
	{
		testEntityVar++;
	}

	void onKill() override
	{
		testEntityVar++;
	}

	void onEnable() override
	{
		testEntityVar++;
	}

	void onDisable() override
	{
		testEntityVar++;
	}

	void onUpdate() override
	{
		testEntityVar++;
	}
};

TEST_CASE( "Entity", "[Gameplay Objects]" )
{
	ExampleEntity entity;

	entity.onSpawn();
	REQUIRE( entity.getState() == con::Entity::State::Enabled );
	REQUIRE( testEntityVar == 1 );
	entity.disable();
	REQUIRE( entity.getState() == con::Entity::State::Disabled );
	REQUIRE( testEntityVar == 2 );
	entity.enable();
	REQUIRE( entity.getState() == con::Entity::State::Enabled );
	REQUIRE( testEntityVar == 3 );

	con::priv::Updater.update();
	REQUIRE( testEntityVar == 4 );
	entity.disable();
	con::priv::Updater.update();
	REQUIRE( testEntityVar == 5 );

	entity.kill();
	REQUIRE( entity.getState() == con::Entity::State::Dead );
	REQUIRE( testEntityVar == 6 );

	con::priv::Updater.update();
	REQUIRE( testEntityVar == 6 );
	testEntityVar = 0;
}

TEST_CASE( "EntityStorage", "[Gameplay Objects]" )
{
	con::priv::EntityStorage es;

	REQUIRE( testEntityVar == 0 );
	auto& e = es.spawn<ExampleEntity>();
	REQUIRE( testEntityVar == 1 );
	e.kill();
	REQUIRE( testEntityVar == 2 );

	REQUIRE( es.getAllEntitiesOfType<ExampleEntity>().size() == 1 );
	std::this_thread::sleep_for( std::chrono::seconds( 2 ) );
	con::priv::Updater.update();
	REQUIRE( es.getAllEntitiesOfType<ExampleEntity>().empty() );
}