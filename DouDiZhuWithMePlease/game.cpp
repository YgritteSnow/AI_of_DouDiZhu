#include "game.h"
#include <iostream>
#include <sstream>

void Game::Start()
{
	GAME_MSG_1("��Ϸ��ʼ");
	m_ai_givein = false;
	PrintCurrentState();
}

void Game::NextMove()
{
	if( m_cur_game->isYgrittesPlaying )
	{
		m_last_shot = AIMove();
	}
	else
	{
		m_last_shot = PlayerMove();
	}
	m_cur_game->Move( m_last_shot );
	PrintCurrentState();
}

bool Game::HasEnd()
{
	return m_ai_givein || m_cur_game->CheckGameEnd();
}

OneShot Game::AIMove()
{
	GAME_MSG_1("AI ˼����");
	OneShot shot;
	if( !m_cur_game->ThinkForNextMove( shot ) )
	{
		m_ai_givein = true;
	}
	return shot;
}

OneShot Game::PlayerMove()
{
	GAME_MSG_1("���ѡ�����");
	while( true )
	{
		std::cout<<"������Ҫ�����ƣ�0��ʾ����)���ո���������س���ȷ�ϣ�"<<std::endl;
		m_last_shot.vec_card.clear();

		std::string playerStr;
		getline( std::cin, playerStr );

		std::stringstream strStream(playerStr);
		int c;
		while( strStream>> c )
		{
			if( c == 0 )
			{
				m_last_shot = OneShot();
				return m_last_shot;
			}
			m_last_shot.vec_card.push_back( Card( c, Card::SuitType_clubs ) );
		}

		if( !m_last_shot.CalSelfType() )
		{
			GAME_MSG_2("�������ϣ�");
		}
		else if( !m_cur_game->JonSnow.isValidShot( m_last_shot ) )
		{
			GAME_MSG_2("û�������ƣ�");
		}
		else if( !m_last_shot.IsHigher(m_cur_game->lastShot) )
		{
			GAME_MSG_2("����ѹ���Է���");
		}
		else
		{
			return m_last_shot;
		}
		std::cout<<"���ƴ���������"<<std::endl;
	}
	return OneShot();
}

void Game::PrintCurrentState()
{
	m_cur_game->Print();
}

void Game::PrintResult()
{
	GAME_MSG_1("��Ϸ����");
	
	PrintCurrentState();

	if( m_ai_givein )
	{
		GAME_MSG_1("AI����");
	}
	else
	{
		if( m_cur_game->m_curIsMax )
		{
			GAME_MSG_1("AIӮ��");
		}
		else
		{
			GAME_MSG_1("��Ӯ��");
		}
	}
}