#ifndef _PLAYERSRANKING_H_
#define _PLAYERSRANKING_H_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <functional>
#include <filesystem>

struct PlayerRecord	//Describes single row of a "PlayersRanking.txt" file
{
	int maze_no_1, maze_no_2, maze_no_3; 
	std::string nickname;
};

class PlayersRanking //Provides an access to a file with game results 
{
public:
	PlayersRanking();
	~PlayersRanking();

	std::vector<PlayerRecord>& get_players_records();
	std::vector<std::string> get_players_nicknames();
	int get_number_of_players();
	void increment_number_of_players();
	void save_the_result(std::string nickname, int maze_no, int result);
	void save_changes(); //Writes players_records to a file 
	void show_ranking(int selected_maze); //Shows ranking of players of selected maze via console

private:
	std::vector<std::string> file_header;		//Vector contains header of a file
	std::vector<PlayerRecord> players_records;
	std::filesystem::path pth;
	int number_of_players;
};

#endif // !_PLAYERSRANKING_H_