#ifndef _RANKINGSUBMENU_H_
#define _RANKINGSUBMENU_H_

#include "Menu.h"

class RankingSubmenu : public Menu			//Submenu in which player can view the standings
{
public:
	RankingSubmenu(sf::RenderWindow* window);
	~RankingSubmenu();

	void show(PlayersRanking* players_ranking);	//Shows submenu and handles user actions
private:
	sf::Text info; //To tell the player what to do - "Select the standing"
};

#endif // !_RANKINGSUBMENU_H_