#ifndef GAMEC_H_
#define GAMEC_H_

#include <vector>
#include <list>
#include <SFML/Graphics.hpp>

class GomokuA {
private:
	sf::Texture boardTexture;
	sf::Sprite boardSprite;
	sf::Texture sideboardTexture;
	sf::Sprite sideboardSprite;
	int currentP;
	std::string infoBox;
	sf::Font font;
	sf::Text playerT;

public:
	std::vector<std::vector<char> > goMatr;
	int coordMatr[19][19][2];
	sf::CircleShape stoneTab[19][19];
	sf::Vertex verTabH[57][2];
	sf::Vertex verTabV[57][2];

	int checkMouseClick(int, int);
	int displayBoard();
	sf::Text getText();
	int getPlayer();
	sf::Font getFont();
	void setPlayer(int player);
	sf::Sprite getBoard();
	sf::Sprite getSideBoard();
	GomokuA();
	~GomokuA();
};

int printG(std::string);

#endif
