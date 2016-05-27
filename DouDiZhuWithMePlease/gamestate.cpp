#include "gamestate.h"
#include <iostream>
#include <map>

bool OneShot::CalSelfType() // �������д��ʵ���Ǽ򵥴ֱ�����������
{
	if( vec_card.empty() )
	{
		return false;
	}
	else if( vec_card.size() == 1 )
	{
		shottype = ShotType_single;
		return true;
	}
	else if( vec_card.size() == 2 )
	{
		if( vec_card[1] == vec_card[0] )
		{
			shottype = ShotType_double;
			return true;
		}
		else
		{
			return false;
		}
	}
	else if( vec_card.size() == 3 )
	{
		if( vec_card[0] == vec_card[1] && vec_card[1] == vec_card[2] )
		{
			shottype = ShotType_three;
			return true;
		}
		else
		{
			return false;
		}
	}
	else if( vec_card.size() == 4 )
	{
		if( vec_card[0] == vec_card[1] && vec_card[1] == vec_card[2] && vec_card[2] == vec_card[3] && vec_card[3] == vec_card[4] )
		{
			shottype = ShotType_four;
			return true;
		}
		else
		{
			std::map< int, int > cardCount;
			for( auto it = vec_card.begin(); it != vec_card.end(); ++it )
			{
				if( cardCount.find( it->num ) == cardCount.end() )
				{
					cardCount[it->num] = 1;
				}
				else
				{
					++ cardCount[it->num];
				}
			}

			vec_card.clear();
			if( cardCount.size() == 2 )
			{
				auto it_1 = cardCount.begin()->first;
				auto it_2 = (++cardCount.begin())->first;
				if( cardCount.begin()->second == 1 )
				{
					vec_card.push_back( Card(it_2, Card::SuitType_clubs ) );
					vec_card.push_back( Card(it_2, Card::SuitType_clubs ) );
					vec_card.push_back( Card(it_2, Card::SuitType_clubs ) );
					vec_card.push_back( Card(it_1, Card::SuitType_clubs ) );
				}
			}
			shottype = ShotType_three_and_one;
			return true;
		}
	}
}

std::vector< OneShot > Player::GenerateShot_all_shift()
{
	std::vector< OneShot::ShotType > vec_shottype;
	vec_shottype.push_back( OneShot::ShotType_double );
	vec_shottype.push_back( OneShot::ShotType_single );
	vec_shottype.push_back( OneShot::ShotType_three );
	vec_shottype.push_back( OneShot::ShotType_three_and_one );
	vec_shottype.push_back( OneShot::ShotType_four );
	vec_shottype.push_back( OneShot::ShotType_twoKing );

	std::vector< OneShot > vec_shot;
	for( auto it = vec_shottype.begin(); it != vec_shottype.end(); ++it )
	{
		auto new_vec = GenerateShot_one_shift_byType( *it );
		vec_shot.insert( vec_shot.end(), new_vec.begin(), new_vec.end() );
	}

	return vec_shot;
}

std::vector< OneShot > Player::GenerateShot_all_space( OneShot lastShot )
{
	std::vector< OneShot::ShotType > vec_shottype;
	vec_shottype.push_back( OneShot::ShotType_double );
	vec_shottype.push_back( OneShot::ShotType_single );
	vec_shottype.push_back( OneShot::ShotType_three );
	vec_shottype.push_back( OneShot::ShotType_three_and_one );
	vec_shottype.push_back( OneShot::ShotType_four );
	vec_shottype.push_back( OneShot::ShotType_twoKing );

	std::vector< OneShot > vec_shot;
	for( auto it = vec_shottype.begin(); it != vec_shottype.end(); ++it )
	{
		auto new_vec = GenerateShot_one_space_byType( *it, lastShot );
		vec_shot.insert( vec_shot.end(), new_vec.begin(), new_vec.end() );
	}

	return vec_shot;
}

std::vector< OneShot > Player::GenerateShot_one_shift_byType( OneShot::ShotType st )
{
	std::vector< OneShot > vec_res;

	switch( st )
	{
	case OneShot::ShotType_single:
		{
			for( auto it = m_vec_card.begin(); it != m_vec_card.end(); ++it )
			{
				OneShot shot;
				shot.vec_card.push_back( *it );
				shot.shottype = OneShot::ShotType_single;

				vec_res.push_back( shot );
			}
			return vec_res;
		}

	case OneShot::ShotType_double:
		{
			for( auto it = m_vec_card.begin(); it != m_vec_card.end(); ++it )
			{
				if( std::find(it+1, m_vec_card.end(), *it) != m_vec_card.end() )
				{
					OneShot shot;
					shot.vec_card.push_back( *it );
					shot.vec_card.push_back( *it );
					shot.shottype = OneShot::ShotType_double;

					vec_res.push_back(shot);
				}
			}
			return vec_res;
		}

	case OneShot::ShotType_three:
		{
			for( auto it = m_vec_card.begin(); it != m_vec_card.end(); ++it )
			{
				int count = 0;
				for( auto it_find = it + 1; it_find != m_vec_card.end(); ++it_find )
				{
					if( *it_find == *it )
					{
						++count;
					}
				}
				if( count >= 3 )
				{
					OneShot shot;
					shot.vec_card.push_back( *it );
					shot.vec_card.push_back( *it );
					shot.vec_card.push_back( *it );
					shot.shottype = OneShot::ShotType_three;

					vec_res.push_back( shot );
				}
			}
			return vec_res;
		}

	case OneShot::ShotType_three_and_one:
		{
			for( auto it = m_vec_card.begin(); it != m_vec_card.end(); ++it )
			{
				int count = 0;
				for( auto it_find = it + 1; it_find != m_vec_card.end(); ++it_find )
				{
					if( *it_find == *it )
					{
						++count;
					}
				}
				if( count >= 3 )
				{
					for( auto it_find_another = m_vec_card.begin(); it_find_another != m_vec_card.end(); ++it_find_another )
					{
						if( *it_find_another != *it )
						{
							OneShot shot;
							shot.vec_card.push_back( *it );
							shot.vec_card.push_back( *it );
							shot.vec_card.push_back( *it );
							shot.vec_card.push_back(*it_find_another);
							shot.shottype = OneShot::ShotType_three_and_one;

							vec_res.push_back( shot );
						}
					}
				}
			}
			return vec_res;
		}

	case OneShot::ShotType_four:
		{
			for( auto it = m_vec_card.begin(); it != m_vec_card.end(); ++it )
			{
				int count = 0;
				for( auto it_find = it + 1; it_find != m_vec_card.end(); ++it_find )
				{
					if( *it_find == *it )
					{
						++count;
					}
				}
				if( count >= 4 )
				{
					OneShot shot;
					shot.vec_card.push_back( *it );
					shot.vec_card.push_back( *it );
					shot.vec_card.push_back( *it );
					shot.vec_card.push_back( *it );
					shot.shottype = OneShot::ShotType_four;

					vec_res.push_back( shot );
				}
			}
			return vec_res;
		}
	}
	return vec_res;
}

std::vector< OneShot > Player::GenerateShot_one_space_byType( OneShot::ShotType st, OneShot lastShot )
{
	std::vector< OneShot > vec_res;

	switch( lastShot.shottype )
	{
	case OneShot::ShotType_single:
		{
			for( auto it = m_vec_card.begin(); it != m_vec_card.end(); ++it )
			{
				if( *it > lastShot.vec_card[0] )
				{
					OneShot shot;
					shot.vec_card.push_back( *it );
					shot.shottype = OneShot::ShotType_single;

					vec_res.push_back( shot );
				}
			}
			return vec_res;
		}

	case OneShot::ShotType_double:
		{
			for( auto it = m_vec_card.begin(); it != m_vec_card.end(); ++it )
			{
				if( *it > lastShot.vec_card[0] )
				{
					if( std::find(it+1, m_vec_card.end(), *it) != m_vec_card.end() )
					{
						OneShot shot;
						shot.vec_card.push_back( *it );
						shot.vec_card.push_back( *it );
						shot.shottype = OneShot::ShotType_double;

						vec_res.push_back(shot);
					}
				}
			}
			return vec_res;
		}

	case OneShot::ShotType_three:
		{
			for( auto it = m_vec_card.begin(); it != m_vec_card.end(); ++it )
			{
				if( *it > lastShot.vec_card[0] )
				{
					int count = 0;
					for( auto it_find = it + 1; it_find != m_vec_card.end(); ++it_find )
					{
						if( *it_find == *it )
						{
							++count;
						}
					}
					if( count >= 3 )
					{
						OneShot shot;
						shot.vec_card.push_back( *it );
						shot.vec_card.push_back( *it );
						shot.vec_card.push_back( *it );
						shot.shottype = OneShot::ShotType_three;

						vec_res.push_back( shot );
					}
				}
			}
			return vec_res;
		}

	case OneShot::ShotType_three_and_one:
		{
			for( auto it = m_vec_card.begin(); it != m_vec_card.end(); ++it )
			{
				if( *it > lastShot.vec_card[0] )
				{
					int count = 0;
					for( auto it_find = it + 1; it_find != m_vec_card.end(); ++it_find )
					{
						if( *it_find == *it )
						{
							++count;
						}
					}
					if( count >= 3 )
					{
						for( auto it_find_another = m_vec_card.begin(); it_find_another != m_vec_card.end(); ++it_find_another )
						{
							if( *it_find_another != *it )
							{
								OneShot shot;
								shot.vec_card.push_back( *it );
								shot.vec_card.push_back( *it );
								shot.vec_card.push_back( *it );
								shot.vec_card.push_back(*it_find_another);
								shot.shottype = OneShot::ShotType_three_and_one;

								vec_res.push_back( shot );
							}
						}
					}
				}
			}
			return vec_res;
		}

	case OneShot::ShotType_four:
		{
			for( auto it = m_vec_card.begin(); it != m_vec_card.end(); ++it )
			{
				if( *it > lastShot.vec_card[0] )
				{
					int count = 0;
					for( auto it_find = it + 1; it_find != m_vec_card.end(); ++it_find )
					{
						if( *it_find == *it )
						{
							++count;
						}
					}
					if( count >= 4 )
					{
						OneShot shot;
						shot.vec_card.push_back( *it );
						shot.vec_card.push_back( *it );
						shot.vec_card.push_back( *it );
						shot.vec_card.push_back( *it );
						shot.shottype = OneShot::ShotType_four;

						vec_res.push_back( shot );
					}
				}
			}
			return vec_res;
		}
	}

	return vec_res;
}

OneShot GameState::DecideAndMove()
{
	GenerateChildren();
	for( auto it = m_vec_children.begin(); it != m_vec_children.end(); ++it )
	{
		if( (*it)->isUseful() )
		{
			return (dynamic_cast<GameState*>(*it))->lastShot;
		}
	}
	return OneShot();
}

void GameState::GenerateChildren()
{
	// ����Ƿ������Ѿ���������
	if( CheckGameEnd() )
	{
		return;
	}

	// ��ǰ�����ߺͽ�����
	Player* p_cur_player = isYgrittesPlaying ? &Ygritte : &JonSnow;
	Player* p_another_player = !isYgrittesPlaying ? &Ygritte : &JonSnow;

	// ��ͼ�ý����߳���
	std::vector< OneShot > vec_new_shot;
	
	if( lastShot.vec_card.empty() ) // ˵���ǿ���
	{
		vec_new_shot = p_another_player->GenerateShot_all_shift();		// ������ѡ�����г��Ʒ���
	}
	else							 // ���ǿ���
	{
		vec_new_shot = p_another_player->GenerateShot_all_space( lastShot );
	}

	bool nextIsYgritte;
	Player* newPlayer = NULL;

	if( vec_new_shot.empty() )
	{	// ���������ƿɳ�
		vec_new_shot = p_cur_player->GenerateShot_all_shift();		// ������ѡ�����г��Ʒ���
		nextIsYgritte = isYgrittesPlaying;								// ���л�������
		newPlayer = p_cur_player;
	}
	else
	{	// ���������ƿɳ�
		nextIsYgritte = !isYgrittesPlaying;								// �л�������
		newPlayer = p_another_player;
	}

	// �������г��Ʒ��������ɺ���
	for( auto it_shot = vec_new_shot.begin(); it_shot != vec_new_shot.end(); ++it_shot )
	{
		GameState* child = GetNewChild( *it_shot, nextIsYgritte );
		child->GenerateChildren();
		AddChildren( child );

		//if( child->isAlreadyMinMax() )
		//{
		//	break;
		//}
	}

	// �������к��ӣ���õ�ǰ���������Сֵ
	if( m_isNeedAllMax )
	{
		m_curIsMax = true;
		for( auto it_child = m_vec_children.begin(); it_child != m_vec_children.end(); ++it_child )
		{
			m_curIsMax = m_curIsMax && (*it_child)->m_curIsMax;
		}
	}
	else
	{
		m_curIsMax = false;
		for( auto it_child = m_vec_children.begin(); it_child != m_vec_children.end(); ++it_child )
		{
			m_curIsMax = m_curIsMax || (*it_child)->m_curIsMax;
		}
	}

}

GameState* GameState::GetNewChild( OneShot shot, bool isYgrittesPlaying )
{
	GameState* child = new GameState();
	if( isYgrittesPlaying )
	{
		child->Ygritte = Ygritte - shot;
		child->JonSnow = JonSnow;
	}
	else
	{
		child->Ygritte = Ygritte;
		child->JonSnow = JonSnow - shot;
	}
	child->isYgrittesPlaying = isYgrittesPlaying;
	child->m_isNeedAllMax = !isYgrittesPlaying;
	child->lastShot = shot;

	return child;
}

bool GameState::CheckGameEnd()
{
	if( Ygritte.m_vec_card.empty() )
	{
		m_curIsMax = true;
		return true;
	}
	else if( JonSnow.m_vec_card.empty() )
	{
		m_curIsMax = false;
		return true;
	}
	else
	{
		return false;
	}
}

void GameState::Print()
{
	std::cout<<" ---- ���γ��ƣ� "<<( isYgrittesPlaying ? "Ygritte" : "JonSnow" )<<std::endl;
	std::cout<<"lastShot: "<<std::endl;
	lastShot.Print();
	std::cout<<"Ygritte: "<<std::endl;
	Ygritte.Print();
	std::cout<<"JonSnow: "<<std::endl;
	JonSnow.Print();
	std::cout<<" ---- ���ƽ��� ---- "<<std::endl<<std::endl;;
}