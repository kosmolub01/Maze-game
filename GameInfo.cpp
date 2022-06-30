#include "GameInfo.h"
#include <iostream>

GameInfo::GameInfo(sf::RenderWindow* window)
{
	this->window = window;

	if (!font.loadFromFile("arial.ttf"))
	{
		//error
	}

	time_left_label.setFont(font);
	time_left_label.setCharacterSize(18);
	time_left_label.setFillColor(sf::Color::White);
	time_left_label.setString("Time left: 0 [s]");
	time_left_label.setPosition(sf::Vector2f(1, 1));

	message.setFont(font);
	message.setCharacterSize(18);
	message.setFillColor(sf::Color::White);
	message.setString("Message");
	message.setPosition(sf::Vector2f(150, 1));
}

void GameInfo::switch_finish_flag()
{
	game_state.finish ? game_state.finish = false : game_state.finish = true;
}

void GameInfo::switch_timeout_flag()
{
	game_state.timeout ? game_state.timeout = false : game_state.timeout = true;
}

void GameInfo::switch_first_move_flag()
{
	game_state.first_move ? game_state.first_move = false : game_state.first_move = true;
}

void GameInfo::switch_map_turned_on_flag()
{
	game_state.map_turned_on ? game_state.map_turned_on = false : game_state.map_turned_on = true;
}

void GameInfo::change_current_room_no(int change)
{
	current_room_no += change;
}

void GameInfo::start_time_measurement()
{
	clock.restart();
}

void GameInfo::set_message(std::string message)
{
	if (message.size() > 30)	//error - no space for sended message
	{
		this->message.setString("*Too long message");
	}
	else
	{
		this->message.setString(message);
	}
}

void GameInfo::erase_message()
{
	this->message.setString("");
}

GameInfo::GameState GameInfo::get_game_state()
{
	return game_state;
}

int GameInfo::get_current_room_no()
{
	return current_room_no;
}

float GameInfo::get_time()
{
	if (game_state.map_turned_on)	//If map is open, time measurement speeds up
	{
		return clock.getElapsedTime().asSeconds() * 1.5;	
	}
	else
	{
		return clock.getElapsedTime().asSeconds();
	}
}

void GameInfo::set_time_left(int time)
{
	this->time_left = time;
}

int GameInfo::get_time_left()
{
	return this->time_left;
}

void GameInfo::show_status_bar()
{
	this->time_left_label.setString("Time left: " + std::to_string(time_left) + " [s]");
	window->draw(this->time_left_label);
	window->draw(message);
}

void GameInfo::show_finish_message()
{
	sf::Text info;	//Instruction for the player
	sf::Event event;

	message.setCharacterSize(22);
	message.setString("Your score: ");
	message.setPosition(sf::Vector2f(text_position_offset(message, window->getSize().x) - 15, (window->getSize().y * 0.4)));


	this->time_left_label.setCharacterSize(22);
	this->time_left_label.setString(std::to_string(time_left));
	this->time_left_label.setPosition(message.getPosition().x + message.getLocalBounds().width, (window->getSize().y * 0.4));

	info.setFont(font);
	info.setCharacterSize(22);
	info.setFillColor(sf::Color::White);
	info.setString("Press any button to continue");
	info.setPosition(sf::Vector2f(text_position_offset(info, window->getSize().x), ((window->getSize().y * 0.4) + 50)));

	window->clear();

	window->draw(message);
	window->draw(this->time_left_label);
	window->draw(info);

	window->display();

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	while (window->pollEvent(event))
	{
		//Ignore upcoming events - so player doesn't accidentally skip timeout info
	}

	while (true)
	{
		if (button_or_close_icon())
		{
			return;
		}
	}
}

void GameInfo::show_timeout_message()
{
	sf::Event event;

	message.setCharacterSize(22);
	message.setString("        You ran out of time\nPress any button to continue");
	message.setPosition(sf::Vector2f(text_position_offset(message, window->getSize().x), (window->getSize().y / 2) - 30));

	window->clear();

	window->draw(message);

	window->display();

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	while (window->pollEvent(event))
	{
		//Ignore upcoming events - so player doesn't accidentally skip timeout info
	}
	
	while (true)
	{
		if (button_or_close_icon())
		{
			return;
		}
	}
}

bool GameInfo::button_or_close_icon()
{
	sf::Event event;

	if (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			return true;

			break;

		case sf::Event::KeyReleased:
			return true;

			break;

		default:
			return false;
			break;
		}
	}
	else
	{
		return false;
	}
}

float GameInfo::text_position_offset(sf::Text text, float window_width)
{
	return ((window_width - text.getLocalBounds().width) / 2);
}