#ifndef _DOOR_H_
#define _DOOR_H_

#include "Mapsite.h"
#include "Room.h"

class Door : public MapSite
{
public:
	Door(Room* r1, Room* r2);	

	bool Enter();	//Alternatively, player sends collection of keys. Function checks, if door are closed and if player has proper key
	void draw(sf::RenderWindow& window, Direction d);
	Room* other_side_from(Room* r);
	std::string type_info();

private:
	Room* room1;
	Room* room2;
	//bool is_open;
};
 
#endif // !_DOOR_H_