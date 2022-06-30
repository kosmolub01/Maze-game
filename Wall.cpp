#include "Wall.h"

Wall::Wall() {};

bool Wall::Enter()
{
	return false;
}

void Wall::draw(sf::RenderWindow& window, Direction d)
{
	sf::RectangleShape shape;

	shape.setSize(sf::Vector2f(400, 50));
	shape.setFillColor(sf::Color::Green);
	
	switch (d)	//Seems like a lot of hard-coded values!
	{
	case Direction::North:

		shape.setPosition(sf::Vector2f(0, 22));

		break;

	case Direction::East:

		shape.setPosition(sf::Vector2f(400, 22));
		shape.rotate(90);

		break;

	case Direction::South:

		shape.setPosition(sf::Vector2f(0, 372));

		break;

	case Direction::West:

		shape.setPosition(sf::Vector2f(50, 22));
		shape.rotate(90);

		break;
	}

	window.draw(shape);
}

std::string Wall::type_info()
{
	return "class Wall";
}