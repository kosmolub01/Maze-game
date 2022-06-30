#include "Map.h"

Map::Map(sf::RenderWindow* window)
{
	this->window = window;

	tile_size = 50;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			shape[(i * 10) + j].setSize(sf::Vector2f(tile_size, tile_size));
			shape[(i * 10) + j].setPosition(sf::Vector2f(tile_size * j, tile_size * i));
			shape[(i * 10) + j].setFillColor(sf::Color(0, 0, 255, 100));
			shape[(i * 10) + j].setOutlineThickness(-1);
			shape[(i * 10) + j].setOutlineColor(sf::Color::Black);		
		}
	}
}

Map::~Map()
{

}

sf::RenderWindow* Map::get_window()
{
	return this->window;
}

void Map::draw(Maze* maze, int current_room_no)
{
	if (this->current_room_no != current_room_no)	//Changing colour of current room to yellow
	{
		shape[this->current_room_no].setFillColor(sf::Color::Blue);

		this->current_room_no = current_room_no;

		shape[this->current_room_no].setFillColor(sf::Color::Yellow);
	}

	for (int i = 0; i < 10; i++)	//Drawing the whole maze on the map
	{
		for (int j = 0; j < 10; j++)
		{
			if (maze->room((i * 10) + j) != nullptr)
			{
				if (maze->room((i * 10) + j)->get_visited() && maze->room((i * 10) + j)->get_room_number() != current_room_no)
				{
					shape[(i * 10) + j].setFillColor(sf::Color::Blue);
				}
			}

			window->draw(shape[(i * 10) + j]);
		}
	}
}