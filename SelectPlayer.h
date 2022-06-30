#ifndef _SELECTPLAYER_H_
#define _SELECTPLAYER_H_

#include "SFML/Graphics.hpp"
#include <regex>
#include <conio.h>
#include "Game.h"
#include "Menu.h"
#include "PlayersRanking.h"

class SelectPlayer : public Menu	//Submenu of PlaySubmenu in which player can select as who he is playing
{
public:
	SelectPlayer(sf::RenderWindow* window, PlayersRanking* players_ranking);
	~SelectPlayer();

	void show(int maze_no);	//Shows submenu and handles user actions
	void move_left();	
	void move_right();
	int add_new_player(); 



private:
	sf::Text info; //To tell the player what to do - "Select the player"
	PlayersRanking* players_ranking;
};

#endif // !_SELECTPLAYER_H_

