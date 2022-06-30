#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow* window, int maze_no)
{
	this->window = window;

	map_thread = nullptr;

	game_info = new GameInfo(window);

	window_x_coordinate = window->getPosition().x;	//Information for other window on how to place itself on the screen according to position of this window 
	window_y_coordinate = window->getPosition().y;

	switch (maze_no)
	{
	case 1:
		maze = create_maze_no1(new StandardMazeBuilder);
		break;
	case 2:
		maze = create_maze_no2(new StandardMazeBuilder);
		break;
	case 3:
		maze = create_maze_no3(new StandardMazeBuilder);
	}

	player = new Player(maze, maze->room(0), this->window->getSize());	//Assume that created maze has at least one room, so it can be passed to player
}

Game::~Game()
{
	
}

int Game::run()
{
	bool escape = false;	//Player can stop the game it two ways, by pressing the escape button and going back to menu, 
							//or by clicking the "Close" icon and stopping the program

	while (window->isOpen() && (!escape))	//As long as player doesn't close the game, execute the loop 
	{
		//Event polling

		sf::Event event;

		while (window->pollEvent(event))
		{
			if (!game_info->get_game_state().first_move)	//Check if player moved
			{
				if (event.type ==  sf::Event::KeyReleased && (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right ||
					event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down))
				{
					game_info->switch_first_move_flag();
				}
			}

			switch (event.type)
			{
			case sf::Event::Closed:

				window->close();

				if (game_info->get_game_state().map_turned_on)	//If map is open, close it
				{
					map_thread->request_stop();

					if (map_thread->joinable())
					{
						map_thread->join();
					}
				}

				break;

				// key pressed
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Left)	
				{
					player->move(Direction::West, game_info);
				}
				else if (event.key.code == sf::Keyboard::Right)
				{
					player->move(Direction::East, game_info);
				}
				else if (event.key.code == sf::Keyboard::Up)
				{
					player->move(Direction::North, game_info);
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					player->move(Direction::South, game_info);
				}
				else if (event.key.code == sf::Keyboard::Escape)
				{
					if (game_info->get_game_state().map_turned_on)	//If map is open, close it
					{
						map_thread->request_stop();

						if (map_thread->joinable())
						{
							map_thread->join();
						}
					}

					escape = true;	//Get back to menu
				}
				else if (event.key.code == sf::Keyboard::M)
				{
					if (game_info->get_game_state().map_turned_on)	//If map is open, close it
					{
						map_thread->request_stop();
					}
					else   //If not, open it. Resonable error handling woud be like if open_map() returns false, map is not open, do not change the flag 
					{
						map_thread = new std::jthread(std::bind_front(&Game::open_map, this), window_x_coordinate, window_y_coordinate);
						game_info->switch_map_turned_on_flag();
						window->requestFocus();
					}
				}
				break;

				//we don't process other types of events
			default:
				break;
			}
		}

		//Update
		
		this->update();

		if (game_info->get_game_state().finish || game_info->get_game_state().timeout)
		{
			return game_info->get_time_left();	//Return back to the "Play" submenu
		}

		//Render

		window->clear();	

		maze->draw(*window, player->get_current_room());	//Draw maze (single room with given number) 
		player->draw(*window);	//and the player 
		game_info->show_status_bar(); //Depending on the game state, it will print status bar or finish message
		window->display();
	}

	return 0;	//Default result value
}

void Game::update()
{
	player->set_current_room(maze->room(game_info->get_current_room_no()));

	if (!player->get_current_room()->get_visited())	//Mark current room as visited, if needed
	{
		player->get_current_room()->set_visited();
	}

	//Update main window position

	window_x_coordinate = window->getPosition().x;	
	window_y_coordinate = window->getPosition().y;

	//Status bar message update

	if (!game_info->get_game_state().first_move)	//As long as player doesn't do anything, restart the time measurement and inform the player how to start
	{
		game_info->start_time_measurement();
		game_info->set_message("Press any arrow key to start");
	}
	else   //If he starts, erase the status bar message
	{
		game_info->erase_message();
	}

	game_info->set_time_left(round(maze->get_time_limit() - game_info->get_time()));	//Count time left. Time is shown in seconds and this is why round 
																		//function is used

	if (game_info->get_time_left() < 0 && game_info->get_game_state().first_move)
	{
		if (game_info->get_game_state().map_turned_on)	//If map is open, close it
		{
			map_thread->request_stop();

			if (map_thread->joinable())
			{
				map_thread->join();
			}
		}

		game_info->switch_timeout_flag();

		game_info->show_timeout_message();	//Timeout
		return;
	}

	if (game_info->get_game_state().finish)
	{
		if (game_info->get_game_state().map_turned_on)	//If map is open, close it
		{
			map_thread->request_stop();

			if (map_thread->joinable())
			{
				map_thread->join();
			}
		}

		game_info->show_finish_message();
		return;
	}
}

void Game::open_map(std::stop_token stop_token, int window_x_coordinate, int window_y_coordinate)
{
	//Create a map, do the event polling

	Map map(new sf::RenderWindow(sf::VideoMode(500, 500), "Map", sf::Style::Close | sf::Style::Titlebar));

	sf::RenderWindow* window = map.get_window();

	if (window_x_coordinate > 510)	//If there is enough space on the screen for both game and map windows, place map to the left of game window 
	{								//In other case, map window will be place in the center of the screen
		window->setPosition(sf::Vector2i(window_x_coordinate - 510, window_y_coordinate));
	}

	while (window->isOpen())
	{
		//Event polling

		sf::Event event;

		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window->close();

				break;

			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Escape)
				{
					window->close();
				}
				else if (event.key.code == sf::Keyboard::M)
				{
					window->close();
				}
			
				break;

				//we don't process other types of events
			default:
				break;
			}
		}

		//Update

		if (stop_token.stop_requested())
		{
			window->close();
		}

		//Render

		window->clear();

		map.draw(maze, game_info->get_current_room_no());

		window->display();
	}

	game_info->switch_map_turned_on_flag();
}

Maze* Game::create_maze_no1(MazeBuilder* builder)	//Recipe to create a maze no. 1
{
	builder->build_maze(15);

	builder->build_room(0);
	builder->build_room(1);
	builder->build_room(2);
	builder->build_room(11);
	builder->build_room(20);
	builder->build_room(21);
	builder->build_room(22);

	builder->build_door(1, 0);
	builder->build_door(2, 1);
	builder->build_door(11, 1);
	builder->build_door(21, 11);
	builder->build_door(21, 20);
	builder->build_door(22, 21);
	builder->build_exit_door(22, Direction::East);

	return builder->get_maze();
}

Maze* Game::create_maze_no2(MazeBuilder* builder)	//Recipe to create a maze no. 2
{
	builder->build_maze(10);

	builder->build_room(0);
	builder->build_room(10);
	builder->build_room(20);
	builder->build_room(21);
	builder->build_room(22);
	builder->build_room(24);
	builder->build_room(31);
	builder->build_room(33);
	builder->build_room(32);
	builder->build_room(34);
	builder->build_room(42);
	builder->build_room(44);

	builder->build_door(10, 0);
	builder->build_door(20, 10);
	builder->build_door(21, 20);
	builder->build_door(31, 21);
	builder->build_door(32, 31);
	builder->build_door(32, 22);
	builder->build_door(42, 32);
	builder->build_door(33, 32);
	builder->build_door(34, 33);
	builder->build_door(34, 24);
	builder->build_door(44, 34);

	builder->build_exit_door(44, Direction::South);

	return builder->get_maze();
}

Maze* Game::create_maze_no3(MazeBuilder* builder)	//Recipe to create a maze no. 3
{
	builder->build_maze(10);

	builder->build_room(0);
	builder->build_room(1);
	builder->build_room(2);
	builder->build_room(3);
	builder->build_room(4);
	builder->build_room(5);
	builder->build_room(10);
	builder->build_room(12);
	builder->build_room(14);
	builder->build_room(20);
	builder->build_room(21);
	builder->build_room(24);
	builder->build_room(30);
	builder->build_room(32);
	builder->build_room(34);
	builder->build_room(40);
	builder->build_room(41);
	builder->build_room(42);
	builder->build_room(43);
	builder->build_room(44);

	builder->build_door(1, 0);
	builder->build_door(2, 1);
	builder->build_door(3, 2);
	builder->build_door(4, 3);
	builder->build_door(5, 4);
	builder->build_door(10, 0);
	builder->build_door(12, 2);
	builder->build_door(14, 4);
	builder->build_door(20, 10);
	builder->build_door(21, 20);
	builder->build_door(24, 14);
	builder->build_door(24, 34);
	builder->build_door(30, 20);
	builder->build_door(42, 32);
	builder->build_door(44, 34);
	builder->build_door(44, 34);
	builder->build_door(40, 30);
	builder->build_door(41, 40);
	builder->build_door(42, 41);
	builder->build_door(43, 42);
	builder->build_door(44, 43);
	
	builder->build_exit_door(24, Direction::East);

	return builder->get_maze();
}