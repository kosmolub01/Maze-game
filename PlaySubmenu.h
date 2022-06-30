#ifndef _PLAYSUBMENU_H_
#define _PLAYSUBMENU_H_

#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Menu.h"
#include "SelectPlayer.h"
#include "PlayersRanking.h"

class PlaySubmenu : public Menu		//Submenu in which player can choose the maze
{
public:
	PlaySubmenu(sf::RenderWindow* window);
	~PlaySubmenu();

	void show(PlayersRanking* players_ranking);	//Shows submenu and handles user actions
};

#endif // !_PLAYSUBMENU_H_
