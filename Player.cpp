#include "Player.h"

Player::Player(Maze* maze, Room* current_room, sf::Vector2u size)
{
	this->maze = maze;

	this->current_room = current_room;

	current_room->set_visited();

	shape.setSize(sf::Vector2f(100, 100));
	shape.setOrigin(50.f, 50.f);
	shape.setPosition(sf::Vector2f((size.x/2), ((size.y / 2) + 11.5)));	//Set position in the centere of the window, and by adding 11.5 make space 
																		//for status bar
}


Player::~Player()
{
}

void Player::set_current_room(Room* r)
{
	current_room = r;
}

Room* Player::get_current_room()
{
	return current_room;
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Player::move(Direction d, GameInfo* game_info)
{
	switch (d)
	{
	case Direction::North:	//Moving up
		if (grid_cell_no < 3)	//If player is in the higher part of the grid
		{
			if (current_room->get_side(Direction::North)->type_info() == "class Door" || current_room->get_side(Direction::North)->type_info() == "class ExitDoor")	//If northern side is door
			{
				//Then check, if he can enter the door
				if (current_room->get_side(Direction::North)->Enter() && grid_cell_no == 1)//send keys
				{
					if (current_room->get_side(Direction::North)->type_info() == "class ExitDoor")
					{
						game_info->switch_finish_flag();
						return;
					}
					
					shape.move(sf::Vector2f(0, 200));
					grid_cell_no += 6;
					game_info->change_current_room_no(-10);
				}
				else 
				{
					//tell the player why he cannot access the door
				}
			}
			else if (current_room->get_side(Direction::North)->Enter())
			{
				shape.move(sf::Vector2f(0, 200));
				grid_cell_no += 6;
				game_info->change_current_room_no(-10);
			}
		}
		else //In any other case, player can move up with no other conditions
		{
			shape.move(sf::Vector2f(0, -100));
			grid_cell_no -= 3;
		}

		break;

	case Direction::East:	//Moving right
		if (grid_cell_no == 2 || grid_cell_no == 5 || grid_cell_no == 8)	//If player is in the right part of the grid
		{
			if (current_room->get_side(Direction::East)->type_info() == "class Door" || current_room->get_side(Direction::East)->type_info() == "class ExitDoor")	//If eastern side is door
			{
				//Then check, if he can enter the door
				if (current_room->get_side(Direction::East)->Enter() && grid_cell_no == 5)//Maybe send keys?
				{
					if (current_room->get_side(Direction::East)->type_info() == "class ExitDoor")
					{
						game_info->switch_finish_flag();
						return;
					}

					shape.move(sf::Vector2f(-200, 0));
					grid_cell_no -= 2;
					game_info->change_current_room_no(1);
				}
				else
				{
					//tell the player why he cannot access the door
				}
			}
			else if(current_room->get_side(Direction::East)->Enter()) //Not door
			{
				shape.move(sf::Vector2f(-200, 0));
				grid_cell_no -= 2;
				game_info->change_current_room_no(1);
			}
		}
		else //In any other case, player can move up with no other conditions
		{
			shape.move(sf::Vector2f(100, 0));
			grid_cell_no += 1;
		}

		break;

	case Direction::South:	//Moving down
		if (grid_cell_no > 5)	//If player is in the lower part of the grid
		{
			if (current_room->get_side(Direction::South)->type_info() == "class Door" || current_room->get_side(Direction::South)->type_info() == "class ExitDoor")	//If eastern side is door
			{
				//Then check, if he can enter the door
				if (current_room->get_side(Direction::South)->Enter() && grid_cell_no == 7)//send keys
				{
					if (current_room->get_side(Direction::South)->type_info() == "class ExitDoor")
					{
						game_info->switch_finish_flag();
						return;
					}

					shape.move(sf::Vector2f(0, -200));
					grid_cell_no -= 6;
					game_info->change_current_room_no(10);
				}
				else
				{
					//tell the player why he cannot access the door
				}
			}
			else if (current_room->get_side(Direction::South)->Enter()) //Not door
			{
				shape.move(sf::Vector2f(0, -200));
				grid_cell_no -= 6;
				game_info->change_current_room_no(10);
			}
		}
		else //In any other case, player can move up with no other conditions
		{
			shape.move(sf::Vector2f(0, 100));
			grid_cell_no += 3;
		}

		break;

	case Direction::West:	//Moving left
		if (grid_cell_no == 0 || grid_cell_no == 3 || grid_cell_no == 6)	//If player is in the left part of the grid
		{
			if (current_room->get_side(Direction::West)->type_info() == "class Door" || current_room->get_side(Direction::West)->type_info() == "class ExitDoor")	//If eastern side is door
			{
				//Then check, if he can enter the door
				if (current_room->get_side(Direction::West)->Enter() && grid_cell_no == 3)//send keys
				{
					if (current_room->get_side(Direction::West)->type_info() == "class ExitDoor")
					{
						game_info->switch_finish_flag();
						return;
					}

					shape.move(sf::Vector2f(200, 0));
					grid_cell_no += 2;
					game_info->change_current_room_no(-1);
				}
				else
				{
					//tell the player why he cannot access the door
				}
			}
			else if (current_room->get_side(Direction::West)->Enter()) //Not door
			{
				shape.move(sf::Vector2f(200, 0));
				grid_cell_no += 2;
				game_info->change_current_room_no(-1);
			}
		}
		else //In any other case, player can move up with no other conditions
		{
			shape.move(sf::Vector2f(-100, 0));
			grid_cell_no -= 1;
		}

		break;
	}
}