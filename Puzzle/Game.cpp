#include "Game.h"


MiniGame::~MiniGame()
{
}

Game::Game() : 
	window_height_(840)
	, window_width_(480)
{
	std::cout << "Here start Puzzle Application";
}


Game::~Game()
{

}

void Game::Initialize()
{
	sf::RenderWindow window(sf::VideoMode(window_height_, window_height_), "Puzzle", sf::Style::Close);
	window.setFramerateLimit(60);

	if (!texture.loadFromFile("image.png"))
		return;

	sf::Sprite main_sprite;
	main_sprite.setTexture(texture);

	//-----Scaling Image to Work size
	sf::Vector2f const target_size(window_height_, window_height_);
	main_sprite.setScale(target_size.x / main_sprite.getLocalBounds().width,
						 target_size.y / main_sprite.getLocalBounds().height);
	//-------------------------------
	auto const size_main_sprite = main_sprite.getTextureRect();

	auto const x_start = size_main_sprite.height / cColumns;
	auto const y_start = size_main_sprite.width / cRows;

	sf::Sprite sprite[cColumns*cRows];
	auto n = 0;
	int table[5][5];
	for (auto i = 0; i < cColumns; i++)
	{
		for (auto j = 0; j < cRows; j++)
		{
			sprite[i] = main_sprite;
			sprite[i].setTextureRect(sf::IntRect(j * y_start, i * x_start, x_start, y_start));
			table[i][j] = n;
			n++;
		}
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
		{
			for (auto j = 0; j < cRows; j++)
			{
				auto k = table[i][j];
				sprite[k].setPosition(j * x_start, i * y_start);
				window.draw(sprite[k]);

			}
		}
		DrawSeparationLine(window);
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

int Game::Block_Numbers(const float block)
{
	return 0;
}

void Game::DrawSeparationLine(sf::RenderWindow & window)
{
	sf::RectangleShape vertical_line[cColumns];
	sf::RectangleShape horizon_line[cRows];

	for (size_t i = 0; i < cColumns; i++)
	{
		vertical_line[i].setSize(sf::Vector2f(2, 500));
		vertical_line[i].setFillColor(sf::Color::White);
		vertical_line[i].setPosition(50 * (i + 1),0);

		window.draw(vertical_line[i]);
	}

	for (size_t i = 0; i < cRows; i++)
	{
		horizon_line[i].setSize(sf::Vector2f(500, 2));
		horizon_line[i].setFillColor(sf::Color::White);
		horizon_line[i].setPosition(0, 50 * (i + 1));

		window.draw(horizon_line[i]);
	}

}
