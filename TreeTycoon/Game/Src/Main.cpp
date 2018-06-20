#include "GamePCH.hpp"

#include "WorldScene.hpp"

int main()
{
	try {
		con::Global.SceneStack.registerScene<WorldScene>( 0 );
		con::Global.SceneStack.push( 0 );

		con::Global.Game.run();
	} catch ( const std::exception& exception ) {
		std::cout << std::endl << exception.what();
		std::cin.get();
	}
}