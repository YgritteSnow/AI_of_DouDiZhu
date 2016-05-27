#include "gamestate.h"
#include "game.h"
#include <iostream>

int main()
{
	std::vector< Card > ygritte;
	ygritte.push_back( Card( 9, Card::SuitType_clubs ) );
	ygritte.push_back( Card( 9, Card::SuitType_clubs ) );

	std::vector< Card > snow;
	snow.push_back( Card( 6, Card::SuitType_clubs ) );
	snow.push_back( Card( 6, Card::SuitType_clubs ) );
	snow.push_back( Card( 7, Card::SuitType_clubs ) );
	snow.push_back( Card( 7, Card::SuitType_clubs ) );

	GameState startGame(ygritte, snow, true);
	
	Game game = Game( &startGame );

	game.Start();
	while( !game.HasEnd() )
	{
		game.NextMove();
	}
	game.PrintResult();

	int a;
	std::cin>>a;
}