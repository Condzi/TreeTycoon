/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "GamePCH.hpp"

#include "Tree.hpp"
#include "Plot.hpp"

Tree::Tree( const TreeInfo* const info_, const std::string& parentPlotName ) :
	info( info_ ),
	parentPlotHash( std::hash<std::string>{}( parentPlotName ) )
{
	initButton();
}

Tree::Tree( const TreeInfo* const info_, size_t parentPlotHash_ ) :
	info( info_ ),
	parentPlotHash( parentPlotHash_ )
{
	texture = &con::Global.Assets.Texture.get( info->textureName );
	initButton();
}

RectI Tree::getTextureRect() const
{
	return
	{
		stats.growingState * constants::TREE_TEXTURE_WIDTH,
		0,
		constants::TREE_TEXTURE_WIDTH,
		constants::TREE_TEXTURE_HEIGHT
	};
}

void Tree::onUpdate()
{
	if ( GlobalGameData.CurrentPlot->getInfo().nameHash != parentPlotHash )
		button->setEnabled( false );
}

void Tree::initButton()
{
	button = tgui::Button::create();
	con::Global.GUI.add( button );
	auto* buttonRenderer = button->getRenderer();
	buttonRenderer->setBackgroundColor( tgui::Color::Transparent );
	buttonRenderer->setBackgroundColorHover( tgui::Color::calcColorOpacity( sf::Color::White, 0.1 ) );
	buttonRenderer->setBackgroundColorDown( tgui::Color::calcColorOpacity( sf::Color::White, 0.5 ) );

	button->setSize( constants::TREE_TEXTURE_WIDTH, constants::TREE_TEXTURE_HEIGHT );

	button->connect( "pressed", [&]() {
		auto& gui = con::Global.GUI;

		auto pic = gui.get<tgui::Picture>( "picture_tree" );
		pic->setEnabled( true );
		pic->setVisible( true );
		pic->getRenderer()->setTexture( { *texture, getTextureRect() } );
	} );
}

