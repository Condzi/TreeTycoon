#include "GamePCH.hpp"

#include "GameScene.hpp"

int main()
{
	Global.SceneStack.registerScene<GameScene>( 0 );
	Global.SceneStack.push( 0 );

	Global.Game.run();
}