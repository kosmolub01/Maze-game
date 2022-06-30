#include "StandardMazeBuilder.h"

void StandardMazeBuilder::build_maze(float time_limit)
{
	current_maze = new Maze(time_limit);
}

void StandardMazeBuilder::build_room(int room_no)
{
	if (!current_maze->room(room_no))	//Only if there is no room with room_number = room_no
	{
		Room* room = new Room(room_no);	//Then you can create one
		current_maze->add_room(room);

		room->set_side(Direction::North, new Wall);
		room->set_side(Direction::South, new Wall);
		room->set_side(Direction::East, new Wall);
		room->set_side(Direction::West, new Wall);
	}
}

void StandardMazeBuilder::build_exit_door(int room_no, Direction d)
{
	Room* r = current_maze->room(room_no);
	ExitDoor* exit_door = new ExitDoor(r);

	r->set_side(d, exit_door);
}

void StandardMazeBuilder::build_door(int room_no1, int room_no2)
{
	Room* r1 = current_maze->room(room_no1);
	Room* r2 = current_maze->room(room_no2);
	Door* door = new Door(r1, r2);

	r1->set_side(common_site(r1, r2), door);
	r2->set_side(common_site(r2, r1), door);
}

void StandardMazeBuilder::merge_rooms(int room_no1, int room_no2)
{
	Room* r1 = current_maze->room(room_no1);
	Room* r2 = current_maze->room(room_no2);

	r1->set_side(common_site(r1, r2), r2);
	r2->set_side(common_site(r2, r1), r1);
}

Direction StandardMazeBuilder::common_site(Room* r1, Room* r2)	//Returns direction of rooms common site, relatively to room r1
{
	int n1 = r1->get_room_number();
	int n2 = r2->get_room_number();

	if (n1 == (n2 + 1))
	{
		return Direction::West;
	}
	else if (n1 == (n2 - 1))
	{
		return Direction::East;
	}
	else if (n1 == (n2 + 10))
	{
		return Direction::North;
	}
	else if (n1 == (n2 - 10))
	{
		return Direction::South;
	}
	else
	{
        //error
	}
}

Maze* StandardMazeBuilder::get_maze()
{
	return current_maze;
}