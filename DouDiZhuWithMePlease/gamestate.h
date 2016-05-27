#ifndef __F__MYPROJECTS_DOUDIZHUWITHMEPLEASE__DOUDIZHUWITHMEPLEASE_GAMESTATE_H__
#define __F__MYPROJECTS_DOUDIZHUWITHMEPLEASE__DOUDIZHUWITHMEPLEASE_GAMESTATE_H__

#include <vector>
#include <string>
#include <algorithm>
#include "minmaxtree.h"
#include <iostream>

struct Card
{
	enum SuitType {
		SuitType_spades, 
		SuitType_diamonds, 
		SuitType_clubs, 
		SuitType_hearts, 
	};
	Card(int n, SuitType s):num(n), suit(s){}
	int num;
	SuitType suit;

	bool isKing(){return num == 14;}
	bool operator==(const Card& c){
		return num == c.num && suit == c.suit;
	}
	bool operator!=(const Card& c){
		return num != c.num || suit != c.suit;
	}
	bool operator > (const Card& c){
		return num > c.num;
	}
	bool operator < (const Card& c){
		return num < c.num;
	}

	void Print(){
		std::cout<<num;
	}
};

struct OneShot
{
	enum ShotType {
		ShotType_single, 
		ShotType_double,
		ShotType_three, 
		ShotType_three_and_one, 
		ShotType_four, 
		ShotType_twoKing, 
	} shottype;
	std::vector< Card > vec_card;

	void Print(){
		for( auto it = vec_card.begin(); it != vec_card.end(); ++it )
		{
			it->Print();
			std::cout<<"  ";
		}
		std::cout<<std::endl;
	}
};

class Player
{
public:
	std::vector< Card > m_vec_card;

	std::vector< OneShot > GenerateShot_all_shift();
	std::vector< OneShot > GenerateShot_one_shift_byType( OneShot::ShotType st );
	std::vector< OneShot > GenerateShot_all_space( OneShot lastShot );
	std::vector< OneShot > GenerateShot_one_space_byType( OneShot::ShotType st, OneShot lastShot );

	const Player operator-( OneShot shot ) const {
		Player res( *this );
		for( auto it = shot.vec_card.begin(); it != shot.vec_card.end(); ++it )
		{
			auto find_it = std::find( res.m_vec_card.begin(), res.m_vec_card.end(), *it );
			if( find_it != res.m_vec_card.end() )
			{
				res.m_vec_card.erase( find_it );
			}
		}
		return res;
	}

	void Print(){
		for( auto it = m_vec_card.begin(); it != m_vec_card.end(); ++it )
		{
			it->Print();
			std::cout<<"  ";
		}
		std::cout<<std::endl;
	}
};

class GameState : public MinMaxTreeNodeBase
{
public:
	virtual void GenerateChildren();
	virtual void Print();

	GameState* GetNewChild( OneShot shot, bool isYgrittesPlaying );
	bool CheckGameEnd();

	Player Ygritte;
	Player JonSnow;
	OneShot lastShot;
	bool isYgrittesPlaying;
};

class GameStateTree : public DecidingTree< GameState >
{
public:
	GameStateTree( std::vector<Card> pGS1, std::vector<Card> pGS2, bool isp11Turn )
	{
		m_root = new GameState();

		int i = -1;
		while( ++i != pGS1.size() )
		{
			m_root->Ygritte.m_vec_card.push_back( pGS1[i] );
		}

		i = -1;
		while( ++i != pGS2.size() )
		{
			m_root->JonSnow.m_vec_card.push_back( pGS2[i] );
		}

		m_root->isYgrittesPlaying = isp11Turn;
	}
	~GameStateTree(){};
};
#endif 
