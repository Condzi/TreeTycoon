/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "GamePCH.hpp"

#include "Tree.hpp"

Tree::Tree( const TreeInfo const* info, GUI& gui ) :
	INFO( *info )
{
	updateVisualRepresentation();
	clickableButton = tgui::Button::create();
	clickableButton->setSize( constants::TREE_TEXTURE_WIDTH, constants::TREE_TEXTURE_HEIGHT );
	clickableButton->setInheritedOpacity( 0.1f );
	gui.add( clickableButton );
}

void Tree::setPosition( const Vec2f& position )
{
	clickableButton->setPosition( position );
	visualRepresentation.setPosition( position.x, position.y - constants::TREE_TEXTURE_HEIGHT_DIFF );
}

void Tree::updateVisualRepresentation()
{
	visualRepresentation.setTexture( con::Global.Assets.Texture.get( INFO.textureName ) );
	sf::IntRect rect
	{
		statistics.growingState * constants::TREE_TEXTURE_WIDTH,
		0,
		constants::TREE_TEXTURE_WIDTH,
		constants::TREE_TEXTURE_REAL_HEIGHT
	};

	visualRepresentation.setTextureRect( rect );
}
