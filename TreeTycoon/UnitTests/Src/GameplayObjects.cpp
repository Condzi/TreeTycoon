/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Catch.hpp"

#include <EntityStorage.hpp>
#include <SystemStorage.hpp>
#include <Updater.hpp>
#include <SceneStack.hpp>
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

	void onPush() override
	{
		testVar++;
	}

	void onPop() override
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

class ExampleSceneB final :
	public con::Scene
{
public:
	inline static int testVar = 0;

	void onPush() override
	{
		testVar++;
	}

	void onPop() override
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

TEST_CASE( "Scene - spawning", "[Gameplay Objects]" )
{
	ExampleEntityA::testVar = ExampleEntityB::testVar = 0;
	ExampleSceneA scene;

	scene.spawn<ExampleEntityA>();
	scene.spawn<ExampleEntityB>();

	REQUIRE( ExampleEntityA::testVar == 1 );
	REQUIRE( ExampleEntityB::testVar == 1 );

	scene._disable();
	REQUIRE( ExampleSceneA::testVar == 1 );

	REQUIRE( ExampleEntityA::testVar == 2 );
	REQUIRE( ExampleEntityB::testVar == 2 );

	con::priv::Updater.update();
	scene._update();
	REQUIRE( ExampleEntityA::testVar == 2 );
	REQUIRE( ExampleEntityB::testVar == 2 );

	scene._enable();

	REQUIRE( ExampleSceneA::testVar == 2 );

	REQUIRE( ExampleEntityA::testVar == 3 );
	REQUIRE( ExampleEntityB::testVar == 3 );
	con::priv::Updater.update();
	scene._update();
	REQUIRE( ExampleSceneA::testVar == 3 );

	REQUIRE( ExampleEntityA::testVar == 4 );
	REQUIRE( ExampleEntityB::testVar == 4 );
}

TEST_CASE( "Scene - manipulating Entities", "[Gameplay Objects]" )
{
	ExampleSceneA scene;

	scene.spawn<ExampleEntityA>();
	scene.spawn<ExampleEntityB>();

	ExampleEntityA::testVar = ExampleEntityB::testVar = 0;

	scene.forEachEntity( []( con::Entity& e ) {
		e.onUpdate();
	} );

	REQUIRE( ExampleEntityA::testVar == 1 );
	REQUIRE( ExampleEntityB::testVar == 1 );

	scene.forEachEntityOfType<ExampleEntityA>( []( ExampleEntityA& e ) {
		e.testVar++;
	} );

	REQUIRE( ExampleEntityA::testVar == 2 );
	REQUIRE( ExampleEntityB::testVar == 1 );

	scene.forEachEntityOfType<ExampleEntityB>( []( ExampleEntityB& e ) {
		e.testVar++;
	} );

	REQUIRE( ExampleEntityA::testVar == 2 );
	REQUIRE( ExampleEntityB::testVar == 2 );
}

TEST_CASE( "SceneStack", "[Gameplay Objects]" )
{
	auto& ss = con::SceneStack;
	ExampleSceneA::testVar = ExampleSceneB::testVar = 0;

	ss.registerScene<ExampleSceneA>( 0 );
	ss.registerScene<ExampleSceneB>( 1 );

	ss.push( 0 );
	con::priv::Updater.update();
	REQUIRE( ExampleSceneA::testVar == 2 );
	REQUIRE( ExampleSceneB::testVar == 0 );
	ss.disableCurrentScene();
	con::priv::Updater.update();
	REQUIRE( ExampleSceneA::testVar == 3 );
	REQUIRE( ExampleSceneB::testVar == 0 );
	ss.push( 1 );
	con::priv::Updater.update();
	REQUIRE( ExampleSceneA::testVar == 3 );
	REQUIRE( ExampleSceneB::testVar == 2 );
	con::priv::Updater.update();
	REQUIRE( ExampleSceneA::testVar == 3 );
	REQUIRE( ExampleSceneB::testVar == 3 );
	ss.pop();
	con::priv::Updater.update();
	REQUIRE( ExampleSceneA::testVar == 3 );
	REQUIRE( ExampleSceneB::testVar == 4 );
	ss.enableCurrentScene();
	con::priv::Updater.update();
	REQUIRE( ExampleSceneA::testVar == 5 );
	REQUIRE( ExampleSceneB::testVar == 4 );
}