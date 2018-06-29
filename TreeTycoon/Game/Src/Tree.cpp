/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "GamePCH.hpp"

#include "Tree.hpp"
#include "Plot.hpp"

Tree::Tree( const TreeInfo* const info_, const std::string& parentPlotName ) :
	Tree( info_, std::hash<std::string>{}( parentPlotName ) )
{}

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
	const auto currentPlotNameHash = GlobalGameData.CurrentPlot ? GlobalGameData.CurrentPlot->getInfo().nameHash : 0;
	auto& gui = con::Global.GUI;

	if ( currentPlotNameHash == parentPlotHash && button->getParent() == nullptr )
		gui.add( button );
	else if ( currentPlotNameHash != parentPlotHash && button->getParent() != nullptr )
		gui.remove( button );
}

void Tree::initButton()
{
	button = tgui::Button::create();
	auto* buttonRenderer = button->getRenderer();
	buttonRenderer->setBackgroundColor( tgui::Color::Transparent );
	buttonRenderer->setBackgroundColorHover( tgui::Color::Transparent );
	buttonRenderer->setBackgroundColorDown( tgui::Color::Transparent );
	buttonRenderer->setBorderColorHover( tgui::Color::calcColorOpacity( tgui::Color::White, 0.1 ) );
	buttonRenderer->setBorderColorFocused( tgui::Color::calcColorOpacity( tgui::Color::White, 0.5 ) );
	buttonRenderer->setBorderColor( tgui::Color::Transparent );
	buttonRenderer->setBorderColorDown( tgui::Color::Transparent );

	button->setSize( constants::TREE_TEXTURE_WIDTH, constants::TREE_TEXTURE_HEIGHT );

	button->connect( "pressed", [&]() {
		auto& gui = con::Global.GUI;

		auto pic = gui.get<tgui::Picture>( "picture_tree" );
		pic->setEnabled( true );
		pic->setVisible( true );
		pic->getRenderer()->setTexture( { *texture, getTextureRect() } );

		auto treeName = gui.get<tgui::Label>( "label_treename" );
		treeName->setEnabled( true );
		treeName->setVisible( true );
		treeName->setText( info->name );

		auto treeFruits = gui.get<tgui::Label>( "label_treefruits" );
		treeFruits->setEnabled( true );
		treeFruits->setVisible( true );
		treeFruits->setText( info->fruitType );
	} );
}

