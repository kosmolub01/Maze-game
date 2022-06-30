#ifndef _MAP_H_
#define _MAP_H_

#include <SFML/Graphics.hpp>
#include "Maze.h"

class Map
{
public:
	Map(sf::RenderWindow* window);
	virtual ~Map();	

	sf::RenderWindow* get_window();

	void draw(Maze* maze, int current_room_no);

private:
	sf::RenderWindow* window;
	sf::RectangleShape shape [100];
	int tile_size = 10;
	int current_room_no = -1; //Set to -1, because leaving it with no default value (current_room_no = 0), would compromise proper current room indication on map
};

#endif // !_MAP_H_
