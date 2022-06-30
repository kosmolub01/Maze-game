#ifndef _MENU_H_
#define _MENU_H_
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "PlayersRanking.h"

class Menu		//Main menu with options: "Play", "Show the player standings", "Help", "Exit"
{
public:
	Menu(sf::RenderWindow* window);
	~Menu();

	void show();	//Shows menu and handles user actions
	void move_up();	//Navigate through the menu 
	void move_down();	//Navigate through the menu 
	int get_selected_option_index();
	float text_position_offset(sf::Text, float window_width); //Computes, how big offset on x axis should be, in order to position text centrally
	void show_help();	//Prints out game help in console 

protected:
	sf::RenderWindow* window;
	std::vector<sf::Text> options;		//Collection of menu options labels
	int selected_option_index;
	sf::Font font;
	int number_of_options;
private:
	PlayersRanking* players_ranking;
};

#endif // !_MENU_H_
