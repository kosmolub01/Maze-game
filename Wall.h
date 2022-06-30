#ifndef _WALL_H_
#define _WALL_H_

#include "Mapsite.h"

class Wall : public MapSite
{
public:
	Wall();

	bool Enter();
	void draw(sf::RenderWindow& window, Direction d);
	std::string type_info();
};

#endif // !_WALL_H_