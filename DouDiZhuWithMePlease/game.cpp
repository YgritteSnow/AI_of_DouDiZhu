#include "game.h"
#include <iostream>
#include <sstream>

void Game::Start()
{
	std::cout<<" --- ��Ϸ��ʼ ---"<<std::endl;
	m_ai_givein = false;
}

void Game::NextMove()
{
	if( m_cur_game->isYgrittesPlaying )
	{
		AIMove();
	}
	else
	{
		PlayerMove();
	}
}

bool Game::HasEnd()
{
	return m_ai_givein || m_cur_game->CheckGameEnd();
}

void Game::AIMove()
{
	std::cout<<" --- AI ˼���� --- "<<std::endl;
	m_last_shot = m_cur_game->DecideAndMove();
	if( m_last_shot.vec_card.empty() )
	{
		m_ai_givein = true;
		std::cout<<" AI û�б�ʤ���գ�Ͷ���ˣ�"<<std::endl;
	}
	else
	{
		std::cout<<"AI ���ƣ�"<<std::endl;
		m_last_shot.Print();
		std::cout<<"��ǰ�ƾ֣�"<<std::endl;
		m_cur_game->Print();
	}
	std::cout<<" --- AI ��� --- "<<std::endl;
}

void Game::PlayerMove()
{
	std::cout<<" --- ��һغϿ�ʼ --- "<<std::endl;
	while( true )
	{
		std::cout<<"������Ҫ�����ƣ��ո���������س���ȷ�ϣ�"<<std::endl;
		m_last_shot.vec_card.clear();

		std::string playerStr;
		getline( std::cin, playerStr );

		std::stringstream strStream(playerStr);
		int c;
		while( strStream>> c )
		{
			m_last_shot.vec_card.push_back( Card( c, Card::SuitType_clubs ) );
		}
		if( m_last_shot.CalSelfType() )
		{
			if( m_cur_game->JonSnow.isValidShot( m_last_shot ) )
			{
				break;
			}
		}
	}

	std::cout<<" --- ��һغϽ��� --- "<<std::endl;
}

void Game::PrintResult()
{
	std::cout<<" --- ��Ϸ���� --- "<<std::endl;
	if( m_ai_givein )
	{
		std::cout<<"AI����"<<std::endl;
	}
	else
	{
		if( m_cur_game->m_curIsMax )
		{
			std::cout<<"AIӮ��"<<std::endl;
		}
		else
		{
			std::cout<<"��Ӯ��"<<std::endl;
		}
	}
}