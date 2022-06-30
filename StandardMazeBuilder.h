#ifndef _STANDARDMAZEBUILDER_H_
#define _STANDARDMAZEBUILDER_H_

#include "MazeBuilder.h"
#include "Maze.h"
#include "Wall.h"
#include "Door.h"
#include "ExitDoor.h"
#include "Room.h"


class StandardMazeBuilder : public MazeBuilder
{
	void build_maze(float time_limit);
	void build_room(int room_no);
	void build_exit_door(int room_no, Direction d);
	void build_door(int room_no1, int room_no2);	
	void merge_rooms(int room_no1, int room_no2);
	Maze* get_maze();
private:
	Direction common_site(Room* r1, Room* r2);	//To distinguish which site of rooms is the common one
	Maze* current_maze;
};

#endif // !_STANDARDMAZEBUILDER_H_