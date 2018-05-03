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

int testEntityVar = 0;
int testSceneVar = 0;
int testSystemVarA = 0;
int testSystemVarB = 0;


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

class ExampleScene final :
	public con::Scene
{};

class ExampleSystemA final :
	public con::System
{
public:
	void onUpdate() override
	{
		testSystemVarA++;
	}
};

class ExampleSystemB final :
	public con::System
{
public:
	void onUpdate() override
	{
		if ( testSystemVarA )
			testSystemVarB++;
	}
};

TEST_CASE( "Entity", "[Gameplay Objects]" )
{
	ExampleEntity entity;

	entity.onSpawn();
	REQUIRE( entity.getStatus() == con::Entity::Status::Enabled );
	REQUIRE( testEntityVar == 1 );
	entity.disable();
	REQUIRE( entity.getStatus() == con::Entity::Status::Disabled );
	REQUIRE( testEntityVar == 2 );
	entity.enable();
	REQUIRE( entity.getStatus() == con::Entity::Status::Enabled );
	REQUIRE( testEntityVar == 3 );

	con::priv::Updater.update();
	REQUIRE( testEntityVar == 4 );
	entity.disable();
	con::priv::Updater.update();
	REQUIRE( testEntityVar == 5 );

	entity.kill();
	REQUIRE( entity.getStatus() == con::Entity::Status::Dead );
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

	REQUIRE( es.getAllEntitiesOfType<con::Entity>().size() == 1 );
	// fukup if 2 seconds. (too short for some reason?)
	std::this_thread::sleep_for( std::chrono::seconds( 3 ) );
	con::priv::Updater.update();
	REQUIRE( es.getAllEntitiesOfType<ExampleEntity>().empty() == true );
}

TEST_CASE( "SystemStorage", "[Gameplay Objects]" )
{
	testSystemVarA = testSystemVarB = 0;
	ExampleScene scene;
	con::priv::SystemStorage ss{ &scene };

	ss.addSystem<ExampleSystemB>( 1 );
	ss.addSystem<ExampleSystemA>( 0 );

	con::priv::Updater.update();

	ss.updateSystems();

	REQUIRE( testSystemVarA == testSystemVarB );
}