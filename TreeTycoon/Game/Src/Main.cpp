/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Game.hpp"
#include "Drawable.hpp"
#include "Scene.hpp"
#include "SceneStack.hpp"
#include "Input.hpp"

using namespace con;

class ExampleEntity final :
	public Entity
{
public:
	RectangleShape rect;
	ExampleEntity()
	{
		rect.setFillColor( sf::Color{ 155,155,155 } );
		rect.setSize( { 400,300 } );
		rect.setOrigin( 200, 150 );
		rect.setPosition( 400, 300 );
	}

	void onUpdate() override
	{
		const float delta = Global.FrameTime.asSeconds();
		const Vec2f maxForce{ 150 * delta,150 * delta };
		Vec2f force{};

		if ( Global.Input.isHeld( KeyboardKey::W ) )
			force.y = -maxForce.y;
		if ( Global.Input.isHeld( KeyboardKey::S ) )
			force.y = maxForce.y;
		if ( Global.Input.isHeld( KeyboardKey::A ) )
			force.x = -maxForce.x;
		if ( Global.Input.isHeld( KeyboardKey::D ) )
			force.x = maxForce.x;

		rect.move( force );

		if ( Global.Input.isDown( KeyboardKey::Escape ) )
			Global.ExitGame = true;
	}
};

class ExampleScene final :
	public Scene
{
public:
	void onPush() override
	{
		spawn<ExampleEntity>();
	}
};

int main()
{
	Global.SceneStack.registerScene<ExampleScene>( 0 );
	Global.SceneStack.push( 0 );

	Global.Game.run();
}