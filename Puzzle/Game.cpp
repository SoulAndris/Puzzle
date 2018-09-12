#include "Game.h"


MiniGame::~MiniGame()
{
}

Game::Game() : 
	window_height_(400)
	, window_width_(400)
{
	std::cout << "Hete start Puzzle Application";
}


Game::~Game()
{

}

void Game::Initialize()
{
	sf::RenderWindow window(sf::VideoMode(window_height_, window_width_), "Puzzle", sf::Style::Close);
	window.setFramerateLimit(60);
	if (!texture.loadFromFile("image.png"))
		return;

	sf::Sprite sprite[cColumns*cRows];
	int n = 0;
	int table[7][7];
	for (int i = 0; i < cColumns; i++)
	{
		for (int j = 0; j < cRows; j++)
		{
			sprite[i].setTexture(texture);
			sprite[i].setTextureRect(sf::IntRect(j * 120, i * 120, 120, 120));
			table[i + 1][j + 1] = n;
			n++;
		}
	}

	float x_start = window_height_ / cColumns;
	float y_start = window_width_ / cRows;

	/*Rect tmp_coords;
	float h, w = 0;
	for (; h > window_height && w > window_width; )
	{
		tmp_coords.left = h;
		tmp_coords.top = h += h + x_start;
		tmp_coords.right = w += w + y_start;
		tmp_coords.bottom = w;
		Rect_Vector.push_back(tmp_coords);
	}*/

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
				auto n = table[i + 1][j + 1];
				sprite[n].setPosition(j * 50, i * 50);
				window.draw(sprite[n]);

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
