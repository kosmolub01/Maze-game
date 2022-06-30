#include "PlayersRanking.h"

bool greater_than(PlayerRecord record_1, PlayerRecord record_2, int maze_no)	//Compare two records
{
    switch (maze_no)
    {
    case 1:
        return record_1.maze_no_1 > record_2.maze_no_1;
    case 2:
        return record_1.maze_no_2 > record_2.maze_no_2;
    case 3:
        return record_1.maze_no_3 > record_2.maze_no_3;
    }
}

PlayersRanking::PlayersRanking()
{
    std::ifstream file;
    std::string line, header_element;
    std::istringstream input_data;
    PlayerRecord player_record;
    bool change = false;    //Indicates if player's nickname is changed
    int i = 0;

    //Load data from "PlayersRanking.txt"

    pth = std::filesystem::path{ "Data" } / "PlayersRanking.txt";

    file.open(pth.c_str());

    if (file.is_open())
    {
        if (file.peek() == std::ifstream::traits_type::eof())
        {
            std::cout << "Empty file\n";
            number_of_players = 0;
        }
        else
        {
            while (getline(file, line))
            {
                input_data.str(line);
                input_data.clear();

                if (i == 0)
                {
                    while (input_data >> header_element)
                    {
                        file_header.push_back(header_element);
                    }
                }
                else if (i < 999)    //999 is a max number of players
                {
                    input_data >> player_record.nickname >> player_record.maze_no_1 >> player_record.maze_no_2 >> player_record.maze_no_3;

                    if (player_record.nickname.size() > 20)	//If player's nickname loaded from a file is too long, change it
                    {
                        player_record.nickname = "Too_long_nickname";
                        change = true;
                    }

                    players_records.push_back(player_record);
                }
                else
                {
                    change = true;  //Only 999 players records will be saved. Rest will be lost
                    break;
                }

                i++;
            }
            number_of_players = i - 1;
        }  

        file.close();
    }
    else //Error handling
    {
        system("CLS");
        std::cout << "An error occurred while attempting to open the file \"PlayersRanking.txt\"" << std::endl;
    }

    if (change) //If any nick is changed, save it
    {
        this->save_changes();
    }
}

std::vector<PlayerRecord>& PlayersRanking::get_players_records()
{
    return this->players_records;
}

std::vector<std::string> PlayersRanking::get_players_nicknames()
{
    std::vector<std::string> nicknames;

    for (auto player : players_records)
    {
        nicknames.push_back(player.nickname);
    }

    return nicknames;
}

int PlayersRanking::get_number_of_players()
{
    return this->number_of_players;
}

void PlayersRanking::increment_number_of_players()
{
    this->number_of_players++;
}

void PlayersRanking::save_the_result(std::string nickname, int maze_no, int result)
{
    std::ofstream file;

    if (result <= 0)    //If player runs of time, there is no sense in checking if it is the best result so far or in saving the results
    {
        return;
    }

    file.open(pth.c_str(), std::ios::trunc);

    if (file.is_open())
    {
        for (auto element : file_header)
        {
            file << element << " ";
        }

        file << "\n";

        for (auto& player_record : players_records)
        {
            if (player_record.nickname == nickname)
            {
                switch (maze_no)    //Check if it is the best result so far
                {
                case 1:
                    if (result > player_record.maze_no_1)
                    {
                        player_record.maze_no_1 = result;
                    }
                    break;

                case 2:
                    if (result > player_record.maze_no_2)
                    {
                        player_record.maze_no_2 = result;
                    }
                    break;
                case 3:
                    if (result > player_record.maze_no_3)
                    {
                        player_record.maze_no_3 = result;
                    }
                    break;
                }
            }

            file << player_record.nickname << " " << player_record.maze_no_1 << " " << player_record.maze_no_2 << " "
                 << player_record.maze_no_3 << "\n";
        }

        file.close();

    }
    else
    {
        system("CLS");
        std::cout << "Error" << std::endl;
    }
    
}

void PlayersRanking::save_changes()
{
    std::ofstream file;

    file.open(pth.c_str(), std::ios::trunc);

    if (file.is_open())
    {
        for (auto element : file_header)
        {
            file << element << " ";
        }

        file << "\n";

        for (auto& player_record : players_records)
        {
            file << player_record.nickname << " " << player_record.maze_no_1 << " " << player_record.maze_no_2 << " "
                << player_record.maze_no_3 << "\n";
        }

        file.close();

    }
    else
    {
        std::cout << "Error" << std::endl;
    }
}

void PlayersRanking::show_ranking(int selected_maze)
{
    int score = 0, max_length = 8, nickname_length = 0, additional_characters = 0;
    std::vector<std::string> nicknames;

    //Proper printing for maximum 999 players, length of player nickname < 21 and maximum score = 99999

    nicknames = this->get_players_nicknames();

    for (auto nickname : nicknames) //Searching for max length of nickname
    {
        nickname_length = nickname.size();

        if (nickname_length > max_length)
        {       
            max_length = nickname_length;
        }
    }

    //std::cout << max_length << "\n";

    if (8 < max_length) //8 is a length of "Nickname" header
    {
        additional_characters = max_length - 8;
    }

    std::ranges::sort(players_records, std::bind(greater_than, std::placeholders::_1, std::placeholders::_2, selected_maze));   //Sorting players results

    system("CLS");

    //std::cout << additional_characters << "\n";

    std::cout << "+------------------------" << std::string(additional_characters, '-') << "+\n|  Ranking - maze no. " << selected_maze << "  " << std::string(additional_characters, ' ') << "|\n"
              << "+-----+----------" << std::string(additional_characters, '-') << "+-------+\n"
              << "| Pos | Nickname " << std::string(additional_characters, ' ') << "| Score |\n"
              << "+-----+----------" << std::string(additional_characters, '-') << "+-------+\n";

    int i = 1;

    for (auto player_record : players_records)
    { 
        std::cout << "| " << i;

        if (i < 10)     //Depending on ordinal number, print out proper number of spaces
        {
            std::cout << std::string(3, ' ');
        }
        else if (i < 100)
        {
            std::cout << std::string(2, ' ');
        }

        std::cout << "| " << player_record.nickname << std::string((9 + additional_characters - player_record.nickname.size()), ' ') << "| ";

        switch (selected_maze)      //Print scores in given maze
        {
        case 1:
            score = player_record.maze_no_1;
            std::cout << score;
            break;

        case 2:
            score = player_record.maze_no_2;
            std::cout << score;
            break;
        case 3:
            score = player_record.maze_no_3;
            std::cout << score;
            break;
        }

        if (score < 10)     //Depending on the score, print out proper number of spaces
        {
            std::cout << std::string(5, ' ');
        }
        else if (score < 100)
        {
            std::cout << std::string(4, ' ');
        }

        std::cout << "|\n";

        i++;
    
    }

    std::cout << "+-----+----------" << std::string(additional_characters, '-') << "+-------+\n";

}

PlayersRanking::~PlayersRanking()
{

}

