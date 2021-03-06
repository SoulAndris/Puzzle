#ifndef GAME_H
#define GAME_H

/*---------------Nevosoft-------------*/
#include "MiniGameInterface.h"
/*------------------------------------*/

/*--------------SFML-------------*/

#include <SFML/Graphics.hpp>

/*------------Other Header's----------*/

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

	void SwapBlocks(int const first_block, int const second_block);  // function of changing two pieces of the puzzle in places
	void DrawSeparationLine(sf::RenderWindow *window, float const x_start, float const y_start) const;  //function of drawing the dividing lines of the puzzle
	static void Randomize_Puzzle(sf::Sprite *m); //function of random mixing of puzzle pieces

	sf::RenderWindow *window;

	int window_width_,
		window_height_;

	sf::Texture texture;
	sf::Image puzzle_image;

	sf::Sprite  *sprite,
				*default_puzzle_sprite,
				 main_sprite;

	float scaling_coeff_w,
		  scaling_coeff_h;

	int firts_sprite,
		second_sprite;

	bool Help_Flag;
	sf::Event event{};

	Rect rect_sprite_;

	int Game_table[cColumns][cRows] = {{0}};
};





#endif // GAME_H