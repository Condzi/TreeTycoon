/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "IUpdatable.hpp"
#include "Drawable.hpp"

namespace con::priv
{
class RendererClass final :
	public IUpdatable
{
public:
	int16_t getUpdatePriority() const override
	{
		return -6;
	}

	void add( IDrawable* drawable );
	void remove( IDrawable* drawable );

private:
	std::vector<IDrawable*> drawables;

	void sortByLayer();
	void render();
	void update() override;
};
}