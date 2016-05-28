#ifndef __F__MYPROJECTS_UDIZHUWITHMEPLEASE__DOUDIZHUWITHMEPLEASE_MINMAXTREE_H__
#define __F__MYPROJECTS_UDIZHUWITHMEPLEASE__DOUDIZHUWITHMEPLEASE_MINMAXTREE_H__

#include "gamestate.h"

class Game 
{
public:
	Game( std::vector<Card> pGS1, std::vector<Card> pGS2, bool isp11Turn )
		: m_ai_givein(false)
	{
		m_cur_game = new GameState( pGS1, pGS2, isp11Turn );
	}
	virtual ~Game()
	{
		DEBUG_TRACE_FUNC("Game");
		delete m_cur_game;
		m_cur_game = NULL;
		DEBUG_TRACE_FUNC("Game");
	}

	void Start();
	void NextMove();
	bool HasEnd();

	OneShot AIMove();
	OneShot PlayerMove();

	void PrintResult();
	void PrintCurrentState();
private:
	GameState* m_cur_game;
	OneShot m_last_shot;

	bool m_ai_givein;
};

#endif