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
	TSystem& addSystem( int16_t updatePriority, TArgs&& ...args )
	{
		static_assert( std::is_base_of_v<System, TSystem> );

		auto& sys = systems.emplace_back( std::make_unique<TSystem>( std::forward<TArgs>( args )... ) );
		sys->_setUpdatePriority( updatePriority );
		sys->_setScene( parentScene );
		needsSort = true;

		return *dynamic_cast<TSystem*>( sys.get() );
	}

	int8_t getUpdatePriority() const override
	{
		return ConvertTo<int8_t>( UpdatePriority::SystemStorage );
	}

	void updateSystems();

private:
	Scene& parentScene;
	bool needsSort = false;
	std::vector<std::unique_ptr<System>> systems;

	void update() override;
};
}