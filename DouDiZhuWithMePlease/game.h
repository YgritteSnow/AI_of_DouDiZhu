#ifndef __F__MYPROJECTS_UDIZHUWITHMEPLEASE__DOUDIZHUWITHMEPLEASE_MINMAXTREE_H__
#define __F__MYPROJECTS_UDIZHUWITHMEPLEASE__DOUDIZHUWITHMEPLEASE_MINMAXTREE_H__

#include "gamestate.h"

class Game 
{
public:
	Game( GameState* pStartState )
		: m_cur_game(pStartState)
		, m_ai_givein(false)
		{}
	virtual ~Game(){}

	void Start();
	void NextMove();
	bool HasEnd();

	void AIMove();
	void PlayerMove();

	void PrintResult();

private:
	GameState* m_cur_game;
	OneShot m_last_shot;

	bool m_ai_givein;
};

#endif