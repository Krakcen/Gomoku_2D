// Gomoku_Arbitre.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameC.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int printG(std::string str) {
	std::cout << str << std::endl;
	return (0);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1100, 800), "Gomoku 2D - Don't Resize Window !");
	GomokuA* gomoku = new GomokuA();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed) {
				//std::cout << "x: " << event.mouseButton.x << "\ny: " << event.mouseButton.y << std::endl << std::endl;
				gomoku->checkMouseClick(event.mouseButton.x, event.mouseButton.y);
			}

			if (event.type == sf::Event::MouseMoved) {
		
			}
		}
		window.clear();

		/* Draw Here */
		window.draw(gomoku->getBoard());
		window.draw(gomoku->getSideBoard());

		// Draw Grid
		for (int i = 0; i < 57; i++) {
			window.draw(gomoku->verTabH[i], 2, sf::Lines);
			window.draw(gomoku->verTabV[i], 2, sf::Lines);
		}

		//Draw Stones
		for (int i = 0; i < 19; i++) {
			for (int j = 0; j < 19; j++) {
				if ((gomoku->goMatr[i][j] == 'B') || ((gomoku->goMatr[i][j] == 'R')))
					window.draw(gomoku->stoneTab[i][j]);
			}
		}
		window.draw(gomoku->getText());
		window.draw(gomoku->getInfoTText());
		window.draw(gomoku->getInfoT());
		window.display();
	}
	delete(gomoku);
    return (0);
}

