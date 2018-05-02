/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "System.hpp"
#include "IUpdatable.hpp"

namespace con::priv
{
class SystemStorage final : 
	public IUpdatable
{
public:
	SystemStorage( Scene* parentScene_ );

	template <typename TSystem, typename ...TArgs>
	void addSystem( int16_t updatePriority, TArgs&& ...args )
	{
		auto& sys = systems.emplace_back( std::make_unique<TSystem>( std::forward<TArgs>( args )... ) );
		sys->_setUpdatePriority( updatePriority );
		sys->setScene( parentScene );
		needsSort = true;
	}

	int16_t getUpdatePriority() const override
	{	
		return -3;
	}

	void updateSystems();

private:
	Scene& parentScene;
	bool needsSort = false;
	std::vector<std::unique_ptr<System>> systems;

	void update() override;
};
}