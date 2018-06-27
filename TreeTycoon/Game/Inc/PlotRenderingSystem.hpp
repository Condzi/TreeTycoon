/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "Plot.hpp"

class PlotRenderingSystem final :
	public con::System
{
public:
	PlotRenderingSystem()
	{
		mapSprite.setPosition( 340, 20 );
	}

	void onUpdate() override
	{
		auto& trees = GlobalGameData.CurrentPlot->getTreesArray();
		const auto mapSz = trees.size2D();
		const Vec2u texSz{ con::ConvertTo<uint32_t>( constants::TREE_TEXTURE_WIDTH ), con::ConvertTo<uint32_t>( constants::TREE_TEXTURE_HEIGHT ) };
		mapTexture.create( mapSz.x * texSz.x, mapSz.y * texSz.y );
		sf::Sprite tempSprite;

		mapTexture.clear( sf::Color::Transparent );
		for ( const auto tree : trees ) {
			if ( !tree )
				continue;

			const Vec2f spritePos{ tree->position.x * texSz.x, tree->position.y * texSz.y };
			tempSprite.setPosition( spritePos );
			tempSprite.setTexture( *tree->texture );
			tempSprite.setTextureRect( tree->getTextureRect() );
			mapTexture.draw( tempSprite );
			mapTexture.display();
		}

		mapSprite.setTexture( mapTexture.getTexture() );
	}

private:
	sf::RenderTexture mapTexture;
	con::Sprite mapSprite;
};