#ifndef _ROOM_H_
#define _ROOM_H_

#include "Mapsite.h"

class Room : public MapSite
{
public:
	Room(int room_no);

	MapSite* get_side(Direction d) const;
	void set_side(Direction d, MapSite* s);
	int get_room_number();

	bool Enter();
	void draw(sf::RenderWindow& window, Direction d);
	void set_visited();
	bool get_visited();
	std::string type_info();

private:
	MapSite* sides[4];
	int room_number;
	bool visited;
};

#endif // !_ROOM_H_