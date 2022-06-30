#ifndef _MAPSITE_H_
#define _MAPSITE_H_

#include <SFML/Graphics.hpp>
#include "Direction.h"

class MapSite
{
public:
	virtual bool Enter() = 0;	
	virtual void draw(sf::RenderWindow& window, Direction d) = 0;
	virtual std::string type_info() = 0;
};

#endif // !_MAPSITE_H_