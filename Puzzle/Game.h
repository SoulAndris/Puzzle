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
#include <vector>


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
	void SwapBlocks(const float first_block, const float second_block);
	int Block_Numbers(const float block);
	void DrawSeparationLine(sf::RenderWindow &window);


	int window_width_;
	int window_height_;
	sf::Texture texture;
	std::vector<Rect> Rect_Vector;


};





#endif // GAME_H