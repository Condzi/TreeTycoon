/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

namespace con
{
class IUpdatable;
}

namespace con::priv
{
class UpdaterClass final
{
public:
	void add( IUpdatable* updatable );
	void remove( IUpdatable* updatable );

	void update();

private:
	std::vector<IUpdatable*> updatables;

	void sortByPriority();
};
}