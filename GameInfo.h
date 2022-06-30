#ifndef _GAMEINFO_H_
#define _GAMEINFO_H_

#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>

class GameInfo
{
	struct GameState	//Describes current game state
	{
		bool finish = false;	//Exit door achieved
		bool timeout = false;
		bool first_move = false;
		bool map_turned_on = false;
	};
	
public:
	GameInfo(sf::RenderWindow* window);

	void switch_finish_flag();
	void switch_timeout_flag();
	void switch_first_move_flag();
	void switch_map_turned_on_flag();
	void change_current_room_no(int change);
	void start_time_measurement();
	void set_message(std::string message);
	void erase_message();
	GameState get_game_state();
	int get_current_room_no();
	float get_time(); //In seconds	
	void set_time_left(int time);
	int get_time_left();
	void show_status_bar();
	void show_finish_message();
	void show_timeout_message();
	bool button_or_close_icon();	//Returns true if player presses any button or clicks "Close" icon
	float text_position_offset(sf::Text text, float window_width);
private:
	sf::RenderWindow* window;
	sf::Font font;
	sf::Text message;
	sf::Text time_left_label;
	GameState game_state;
	sf::Clock clock;
	int current_room_no = 0;	//Used to update current_room according to player actions
	int time_left = 0;
};

#endif // !_GAMEINFO_H_

