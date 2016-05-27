#include "gamestate.h"
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

	GameStateTree gametree(ygritte, snow, true);

	gametree.StartGenerate();
	gametree.Print();

	int a;
	std::cin>>a;
}