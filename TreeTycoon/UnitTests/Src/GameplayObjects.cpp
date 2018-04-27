/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Catch.hpp"

#include <Entity.hpp>
#include <Updater.hpp>

int testEntityVar = 0;

TEST_CASE( "Entity", "[Gameplay Objects]" )
{
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
}