#include "Game.h"
#include <random>
#include <ctime>
#include <iostream>


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
	, Help_Flag(false)
	, rect_sprite_({0})
{
	window = new sf::RenderWindow;
	sprite = new sf::Sprite[cColumns * cRows];
	default_puzzle_sprite = new sf::Sprite[cColumns * cRows];
}


Game::~Game()
{
	delete[] default_puzzle_sprite;
	delete[] sprite;
	delete[] window;
}

void Game::Initialize()
{
	window->create(sf::VideoMode(window_width_, window_height_), "Puzzle", sf::Style::Close);
	window->setFramerateLimit(60);

	if (!puzzle_image.loadFromFile("image.png")) //Load puzzle Image
		return;

	if (!texture.loadFromImage(puzzle_image)) //Load texture of image
		return;

	main_sprite.setTexture(texture); //generation sprite

	//-----Scaling Image to Work size  (This code is for scaling the uploaded image in cases where it does not fit the size of the game window (I can implement it if needed) )
	sf::Vector2f const target_size(window_width_, window_height_);
	main_sprite.setScale(target_size.x / main_sprite.getLocalBounds().width,
						 target_size.y / main_sprite.getLocalBounds().height);     

	scaling_coeff_w = main_sprite.getScale().x;
	scaling_coeff_h = main_sprite.getScale().y;
	//-------------------------------

	rect_sprite_.left = main_sprite.getGlobalBounds().width / cColumns;
	rect_sprite_.top = main_sprite.getGlobalBounds().height / cRows;

	for (int i = 0; i < cColumns; i++)
		for (int j = 0; j < cRows; j++)
		{
			sprite[(i * cColumns ) + j] = main_sprite;
			sprite[(i * cColumns ) + j].setTextureRect(sf::IntRect(i * rect_sprite_.left, j * rect_sprite_.top, rect_sprite_.left, rect_sprite_.top));
			Game_table[i][j] = (i * cColumns) + j;
		}

	memcpy(default_puzzle_sprite, sprite, sizeof (*default_puzzle_sprite) * (cColumns * cRows));

	Randomize_Puzzle(sprite);

	while (window->isOpen())
	{

		while (window->pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
					window->close();
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::F1)
					Help_Flag = !Help_Flag;
			if (event.type == sf::Event::MouseButtonPressed && !Help_Flag && !IsCompleted() )
				if (event.key.code == sf::Mouse::Left)
						Click(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
		}

		Render();
	}
}

void Game::Render() const
{
	window->clear(sf::Color::White);

	if (!Help_Flag)
	{
		for (auto i = 0; i < cColumns; i++)
			for (auto j = 0; j < cRows; j++)
			{
				const auto k = Game_table[i][j];
				sprite[k].setPosition(i * rect_sprite_.left, j * rect_sprite_.top);
				window->draw(sprite[k]);
			}
		DrawSeparationLine(window, rect_sprite_.left, rect_sprite_.top);
	}
	else
		window->draw((main_sprite));

	window->display();
}

void Game::Click(float x, float y)
{
	if (!(x < window_width_ && y <window_height_))
		return;
	auto c = 0;

	for (auto i = 0; i < (cColumns * cRows); i++)
	{
		if (sprite[i].getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
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
		if (sprite[i].getTextureRect() != default_puzzle_sprite[i].getTextureRect())
			return false;
	}
	return  true;
}

void Game::SwapBlocks(int const first_block, int const second_block)
{

	auto const tmp_sprite = sprite[first_block];
	sprite[first_block] = sprite[second_block];
	sprite[second_block] = tmp_sprite;

	firts_sprite = second_sprite = -1;
}


void Game::DrawSeparationLine(sf::RenderWindow *window, float const x_start, float const y_start) const
{
	sf::RectangleShape vertical_line[cColumns];
	sf::RectangleShape horizon_line[cRows];

	for (size_t i = 0; i < cColumns; i++)
	{
		vertical_line[i].setSize(sf::Vector2f(1.f, window_height_));
		vertical_line[i].setFillColor(sf::Color::White);
		vertical_line[i].setPosition(x_start * (i),0);

		window->draw(vertical_line[i]);
	}

	for (size_t i = 0; i < cRows; i++)
	{
		horizon_line[i].setSize(sf::Vector2f(window_width_, 1.f));
		horizon_line[i].setFillColor(sf::Color::White);
		horizon_line[i].setPosition(0, y_start * (i));

		window->draw(horizon_line[i]);
	}
}

void Game::Randomize_Puzzle(sf::Sprite *sprite_tmp)
{
	srand(time(0));

	for (auto i = 0; i < 10000; i++)
	{
		int a = rand() % (cColumns * cRows -1);
		int b = rand() % (cColumns * cRows - 1);
		const sf::Sprite local_spite = sprite_tmp[a];
		sprite_tmp[a] = sprite_tmp[b];
		sprite_tmp[b] = local_spite;
	}

}

