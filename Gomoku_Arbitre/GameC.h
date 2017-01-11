#ifndef GAMEC_H_
#define GAMEC_H_

#include "PyLoader.h"

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
	sf::Font font;
	sf::Text playerT;
	sf::Text infoT;
	sf::Text infoTitle;
	sf::Text endT;
	sf::Color* infoE = new sf::Color(217, 83, 79);
	sf::Color* infoS = new sf::Color(92, 184, 92);
	sf::Color* infoW = new sf::Color(240, 173, 78);

	int pairB;
	int pairR;

public:
	PyLoader* pl;

	int end;
	std::vector<std::vector<char> > goMatr;
	int coordMatr[19][19][2];
	sf::CircleShape stoneTab[19][19];
	sf::Vertex verTabH[57][2];
	sf::Vertex verTabV[57][2];

	int** vecToInt(std::vector < std::vector<char> > matr);
	char** vectorToChar(std::vector < std::vector<char> > matr);
	int checkIAPlay();
	int checkMouseClick(int, int);
	void changeInfoText(std::string, std::string);
	int displayBoard();
	int getPairB();
	int getPairR();
	void setPairB();
	void setPairR();
	sf::Text getText();
	sf::Text getInfoT();
	sf::Text getInfoTText();
	sf::Text getEndText();
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
