#ifndef _MAZE_H_
#define _MAZE_H_

#include <vector>
#include "Room.h"

class Maze
{
public:
	Maze(float time_limit = 0);
	~Maze() {};

	void add_room(Room*);
	Room* room(int room_no) const;
	void set_time_limit(float time_limit);
	float get_time_limit();
	void draw(sf::RenderWindow& window, Room* current_room);

private:
	std::vector<Room*> rooms;	
	float time_limit = 0;	//In seconds
};


#endif // !_MAZE_H_