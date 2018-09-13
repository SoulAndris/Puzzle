#include "Game.h"
#include <random>
#include  <ctime>


MiniGame::~MiniGame()
{
}

Game::Game() :
	window_width_(700)
	,window_height_(465)

{
	std::cout << "Here start Puzzle Application";
}


Game::~Game()
{

}

void Game::Initialize()
{
	sf::RenderWindow window(sf::VideoMode(window_width_, window_height_), "Puzzle", sf::Style::Close);
	window.setFramerateLimit(60);

	if (!puzzle_image.loadFromFile("image.png"))
		return;

	if (!texture.loadFromImage(puzzle_image))
		return;

	sf::Sprite main_sprite;
	main_sprite.setTexture(texture);

	//-----Scaling Image to Work size
	sf::Vector2f const target_size(window_width_, window_height_);
	main_sprite.setScale(target_size.x / main_sprite.getLocalBounds().width,
						 target_size.y / main_sprite.getLocalBounds().height);
	//-------------------------------

	float const w_start = main_sprite.getGlobalBounds().width / cColumns;
	float const h_start = main_sprite.getGlobalBounds().height / cRows;

	scaling_coeff_w = main_sprite.getScale().x;
	scaling_coeff_h = main_sprite.getScale().y;

	std::cout << std::endl << main_sprite.getGlobalBounds().width;
	std::cout << std::endl << main_sprite.getGlobalBounds().height;
	std::cout << std::endl << w_start;
	std::cout << std::endl << h_start;

	sf::Sprite sprite[cColumns*cRows];

	int sprite_counter = 0;
	int table[cColumns][cRows] = { 0 };
	for (auto i = 0; i < cColumns; i++)
		for (auto j = 0; j < cRows; j++)
		{
			sprite[sprite_counter] = main_sprite;
			sprite[sprite_counter].setTextureRect(sf::IntRect(i * w_start, j * h_start, w_start, h_start));
			table[i][j] = sprite_counter;
			sprite_counter++;
		}

	sf::Sprite works_spite[cColumns*cRows];

	memcpy(works_spite, sprite, sizeof(works_spite));

	Randomize_Puzzle(sprite);

	int a = -1, b = -1;
	bool Help_flag = false;

	while (window.isOpen())
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		//std::cout << pixelPos.x << "\n";

		int flag1 = 0, flag2 = 0;

		sf::Event event;


		while (window.pollEvent(event))
		{


			if (event.type == sf::Event::Closed || isPermutation(works_spite, sprite))
				window.close();
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::F1)
				{
					Help_flag = !Help_flag;
					std::cout << "\n" << "Pressed F1 ";
				}
			if (event.type == sf::Event::MouseButtonPressed)
				if (event.key.code == sf::Mouse::Left)
				{
					if(sf::Mouse::getPosition(window).x < window_width_ && sf::Mouse::getPosition(window).y < window_height_)
					{
						//std::cout << std::endl << "Click to game field";

						int c = 0;

							for (auto i : sprite)
							{
								if (i.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
								{
									std::cout << "\n" << "isClicked sprite one in number= " << c;
									flag1 = 1;
									a == -1 ? a = c : b = c;
								}
								else
									c++;
							}

						if(a != -1 && b!= -1)
						{
							sf::Sprite tmp_sprite;

							/*tmp_sprite.setTextureRect(sprite[a].getTextureRect());
							sprite[a].setTextureRect(sprite[b].getTextureRect());
							sprite[b].setTextureRect(tmp_sprite.getTextureRect());*/

							tmp_sprite = sprite[a];
							sprite[a] = sprite[b];
							sprite[b] = tmp_sprite;


							a = b = -1;
						}

					}
				}
		}

		window.clear(sf::Color::White);

		if(!Help_flag)
		{
			for (auto i = 0; i < cColumns; i++)
				for (auto j = 0; j < cRows; j++)
				{
					auto k = table[i][j];
					sprite[k].setPosition(/*scaling_coeff_w*/ i * w_start, /*scaling_coeff_h*/ j * h_start);
					window.draw(sprite[k]);

				}
		}
		else
		{
			window.draw((main_sprite));
		}

		DrawSeparationLine(window, w_start, h_start);
		window.display();
	}
}

bool Game::isPermutation(sf::Sprite *main, sf::Sprite *child)
{
	for(auto i = 0; i < (cColumns * cRows); i++)
	{
		if (main[i].getTextureRect() != child[i].getTextureRect())
			return false;
	}
	return  true;
}

void Game::Click(float x, float y)
{

}

bool Game::IsCompleted() const
{
	return false;
}

void Game::Render() const
{
}

void Game::SwapBlocks(const float first_block, const float second_block)
{
}


void Game::DrawSeparationLine(sf::RenderWindow & window, float const x_start, float const y_start) const
{
	sf::RectangleShape vertical_line[cColumns];
	sf::RectangleShape horizon_line[cRows];

	for (size_t i = 0; i < cColumns; i++)
	{
		vertical_line[i].setSize(sf::Vector2f(1, window_height_));
		vertical_line[i].setFillColor(sf::Color::White);
		vertical_line[i].setPosition(x_start * (i),0);

		window.draw(vertical_line[i]);
	}

	for (size_t i = 0; i < cRows; i++)
	{
		horizon_line[i].setSize(sf::Vector2f(window_width_, 1));
		horizon_line[i].setFillColor(sf::Color::White);
		horizon_line[i].setPosition(0, y_start * (i));

		window.draw(horizon_line[i]);
	}

}

void Game::Randomize_Puzzle(sf::Sprite *sprite_tmp)
{
	sf::Sprite local_spite;
	int a, b;
	srand(time(0));

	for (int i = 0; i < 10000; i++)
	{
		a = rand() % (cColumns * cRows -1);
		b = rand() % (cColumns * cRows -1);
		local_spite = sprite_tmp[a];
		sprite_tmp[a] = sprite_tmp[b];
		sprite_tmp[b] = local_spite;
	}

}

