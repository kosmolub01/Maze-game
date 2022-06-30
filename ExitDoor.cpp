#include "ExitDoor.h"

ExitDoor::ExitDoor(Room* r)
{
	room = r;
}

bool ExitDoor::Enter()
{
	return true;
}

void ExitDoor::draw(sf::RenderWindow& window, Direction d)
{
	sf::RectangleShape wall, door;	//Wall is the background of the door

	wall.setSize(sf::Vector2f(400, 50));
	wall.setFillColor(sf::Color::Green);

	door.setSize(sf::Vector2f(120, 50));
	door.setFillColor(sf::Color::Blue);

	switch (d)	//Seems like a lot of hard-coded values!
	{
	case Direction::North:

		wall.setPosition(sf::Vector2f(50, 22));

		door.setPosition(sf::Vector2f(140, 22));

		break;

	case Direction::East:

		wall.setPosition(sf::Vector2f(400, 72));
		wall.rotate(90);

		door.setPosition(sf::Vector2f(400, 162));
		door.rotate(90);

		break;

	case Direction::South:

		wall.setPosition(sf::Vector2f(50, 372));

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

std::string ExitDoor::type_info()	//Not used - defined only to preserve consistency
{
	return "class ExitDoor";
}