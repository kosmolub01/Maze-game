#include "Room.h"

Room::Room(int room_no)
{
	room_number = room_no;
	visited = false;
}

MapSite* Room::get_side(Direction d) const
{
	return sides[static_cast<int>(d)];
}

void Room::set_side(Direction d, MapSite* s)
{
	sides[static_cast<int>(d)] = s;
}

int Room::get_room_number()
{
	return room_number;
}

bool Room::Enter()
{
	return true;
}

void Room::draw(sf::RenderWindow& window, Direction d)
{
	
}

void Room::set_visited()
{
	this->visited = true;
}

bool Room::get_visited()
{
	return this->visited;
}

std::string Room::type_info()
{
	return "class Room";
}