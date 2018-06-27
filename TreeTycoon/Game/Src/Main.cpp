#include "GamePCH.hpp"

#include "WorldScene.hpp"
#include "PlotViewScene.hpp"

int main()
{
	con::Global.SceneStack.registerScene<WorldScene>( 0 );
	con::Global.SceneStack.registerScene<PlotViewScene>( 1 );
	con::Global.SceneStack.push( 0 );

	con::Global.Game.run();
}