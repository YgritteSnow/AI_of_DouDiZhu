#include "game.h"
#include <iostream>
#include <sstream>

void Game::Start()
{
	std::cout<<" --- 游戏开始 ---"<<std::endl;
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
	std::cout<<" --- AI 思考中 --- "<<std::endl;
	m_last_shot = m_cur_game->DecideAndMove();
	if( m_last_shot.vec_card.empty() )
	{
		m_ai_givein = true;
		std::cout<<" AI 没有必胜把握！投降了！"<<std::endl;
	}
	else
	{
		std::cout<<"AI 出牌："<<std::endl;
		m_last_shot.Print();
		std::cout<<"当前牌局："<<std::endl;
		m_cur_game->Print();
	}
	std::cout<<" --- AI 完成 --- "<<std::endl;
}

void Game::PlayerMove()
{
	std::cout<<" --- 玩家回合开始 --- "<<std::endl;
	while( true )
	{
		std::cout<<"输入你要出的牌，空格键隔开，回车键确认："<<std::endl;
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

	std::cout<<" --- 玩家回合结束 --- "<<std::endl;
}

void Game::PrintResult()
{
	std::cout<<" --- 游戏结束 --- "<<std::endl;
	if( m_ai_givein )
	{
		std::cout<<"AI认输"<<std::endl;
	}
	else
	{
		if( m_cur_game->m_curIsMax )
		{
			std::cout<<"AI赢了"<<std::endl;
		}
		else
		{
			std::cout<<"你赢了"<<std::endl;
		}
	}
}