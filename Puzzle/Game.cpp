#include "Game.h"


MiniGame::~MiniGame()
{
}

Game::Game() :
	window_width_(840)
	,window_height_(480)

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

	auto sprite_counter = 0;
	int table[cColumns][cRows] = {0};
	for (auto i = 0; i < cColumns; i++)
		for (auto j = 0; j < cRows; j++)
		{
			sprite[sprite_counter] = main_sprite;
			sprite[sprite_counter].setTextureRect(sf::IntRect(i * w_start, j * h_start, w_start, h_start));
			table[i][j] = sprite_counter;
			sprite_counter++;
		}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);
		for (auto i = 0; i < cColumns; i++)
			for (auto j = 0; j < cRows; j++)
			{
				auto k = table[i][j];
				sprite[k].setPosition(scaling_coeff_w * i * w_start, scaling_coeff_h * j * h_start);
				window.draw(sprite[k]);

			}
		//window.draw((main_sprite));
		DrawSeparationLine(window, w_start, h_start);
		window.display();
	}
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
