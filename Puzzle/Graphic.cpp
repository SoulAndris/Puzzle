#include "Graphic.h"



Graphic::Graphic()
{
	sf::RenderWindow window( sf::VideoMode(400, 400), "Puzzle");

	sf::Texture texture;
	if (!texture.loadFromFile("image.png"))
		return;

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(300, 300);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(sprite);
		window.display();
	}
}


Graphic::~Graphic()
{
}
