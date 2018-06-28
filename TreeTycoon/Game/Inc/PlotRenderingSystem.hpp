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
			tree->button->setPosition( spritePos );
			tempSprite.setPosition( spritePos );
			tempSprite.setTexture( *tree->texture );
			tempSprite.setTextureRect( tree->getTextureRect() );
			mapTexture.draw( tempSprite );
			mapTexture.display();
		}

		mapSprite.setTexture( mapTexture.getTexture() );
		setMapPosition();
		// buttons positions are set above, but have to shift because whole map sprite is shifted
		updateTreesButtonsPositions();
	}

private:
	sf::RenderTexture mapTexture;
	con::Sprite mapSprite;

	void setMapPosition()
	{
		mapSprite.setOrigin( mapSprite.getGlobalBounds().width / 2, mapSprite.getGlobalBounds().height / 2 );
		mapSprite.setPosition( con::Global.GameWindow.getSize().x / 2, con::Global.GameWindow.getSize().y / 2 );
	}

	void updateTreesButtonsPositions()
	{
		const auto offset = mapSprite.getPosition() - mapSprite.getOrigin();
		for ( auto tree : GlobalGameData.CurrentPlot->getTreesArray() ) {
			auto& button = tree->button;
			button->setPosition( button->getPosition() + offset );
		}
	}
};