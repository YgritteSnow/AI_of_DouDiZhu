#include "gamestate.h"
#include "game.h"
#include <iostream>

#define ReleaseVersion

int main()
{
	std::vector< Card > ygritte;

#ifdef ReleaseVersion
	const int ysize = 6;
	int y[ysize] = {14, 13, 13, 13, 11, 9};
#else
	const int ysize = 1;
	int y[ysize] = {9};
#endif
	for( int i = 0; i < ysize; ++i )
	{
		ygritte.push_back( Card( y[i], Card::SuitType_clubs ) );
	}

	std::vector< Card > snow;

#ifdef ReleaseVersion
	const int jsize = 7;
	int j[jsize] = {15, 12, 7, 7, 7, 4, 3};
#else
	const int jsize = 5;
	int j[jsize] = {15, 7, 7, 7, 4};
#endif
	for( int i = 0; i < jsize; ++i )
	{
		snow.push_back( Card( j[i], Card::SuitType_clubs ) );
	}

	Game game( ygritte, snow, true);

	game.Start();
	while( !game.HasEnd() )
	{
		game.NextMove();
	}
	game.PrintResult();

	int a;
	std::cin>>a;
}