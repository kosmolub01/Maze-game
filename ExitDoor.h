#ifndef _EXITDOOR_H_
#define _EXITDOOR_H_

#include "Mapsite.h"
#include "Room.h"

class ExitDoor : public MapSite
{
public:
	ExitDoor(Room* r);	

	bool Enter();
	void draw(sf::RenderWindow& window, Direction d);
	std::string type_info();

private:
	Room* room;
	//bool is_open;
};

#endif // !_EXITDOOR_H_

