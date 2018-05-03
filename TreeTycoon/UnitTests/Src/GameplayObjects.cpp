/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Catch.hpp"

#include <EntityStorage.hpp>
#include <SystemStorage.hpp>
#include <Updater.hpp>
#include <Scene.hpp>
// for sleep
#include <thread>

class ExampleEntityA final :
	public con::Entity
{
public:
	inline static int testVar = 0;

	void onSpawn() override
	{
		testVar++;
	}

	void onKill() override
	{
		testVar++;
	}

	void onEnable() override
	{
		testVar++;
	}

	void onDisable() override
	{
		testVar++;
	}

	void onUpdate() override
	{
		testVar++;
	}
};

class ExampleEntityB final :
	public con::Entity
{
public:
	inline static int testVar = 0;

	void onSpawn() override
	{
		testVar++;
	}

	void onKill() override
	{
		testVar++;
	}

	void onEnable() override
	{
		testVar++;
	}

	void onDisable() override
	{
		testVar++;
	}

	void onUpdate() override
	{
		testVar++;
	}
};

class ExampleSceneA final :
	public con::Scene
{
public:
	inline static int testVar = 0;
};

class ExampleSceneB final :
	public con::Scene
{
public:
	inline static int testVar = 0;
};

class ExampleSystemA final :
	public con::System
{
public:
	inline static int testVar = 0;

	void onUpdate() override
	{
		testVar++;
	}
};

class ExampleSystemB final :
	public con::System
{
public:
	inline static int testVar = 0;

	void onUpdate() override
	{
		if ( ExampleSystemA::testVar )
			testVar++;
	}
};

TEST_CASE( "Entity", "[Gameplay Objects]" )
{
	ExampleEntityA::testVar = 0;
	ExampleEntityA entity;

	entity.onSpawn();
	REQUIRE( entity.getStatus() == con::Entity::Status::Enabled );
	REQUIRE( ExampleEntityA::testVar == 1 );
	entity.disable();
	REQUIRE( entity.getStatus() == con::Entity::Status::Disabled );
	REQUIRE( ExampleEntityA::testVar == 2 );
	entity.enable();
	REQUIRE( entity.getStatus() == con::Entity::Status::Enabled );
	REQUIRE( ExampleEntityA::testVar == 3 );

	con::priv::Updater.update();
	REQUIRE( ExampleEntityA::testVar == 4 );
	entity.disable();
	con::priv::Updater.update();
	REQUIRE( ExampleEntityA::testVar == 5 );

	entity.kill();
	REQUIRE( entity.getStatus() == con::Entity::Status::Dead );
	REQUIRE( ExampleEntityA::testVar == 6 );

	con::priv::Updater.update();
	REQUIRE( ExampleEntityA::testVar == 6 );
}

TEST_CASE( "EntityStorage", "[Gameplay Objects]" )
{
	ExampleEntityA::testVar = 0;
	con::priv::EntityStorage es;

	auto& e = es.spawn<ExampleEntityA>();
	REQUIRE( ExampleEntityA::testVar == 1 );
	e.kill();
	REQUIRE( ExampleEntityA::testVar== 2 );

	REQUIRE( es.getAllEntitiesOfType<con::Entity>().size() == 1 );
	// fukup if 2 seconds. (too short for some reason?)
	std::this_thread::sleep_for( std::chrono::seconds( 3 ) );
	con::priv::Updater.update();
	REQUIRE( es.getAllEntitiesOfType<ExampleEntityA>().empty() == true );
}

TEST_CASE( "SystemStorage", "[Gameplay Objects]" )
{
	ExampleSystemA::testVar = ExampleSystemB::testVar = 0;
	ExampleSceneA scene;
	con::priv::SystemStorage ss{ &scene };

	ss.addSystem<ExampleSystemB>( 1 );
	ss.addSystem<ExampleSystemA>( 0 );

	con::priv::Updater.update();

	ss.updateSystems();

	REQUIRE( ExampleSystemA::testVar == ExampleSystemB::testVar );
}