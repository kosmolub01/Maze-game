#include "Maze.h"

Maze::Maze(float time_limit)
{
	this->time_limit = time_limit;
	rooms.resize(100);

	for (auto i : rooms)
	{
		i = nullptr;
	}
}

/*Maze::~Maze() 
{

}*/


void Maze::add_room(Room* r)
{
	rooms[r->get_room_number()] = r;
}

Room* Maze::room(int room_no) const
{
	return rooms[room_no];
}

void  Maze::set_time_limit(float time_limit)
{
	this->time_limit = time_limit;
}

float  Maze::get_time_limit()
{
	return time_limit;
}

void Maze::draw(sf::RenderWindow& window, Room* current_room)
{
	current_room->get_side(Direction::North)->draw(window, Direction::North);
	current_room->get_side(Direction::East)->draw(window, Direction::East);
	current_room->get_side(Direction::South)->draw(window, Direction::South);
	current_room->get_side(Direction::West)->draw(window, Direction::West);
}