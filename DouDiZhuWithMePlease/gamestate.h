#ifndef __F__MYPROJECTS_DOUDIZHUWITHMEPLEASE__DOUDIZHUWITHMEPLEASE_GAMESTATE_H__
#define __F__MYPROJECTS_DOUDIZHUWITHMEPLEASE__DOUDIZHUWITHMEPLEASE_GAMESTATE_H__

#include <vector>
#include <string>
#include <algorithm>
#include "minmaxtree.h"
#include <iostream>
#include "quick_micros.h"

struct Card
{
	enum SuitType {
		SuitType_spades, 
		SuitType_diamonds, 
		SuitType_clubs, 
		SuitType_hearts, 
	};
	Card(int n, SuitType s):num(n), suit(s){}
	Card( const Card& c ):num(c.num), suit(c.suit){}

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
	~OneShot(){
		DEBUG_TRACE_FUNC("OneShot");}
	OneShot():shottype(ShotType_null){};
	OneShot( const OneShot& c ):shottype(c.shottype){
		vec_card.clear();
		for( auto it = c.vec_card.begin(); it != c.vec_card.end(); ++it )
		{
			vec_card.push_back( Card( it->num, it->suit ) );
		}
	}

	enum ShotType {
		ShotType_null,
		ShotType_single, 
		ShotType_double,
		ShotType_three, 
		ShotType_three_and_one, 
		ShotType_four, 
		ShotType_twoKing, 
	} shottype;
	std::vector< Card > vec_card;

	bool IsHigher( const OneShot s ) const {
		if( s.Empty() )
		{
			return true;
		}

		if( Empty() )
		{
			return false;
		}

		if( shottype != s.shottype )
		{
			return false;
		}

		return vec_card[0].num > s.vec_card[0].num;
	}

	void Print(){
		for( auto it = vec_card.begin(); it != vec_card.end(); ++it )
		{
			it->Print();
			std::cout<<"  ";
		}
		std::cout<<std::endl;
	}
	
	bool Empty() const {
		return vec_card.empty();
	}

	bool CalSelfType();
};

class Player
{
public:
	~Player(){
		DEBUG_TRACE_FUNC("Player");}
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

	const Player operator-=( OneShot shot ) {
		for( auto it = shot.vec_card.begin(); it != shot.vec_card.end(); ++it )
		{
			auto find_it = std::find( m_vec_card.begin(), m_vec_card.end(), *it );
			if( find_it != m_vec_card.end() )
			{
				m_vec_card.erase( find_it );
			}
		}
		return *this;
	}

	bool isValidShot( OneShot shot ) const {
		Player res( *this );
		for( auto it = shot.vec_card.begin(); it != shot.vec_card.end(); ++it )
		{
			auto find_it = std::find( res.m_vec_card.begin(), res.m_vec_card.end(), *it );
			if( find_it != res.m_vec_card.end() )
			{
				res.m_vec_card.erase( find_it );
			}
			else
			{
				return false;
			}
		}
		return true;
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
	GameState(){};
	GameState( std::vector<Card> pGS1, std::vector<Card> pGS2, bool isp11Turn )
	{
		int i = -1;
		while( ++i != pGS1.size() )
		{
			Ygritte.m_vec_card.push_back( pGS1[i] );
		}

		i = -1;
		while( ++i != pGS2.size() )
		{
			JonSnow.m_vec_card.push_back( pGS2[i] );
		}
		isYgrittesPlaying = isp11Turn;
		m_isNeedAllMax = !isYgrittesPlaying;
		
	}
	virtual ~GameState(){
		DEBUG_TRACE_FUNC("GameState");
	}
	bool ThinkForNextMove( OneShot& shot );
	virtual void GenerateChildren();
	virtual void Print();
	void Move( OneShot shot );
	bool CheckGameEnd();

	bool isYgrittesPlaying;
	Player JonSnow;
	OneShot lastShot;

private:
	void CheckChildMinMax();

	GameState* GetNewChild( OneShot shot, bool isYgrittesPlaying );

	Player Ygritte;
};

#endif 
