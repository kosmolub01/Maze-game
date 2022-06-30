#include "Menu.h"

int main()
{
	Menu menu(new sf::RenderWindow(sf::VideoMode(400, 422), "Maze game", sf::Style::Close | sf::Style::Titlebar));
	
	menu.show();	//Program starts with showing up the menu

	return 0;
}