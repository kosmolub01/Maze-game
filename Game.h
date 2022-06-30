#ifndef _GAME_H_
#define _GAME_H_

#include <SFML/Graphics.hpp>
#include <thread>
#include <functional>
#include "GameInfo.h"
#include "Maze.h"
#include "MazeBuilder.h"
#include "StandardMazeBuilder.h"
#include "Player.h"
#include "Map.h"

class Game
{
public:
	Game(sf::RenderWindow* window, int maze_no);
	virtual ~Game();	

	int run();
	void update();
	void open_map(std::stop_token stop_token, int window_x_coordinate, int window_y_coordinate);

	Maze* create_maze_no1(MazeBuilder* builder);
	Maze* create_maze_no2(MazeBuilder* builder);
	Maze* create_maze_no3(MazeBuilder* builder);

private:
	sf::RenderWindow* window;
	std::jthread* map_thread;
	GameInfo* game_info;
	Maze* maze;
	Player* player;
	int window_x_coordinate;
	int window_y_coordinate;
};

#endif // !_GAME_H_