#include "SelectPlayer.h"

SelectPlayer::SelectPlayer(sf::RenderWindow* window, PlayersRanking* players_ranking) : Menu(window), players_ranking(players_ranking)
{
	// window initialization

	this->window = window;

	if (!font.loadFromFile("arial.ttf"))
	{
		//error
	}

	info.setFont(font);
	info.setFillColor(sf::Color::White);
	info.setString("Select the player \n- use arrow keys");
	info.setPosition(sf::Vector2f(text_position_offset(info, window->getSize().x), (window->getSize().y / 2) - 100));

	std::vector<PlayerRecord> players_records = players_ranking->get_players_records();

	number_of_options = players_records.size() + 1;

	options.resize(number_of_options);

	options[0].setFont(font);
	options[0].setFillColor(sf::Color::Red);
	options[0].setString("< Add new player >");
	options[0].setPosition(sf::Vector2f(text_position_offset(options[0], window->getSize().x), window->getSize().y / 2));

	for (int i = 1; i < number_of_options; i++)
	{
		options[i].setFont(font);
		options[i].setFillColor(sf::Color::Red);
		options[i].setString("< " + players_records[i-1].nickname + " >");
		options[i].setPosition(sf::Vector2f(text_position_offset(options[i], window->getSize().x), window->getSize().y / 2));
	}

	selected_option_index = 0;
}

SelectPlayer::~SelectPlayer()
{

}

void SelectPlayer::show(int maze_no)
{
	bool escape = false;
	bool escaped_form_add_new_player = false;	//Informs if player escaped form add_new_player
	int result = 0, return_code = 0;
	std::string nickname;	//Nick name

	while (window->isOpen() && (!escape)) //Player can click the "Close" icon and stop the program or choose "Go back to menu" option or get back to menu by pressing the escape button
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

				// key pressed
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Right)
				{
					this->move_right();
				}
				else if (event.key.code == sf::Keyboard::Left)
				{
					this->move_left();
				}
				else if (event.key.code == sf::Keyboard::Return)	//Handle chosen option
				{
					if (selected_option_index == 0)		//If player wants to add new player
					{
						window->setVisible(false);

						return_code = add_new_player();

						window->setVisible(true);

						if (return_code == 0)
						{
							while (window->pollEvent(event));

							Game game(window, maze_no);
							result = game.run();
							players_ranking->save_the_result(players_ranking->get_players_records()[number_of_options - 1].nickname, maze_no, result);
						}
						else if(return_code == 1)
						{
							std::cout << "There is too much players (" << players_ranking->get_number_of_players() 
									  << "). Select one of the already existing.\n";

							break;
						}
						else if(return_code == 2)
						{
							escaped_form_add_new_player = true;

							break;
						}
					}
					else
					{
						system("CLS");

						Game game(window, maze_no);
						result = game.run();
						players_ranking->save_the_result(players_ranking->get_players_records()[selected_option_index - 1].nickname, maze_no, result);
					}

					return;
				}
				else if (event.key.code == sf::Keyboard::Escape)
				{
					if (escaped_form_add_new_player)	//Ignore this escape event
					{
						escaped_form_add_new_player = false;
					}
					else
					{
						escape = true;
					}
				}
				break;

				// we don't process other types of events
			default:
				break;
			}
		}

		//Update

		//Render

		window->clear();

		window->draw(info);

		window->draw(options[selected_option_index]);

		window->display();
	}
}

void SelectPlayer::move_left()
{
	if (selected_option_index == 0)
	{
		selected_option_index = number_of_options - 1;
	}
	else
	{
		selected_option_index--;
	}
}

void SelectPlayer::move_right()
{
	if (selected_option_index == number_of_options - 1)
	{
		selected_option_index = 0;
	}
	else
	{
		selected_option_index++;
	}
}

int SelectPlayer::add_new_player()
{
	char c = 0, clear_output = 0;
	std::regex r("[A-Za-z0-9]+");
	std::string nickname = "";
	int space_occurrences = 0;
	bool forbidden_character_occurrence = false, empty_field = false, too_long = false;

	system("CLS");

	if ((players_ranking->get_number_of_players() + 1) > 999)
	{
		return 1;
	}
	else
	{
		std::cout << "Type new player's nickname:\n";

		while (true)
		{
			c = _getch();	//_getchar() is used because it makes it possible to analyze 
							//every single character typed by player even before pressing enter button

			std::cout << c;

			if (c == 13 && (!too_long))	// Enter button, nickname has sufficient length
			{
				if (regex_match(nickname, r))	//Proper nickname
				{
					//Correct - Add new player
					PlayerRecord player_record;

					player_record.nickname = nickname;
					player_record.maze_no_1 = player_record.maze_no_2 = player_record.maze_no_3 = 0;

					players_ranking->get_players_records().push_back(player_record);
					players_ranking->save_changes();
					players_ranking->increment_number_of_players();

					system("CLS");

					return 0;
				}
				else //Empty field or forbidden characters
				{
					system("CLS");
					
					if (nickname == "")
					{
						empty_field = true;

						std::cout << "Empty field. Type new nickname:\n";
					}
					else
					{
						forbidden_character_occurrence = true;

						space_occurrences = 0;

						for (int i = 0; i < nickname.size(); i++)
						{
							if (nickname[i] == ' ')
							{
								space_occurrences++;
							}
						}

						if (space_occurrences == nickname.size())	//If player typed only spaces
						{
							nickname = "";	//Erase nickname
							forbidden_character_occurrence = false;
						}

						std::cout << "Forbidden characters. Allowed: A-Z, a-z, 0-9. Type new nickname:\n" << nickname;
					}
				}
			}
			else if (c == 27) // Escape button
			{
				system("CLS");

				return 2;
			}
			else if (nickname.size() > 0 && c == 8) // Backspace button
			{
				system("CLS");

				nickname.pop_back();

				if (forbidden_character_occurrence)	//If there was forbidden character in nickname, check if there is still one
				{
					if (regex_match(nickname, r))
					{
						forbidden_character_occurrence = false;
						std::cout << "Type new player's nickname:\n";
					}
					else if(nickname.size() > 0)
					{
						std::cout << "Forbidden characters. Allowed: A-Z, a-z, 0-9. Type new nickname:\n";
					}
					else   //Nickname is empty
					{
						forbidden_character_occurrence = false;
						std::cout << "Type new player's nickname:\n";
					}
				}
				else if(nickname.size() <= 20)
				{
					too_long = false;
					std::cout << "Type new player's nickname:\n";
				}

				std::cout << nickname;
			}
			else if(c != 8 && c != 13)	//If player doesn't use backspace, then you can add character to nickname
			{
				nickname += c;

				if (empty_field) //If there was an empty field, there is no longer one
				{
					empty_field = false;

					system("CLS");

					std::cout << "Type new player's nickname:\n" << nickname;	//No empty field, so show normal information
				}
			}
			
			if (nickname.size() > 20)	//Too long nickname
			{
				too_long = true;

				system("CLS");

				std::cout << "Nickname is too long (maximum length is 20 characters).\n" << nickname;
			}
		}
	}
}
