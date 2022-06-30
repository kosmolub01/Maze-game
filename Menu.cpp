#include "Menu.h"
#include "PlaySubmenu.h"
#include "PlayersRanking.h"
#include "RankingSubmenu.h"


Menu::Menu(sf::RenderWindow* window)
{
	number_of_options = 4;

	players_ranking = new PlayersRanking;

	// window initialization
	
	this->window = window;

	options.resize(number_of_options);

	if (!font.loadFromFile("arial.ttf"))
	{
		//error
	}

	//With window width = 400, font size = 30, the maximum length of text (properly printed) = 24

	options[0].setFont(font);
	options[0].setFillColor(sf::Color::Red);
	options[0].setString("Play");
	options[0].setPosition(sf::Vector2f(text_position_offset(options[0], window->getSize().x), window->getSize().y / (number_of_options + 1) * 1));

	options[1].setFont(font);
	options[1].setFillColor(sf::Color::White);
	options[1].setString("Show the player standings");
	options[1].setPosition(sf::Vector2f(text_position_offset(options[1], window->getSize().x), window->getSize().y / (number_of_options + 1) * 2));

	options[2].setFont(font);
	options[2].setFillColor(sf::Color::White);
	options[2].setString("Help");
	options[2].setPosition(sf::Vector2f(text_position_offset(options[2], window->getSize().x), window->getSize().y / (number_of_options + 1) * 3));

	options[3].setFont(font);
	options[3].setFillColor(sf::Color::White);
	options[3].setString("Exit");
	options[3].setPosition(sf::Vector2f(text_position_offset(options[3], window->getSize().x), window->getSize().y / (number_of_options + 1) * 4));

	selected_option_index = 0;
}

Menu::~Menu()
{
	
}

void Menu::show()
{
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

			// key pressed
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Up)
				{
					this->move_up();
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					this->move_down();
				}
				else if (event.key.code == sf::Keyboard::Return)	//Handle chosen option
				{
					switch (this->get_selected_option_index())
					{
					case 0:	//Play
					{
						system("CLS");

						PlaySubmenu play_submenu(window);

						play_submenu.show(players_ranking);

						break;
					}
					case 1:	//Show the player standings
					{
						system("CLS");

						RankingSubmenu ranking_submenu(window);

						ranking_submenu.show(players_ranking);
						
						break;
					}
					case 2:	//Help
					{
						this->show_help();
						break;
					}
					case 3:	//Exit
					{
						window->close();
						break;
					}
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

		for (auto option : options)
		{
			window->draw(option);
		}

		window->display();
	}

	system("CLS");

}

void Menu::move_up()
{
	if (selected_option_index - 1 >= 0)
	{
		options[selected_option_index].setFillColor(sf::Color::White);
		selected_option_index--;
		options[selected_option_index].setFillColor(sf::Color::Red);
	}
	else
	{
		options[selected_option_index].setFillColor(sf::Color::White);
		selected_option_index = number_of_options - 1;
		options[selected_option_index].setFillColor(sf::Color::Red);
	}
}

void Menu::move_down()
{
	if (selected_option_index + 1 < number_of_options)
	{
		options[selected_option_index].setFillColor(sf::Color::White);
		selected_option_index++;
		options[selected_option_index].setFillColor(sf::Color::Red);
	}
	else
	{
		options[selected_option_index].setFillColor(sf::Color::White);
		selected_option_index = 0;
		options[selected_option_index].setFillColor(sf::Color::Red);
	}
}

int Menu::get_selected_option_index()
{
	return selected_option_index;
}

float Menu::text_position_offset(sf::Text text, float window_width)
{
	return ((window_width - text.getLocalBounds().width) / 2);
}

void Menu::show_help()
{
	std::filesystem::path pth;
	std::ifstream file;
	std::string line;

	//Load data from "Help.txt"

	pth = std::filesystem::path{ "Data" } / "Help.txt";

	file.open(pth.c_str());

	system("CLS");

	if (file.is_open())
	{
		if (file.peek() == std::ifstream::traits_type::eof())
		{
			std::cout << "Empty file\n";
		}
		else
		{
			while (getline(file, line))
			{
				std::cout << line << "\n";
			}
		}

		file.close();
	}
	else //Error handling
	{
		std::cout << "An error occurred while attempting to open the file \"Help.txt\"" << std::endl;
	}
}
