#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SFML/Graphics.hpp>
#include "Direction.h"
#include "GameInfo.h"
#include "Room.h"
#include "Door.h"
#include "Maze.h"

class Player
{
public:
	Player(Maze* maze, Room* current_room, sf::Vector2u size);
	~Player();

	Room* get_current_room();
	void set_current_room(Room* r);
	void draw(sf::RenderWindow& window);
	void move(Direction d, GameInfo* game_info);	//Depending on the player actions, game state can change, so there is need to pass GameInfo pointer
private:
	Maze* maze;
	sf::RectangleShape shape;
	Room* current_room = 0;
	int grid_cell_no = 4;
};


#endif // !_PLAYER_H_
