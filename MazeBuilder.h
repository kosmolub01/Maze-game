#ifndef _MAZEBUILDER_H_
#define _MAZEBUILDER_H_

#include "Maze.h"

class MazeBuilder	
{
public:
	virtual void build_maze(float time_limit) = 0;	
	virtual void build_room(int room_no) = 0;
	virtual void build_exit_door(int room_no, Direction d) = 0;
	virtual void build_door(int room_no1, int room_no2) = 0;
	virtual void merge_rooms(int room_no1, int room_no2) = 0;
	virtual Maze* get_maze() = 0;
protected:
	MazeBuilder() {};	
};

#endif // !_MAZEBUILDER_H_

