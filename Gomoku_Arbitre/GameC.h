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
	sf::Font font;
	sf::Text playerT;
	sf::Text infoT;
	sf::Text infoTitle;
	sf::Color* infoE = new sf::Color(217, 83, 79);
	sf::Color* infoS = new sf::Color(92, 184, 92);
	sf::Color* infoW = new sf::Color(240, 173, 78);

public:
	std::vector<std::vector<char> > goMatr;
	int coordMatr[19][19][2];
	sf::CircleShape stoneTab[19][19];
	sf::Vertex verTabH[57][2];
	sf::Vertex verTabV[57][2];

	int checkMouseClick(int, int);
	void changeInfoText(std::string, std::string);
	int displayBoard();
	sf::Text getText();
	sf::Text getInfoT();
	sf::Text getInfoTText();
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
