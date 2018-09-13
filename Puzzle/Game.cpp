#include "Game.h"
#include <random>
#include <ctime>


MiniGame::~MiniGame()
{
}

Game::Game() 
	: window_width_(700)
	, window_height_(465)
	, scaling_coeff_w(1)
	, scaling_coeff_h(1)
	, firts_sprite(-1)
	, second_sprite(-1)
{
	std::cout << "Here start Puzzle Application";
}


Game::~Game()
{

}

void Game::Initialize()
{
	window.create(sf::VideoMode(window_width_, window_height_), "Puzzle", sf::Style::Close);
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

	int sprite_counter = 0;
	int table[cColumns][cRows] = {{0}};
	for (auto i = 0; i < cColumns; i++)
		for (auto j = 0; j < cRows; j++)
		{
			sprite[sprite_counter] = main_sprite;
			sprite[sprite_counter].setTextureRect(sf::IntRect(i * w_start, j * h_start, w_start, h_start));
			table[i][j] = sprite_counter;
			sprite_counter++;
		}

	memcpy(static_cast<void*>(works_spite), sprite, sizeof(works_spite));

	Randomize_Puzzle(sprite);

	bool Help_flag = false;

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{


			if (event.type == sf::Event::Closed || IsCompleted())
				window.close();
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::F1)
				{
					Help_flag = !Help_flag;
					std::cout << "\n" << "Pressed F1 ";
				}
			if (event.type == sf::Event::MouseButtonPressed)
				if (event.key.code == sf::Mouse::Left)
						Click(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
		}

		window.clear(sf::Color::White);

		if (!Help_flag)
		{
			for (auto i = 0; i < cColumns; i++)
				for (auto j = 0; j < cRows; j++)
				{
					auto k = table[i][j];
					sprite[k].setPosition(/*scaling_coeff_w* */ i * w_start, /*scaling_coeff_h* */ j * h_start);
					window.draw(sprite[k]);

				}
			DrawSeparationLine(window, w_start, h_start);
		}
		else
			window.draw((main_sprite));

		window.display();

	}
}

void Game::Click(float x, float y)
{
	if (!(x < window_width_ && y <window_height_))
		return;
	auto c = 0;

	for (auto i : sprite)
	{
		if (i.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			firts_sprite == -1 ? firts_sprite = c : second_sprite = c;
		else
			c++;
	}

	if (firts_sprite >= 0 && second_sprite >= 0)
		if ((firts_sprite < (cColumns * cRows)) && (second_sprite < (cColumns * cRows)))
			SwapBlocks(firts_sprite, second_sprite);
}

bool Game::IsCompleted() const
{
	for (auto i = 0; i < (cColumns * cRows); i++)
	{
		if (sprite[i].getTextureRect() != works_spite[i].getTextureRect())
			return false;
	}
	return  true;
}

void Game::Render() const
{
}

void Game::SwapBlocks(int const first_block, int const second_block)
{

	auto const tmp_sprite = sprite[first_block];
	sprite[first_block] = sprite[second_block];
	sprite[second_block] = tmp_sprite;

	firts_sprite = second_sprite = -1;
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

