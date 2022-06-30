#include "Door.h"

Door::Door(Room* r1, Room* r2)
{
	room1 = r1;
	room2 = r2;
}

bool Door::Enter()	//Ewentualne sprawdzenie, czy gracz ma klucz do drzwi
{
	return true;
}

void Door::draw(sf::RenderWindow& window, Direction d)
{
	sf::RectangleShape wall, door;	//Wall is the background of the door

	wall.setSize(sf::Vector2f(400, 50));
	wall.setFillColor(sf::Color::Green);

	door.setSize(sf::Vector2f(120, 50));
	door.setFillColor(sf::Color::Red);

	switch (d)	//Seems like a lot of hard-coded values!
	{
	case Direction::North:

		wall.setPosition(sf::Vector2f(0, 22));

		door.setPosition(sf::Vector2f(140, 22));

		break;

	case Direction::East:

		wall.setPosition(sf::Vector2f(400, 72));
		wall.rotate(90);

		door.setPosition(sf::Vector2f(400, 162));
		door.rotate(90);

		break;

	case Direction::South:

		wall.setPosition(sf::Vector2f(0, 372));

		door.setPosition(sf::Vector2f(140, 372));

		break;

	case Direction::West:

		wall.setPosition(sf::Vector2f(50, 72));
		wall.rotate(90);

		door.setPosition(sf::Vector2f(50, 162));
		door.rotate(90);
	}

	window.draw(wall);
	window.draw(door);
}

Room* Door::other_side_from(Room* r)	//Useless
{
	if (r == room1)
	{
		return room2;
	}
	else if (r == room2)
	{
		return room1;
	}
	else
	{
		return room1;
		//error
	}
}

std::string Door::type_info()
{
	return "class Door";
}