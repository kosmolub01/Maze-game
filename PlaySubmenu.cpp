#include "PlaySubmenu.h"

PlaySubmenu::PlaySubmenu(sf::RenderWindow* window) : Menu(window)
{
	number_of_options = 4;

	// window initialization

	this->window = window;

	options.resize(number_of_options);

	if (!font.loadFromFile("arial.ttf"))
	{
		//error
	}

	options[0].setFont(font);
	options[0].setFillColor(sf::Color::Red);
	options[0].setString("Maze no. 1");
	options[0].setPosition(sf::Vector2f(text_position_offset(options[0], window->getSize().x), window->getSize().y / (number_of_options + 1) * 1));

	options[1].setFont(font);
	options[1].setFillColor(sf::Color::White);
	options[1].setString("Maze no. 2");
	options[1].setPosition(sf::Vector2f(text_position_offset(options[1], window->getSize().x), window->getSize().y / (number_of_options + 1) * 2));

	options[2].setFont(font);
	options[2].setFillColor(sf::Color::White);
	options[2].setString("Maze no. 3");
	options[2].setPosition(sf::Vector2f(text_position_offset(options[2], window->getSize().x), window->getSize().y / (number_of_options + 1) * 3));

	options[3].setFont(font);
	options[3].setFillColor(sf::Color::White);
	options[3].setString("Go back to menu");
	options[3].setPosition(sf::Vector2f(text_position_offset(options[3], window->getSize().x), window->getSize().y / (number_of_options + 1) * 4));

	selected_option_index = 0;
}


PlaySubmenu::~PlaySubmenu()
{

}


void PlaySubmenu::show(PlayersRanking* players_ranking)
{
	int selected_item_index = 0;
	bool escape = false;

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
					selected_item_index = this->get_selected_option_index();

					if (selected_item_index == 3)
					{
						escape = true;
					}
					else
					{
						SelectPlayer select_player(window, players_ranking);
						select_player.show(this->get_selected_option_index() + 1);
					}
				}
				else if (event.key.code == sf::Keyboard::Escape)
				{
					escape = true;
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

		for (int i = 0; i < number_of_options; i++)
		{
			window->draw(options[i]);
		}

		window->display();
	}
}