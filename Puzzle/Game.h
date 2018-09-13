#ifndef GAME_H
#define GAME_H

/*---------------Nevosoft-------------*/
#include "MiniGameInterface.h"
/*------------------------------------*/

/*--------------SFML-------------*/

#include <SFML/Graphics.hpp>

/*------------Other Header's----------*/
#include "Graphic.h"

#include <iostream>
#include <stdio.h>


class Game : public MiniGame
{
public:
	Game();
	~Game();

	void Initialize();
	void Click(float x, float y);
	bool IsCompleted() const;
	void Render() const;

private:

	void SwapBlocks(int const first_block, int const second_block);
	void DrawSeparationLine(sf::RenderWindow &window, float const x_start, float const y_start) const;
	void Randomize_Puzzle(sf::Sprite *m);

private:

	sf::RenderWindow window;
	int window_width_;
	int window_height_;

	sf::Texture texture;
	sf::Image puzzle_image;

	sf::Sprite  sprite[cColumns * cRows],
				works_spite[cColumns * cRows];

	float scaling_coeff_w;
	float scaling_coeff_h;

	int firts_sprite;
	int second_sprite;
};





#endif // GAME_H