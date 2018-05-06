/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Catch.hpp"

#include <Updater.hpp>
#include <IUpdatable.hpp>

int value = 0;

class UpdatableA : public con::IUpdatable
{
public:
	int16_t getUpdatePriority() const override
	{
		return 1;
	}

	void update() override
	{
		value++;
	}
};

class UpdatableB : public con::IUpdatable
{
public:
	int16_t getUpdatePriority() const override
	{
		return 2;
	}

	void update() override
	{
		value *= 2;
	}
};

TEST_CASE( "Updater", "[IUpdatable]" )
{
	SECTION( "Adding and removing" )
	{
		REQUIRE( value == 0 );
		{
			UpdatableA a;
			con::Global._Updater.update();
		}
		REQUIRE( value == 1 );
		con::Global._Updater.update();
		value = 0;
	}

	SECTION( "Updating order" )
	{
		REQUIRE( value == 0 );
		{
			UpdatableA a;
			UpdatableB b;
			con::Global._Updater.update();
			// If a executes first, then value = 1, and then b does * 2, so in the end value = 2, otherwise - 0.
			REQUIRE( value == 2 );
		}
		value = 0;
	}
}