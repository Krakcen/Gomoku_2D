#include "stdafx.h"
#include "GameC.h"

#include "PyLoader.h"

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Referee.h"

int GomokuA::checkIAPlay() {
	int x;
	int y;
	int* result;

	this->pl->PyLoadFunction("main");
	this->pl->PyCallFunction(PyTuple_Pack(0, NULL));
	int* xy = pl->PyReturnFunctionTuple();
	x = xy[0];
	y = xy[1];

	Referee r;
	result = r.checkPlay(this->vectorToChar(this->goMatr), y, x, this->getPlayer());
	if (result[0] == 1) {
		std::cout << "Invalid Play: Stone Already Here" << std::endl;
		this->changeInfoText("Stone Already Here", "ERROR");
		return (1);
	}
	/*if (result[0] == 0) {
		this->changeInfoText("", "SUCCESS");
	}*/
	if (result[1] != 0) {
		int j = 2;
		int k = 0;
		k = result[1];
		while (k > 0) {
			this->setPairR();
			//tmp
			std::cout << "[IA] pair nb: " << this->getPairR() << std::endl;

			//remove
			this->goMatr[result[j + 1]][result[j]] = '0';
			this->goMatr[result[j + 3]][result[j + 2]] = '0';

			this->pl->PyLoadFunction("delete_pion");
			this->pl->PyCallFunction(PyTuple_Pack(2, PyLong_FromLong(j), PyLong_FromLong(j + 1)));
			this->pl->PyCallFunction(PyTuple_Pack(2, PyLong_FromLong(j + 3), PyLong_FromLong(j + 4)));

			j = j + 4;
			k--;
		}
		this->changeInfoText("Pair Captured", "SUCCESS");
		if (this->getPairR() >= 5) {
			this->changeInfoText("IA Won (5 Pairs) !", "SUCCESS");
			this->end = 1;
			this->playerT.setString("Game Over");
			this->playerT.setFillColor(sf::Color(255, 255, 255));
			this->playerT.setPosition(840, 90);
			this->end = 1;
		}
	}
	if (result[0] == 3) {
		this->changeInfoText("IA Won !", "ERROR");
		this->playerT.setString("Game Over");
		this->end = 1;
		this->playerT.setFillColor(sf::Color(255, 255, 255));
		this->playerT.setPosition(840, 90);
	}

	this->goMatr[y][x] = 'R';

	sf::CircleShape circle(200);
	this->stoneTab[y][x] = circle;
	this->stoneTab[y][x].setRadius(13);
	this->stoneTab[y][x].setPointCount(100);
	this->stoneTab[y][x].setPosition(this->coordMatr[y][x][0] - 12, this->coordMatr[y][x][1] - 12);
	this->stoneTab[y][x].setFillColor(sf::Color(255, 0, 0));
	
	if (this->end == 0) {
		this->playerT.setString("Your Turn");
		this->playerT.setFillColor(sf::Color(0, 255, 255));
	}		
	this->setPlayer(0);
	return (0);
}

int GomokuA::checkMouseClick(int x, int y) {
	int* result;

	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			if ((x < this->coordMatr[i][j][0] + 13) && (x > this->coordMatr[i][j][0] - 13) && (y < this->coordMatr[i][j][1] + 13) && (y > this->coordMatr[i][j][1] - 13)) {
				//Checking
				Referee r;

				result = r.checkPlay(this->vectorToChar(this->goMatr), i, j, this->getPlayer());
				if (result[0] == 1) {
					std::cout << "Invalid Play: Stone Already Here" << std::endl;
					this->changeInfoText("Stone Already Here", "ERROR");
					return (1);
				}
				if (result[0] == 0) {
					this->changeInfoText("", "SUCCESS");
				}
				//Pair
				if (result[1] != 0) {
					int j = 2;
					int k = 0;
					k = result[1];
					while (k > 0) {
						this->setPairB();

						//remove
						this->goMatr[result[j + 1]][result[j]] = '0';
						this->goMatr[result[j + 3]][result[j + 2]] = '0';

						this->pl->PyLoadFunction("delete_pion");
						this->pl->PyCallFunction(PyTuple_Pack(2, PyLong_FromLong(j), PyLong_FromLong(j + 1)));
						this->pl->PyCallFunction(PyTuple_Pack(2, PyLong_FromLong(j + 3), PyLong_FromLong(j + 4)));

						j = j + 4;
						k--;
					}
					this->changeInfoText("Pair Captured", "SUCCESS");
					if (this->getPairB() >= 5) {
						this->changeInfoText("You Won (5 Pairs) !", "SUCCESS");
						this->end = 1;
						this->playerT.setString("Game Over");
						this->playerT.setPosition(840, 90);
						this->playerT.setFillColor(sf::Color(255, 255, 255));
					}
				}
				if (result[0] == 2) {
					this->changeInfoText("You Won (5 Aligned) !", "SUCCESS");
					this->end = 1;
					this->playerT.setString("Game Over");
					this->playerT.setPosition(840, 90);
					this->playerT.setFillColor(sf::Color(255, 255, 255));
				}

				sf::CircleShape circle(200);
				this->stoneTab[i][j] = circle;
				this->stoneTab[i][j].setRadius(13);
				this->stoneTab[i][j].setPointCount(100);
				this->stoneTab[i][j].setPosition(this->coordMatr[i][j][0] - 12, this->coordMatr[i][j][1] - 12);
				this->goMatr[i][j] = 'B';
				this->setPlayer(1);
				this->stoneTab[i][j].setFillColor(sf::Color(0, 255, 255));
				if (this->end == 0) {
					this->playerT.setString("IA Turn");
					this->playerT.setFillColor(sf::Color(255, 0, 0));
				}
				this->pl->PyLoadFunction("put_player_pion");
				this->pl->PyCallFunction(PyTuple_Pack(2, PyLong_FromLong(j), PyLong_FromLong(i)));

				return (0);
			}
		}
	}
	return (1);
}

int** GomokuA::vecToInt(std::vector < std::vector<char> > matr) {
	int** intMatr;

	intMatr = new int*[19];
	for (int i = 0; i < 19; i++) {
		intMatr[i] = new int[19];
	}
	for (int k = 0; k < 19; k++) {
		for (int j = 0; j < 19; j++) {
			if (matr[k][j] == 'B')
				intMatr[k][j] = 1;
			else if (matr[k][j] == 'R')
				intMatr[k][j] = 2;
			else
				intMatr[k][j] = 0;
		}
	}
	return (intMatr);
}

char** GomokuA::vectorToChar(std::vector < std::vector<char> > matr) {
	char** charMtr;

	charMtr = new char*[19];
	for (int i = 0; i < 19; i++) {
		charMtr[i] = new char[19];
	}
	for (int k = 0; k < 19; k++) {
		for (int j = 0; j < 19; j++) {
			charMtr[k][j] = matr[k][j];
		}
	}
	return (charMtr);
}

int GomokuA::displayBoard() {
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			std::cout << this->goMatr[i][j] << " ";
		}
		std::cout << std::endl;
	}
	return (0);
}

void GomokuA::changeInfoText(std::string text, std::string type) {
	if (type == "ERROR") {
		this->infoT.setString(text);
		this->infoT.setFillColor(*this->infoE);
	}
	else if (type == "SUCCESS") {
		this->infoT.setString(text);
		this->infoT.setFillColor(*this->infoS);
	}
	else {
		this->infoT.setString(text);
		this->infoT.setFillColor(*this->infoW);
	}
}

//Pair
void GomokuA::setPairB() {
	this->pairB++;
}
void GomokuA::setPairR() {
	this->pairR++;
}

int GomokuA::getPairB() {
	return (this->pairB);
}
int GomokuA::getPairR() {
	return (this->pairR);
}
//

sf::Font GomokuA::getFont() {
	return (this->font);
}

sf::Text GomokuA::getInfoTText() {
	return (this->infoTitle);
}

sf::Text GomokuA::getInfoT() {
	return (this->infoT);
}

sf::Text GomokuA::getText() {
	return (this->playerT);
}

sf::Text GomokuA::getEndText() {
	return (this->endT);
}

int GomokuA::getPlayer() {
	return (this->currentP);
}

void GomokuA::setPlayer(int player) {
	this->currentP = player;
}

sf::Sprite GomokuA::getBoard() {
	return (this->boardSprite);
}

sf::Sprite GomokuA::getSideBoard() {
	return (this->sideboardSprite);
}


//Constructor
GomokuA::GomokuA() {
	//Init Player
	this->currentP = 0;

	//Init Font
	if (!this->font.loadFromFile("Fh_Space.otf"))
	{
		// error...
	}

	//Init Texts
	this->endT.setFont(this->font);
	this->endT.setString("Game Over");
	this->endT.setCharacterSize(40);
	this->endT.setFillColor(sf::Color(192, 192, 192));
	this->endT.setStyle(sf::Text::Bold);
	this->endT.setPosition(900, 500);

	this->playerT.setFont(this->font);
	this->playerT.setString("Your Turn");
	this->playerT.setCharacterSize(40);
	this->playerT.setFillColor(sf::Color(0, 255, 255));
	this->playerT.setStyle(sf::Text::Bold);
	this->playerT.setPosition(860, 90);

	this->infoTitle.setFont(this->font);
	this->infoTitle.setString("Info");
	this->infoTitle.setCharacterSize(40);
	this->infoTitle.setFillColor(sf::Color(252, 181, 20));
	this->infoTitle.setStyle(sf::Text::Bold);
	this->infoTitle.setPosition(900, 500);

	this->infoT.setFont(this->font);
	this->infoT.setCharacterSize(20);
	this->infoT.setString("");
	this->infoT.setPosition(850, 600);

	//Init Pair
	this->pairB = 0;
	this->pairR = 0;

	//Init Go Matrix
	this->goMatr.resize(19);
	for (int i = 0; i < 19; ++i)
		this->goMatr[i].resize(19);
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			this->goMatr[i][j] = '0';
		}
	}

	//Init End
	this->end = 0;

	//Init Coord Matrix
	int cx = 40;
	int cy = 40;
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			this->coordMatr[i][j][0] = cx;
			this->coordMatr[i][j][1] = cy;
			cx = cx + 40;
		}
		cx = 40;
		cy = cy + 40;
	}

	//Init Sprites
	if (!this->boardTexture.loadFromFile("space_texture.jpg"))
		printG("couldnt load space texture");
	if (!this->sideboardTexture.loadFromFile("sideboard_texture.jpg"))
		printG("couldnt load sideboard texture");

	this->boardSprite.setTexture(this->boardTexture);
	this->sideboardSprite.setTexture(this->sideboardTexture);
	this->sideboardSprite.setPosition(sf::Vector2f(800, 0));

	//Init Grid
	float x1 = 40;
	float y1 = 40;
	float y2 = 40;
	float x2 = 760;
	int j = 0;
	for (int i = 0; i < 19; i++) {
		this->verTabH[j][0] = sf::Vertex(sf::Vector2f(x1, y1));
		this->verTabH[j][1] = sf::Vertex(sf::Vector2f(x2, y2));

		this->verTabH[j + 1][0] = sf::Vertex(sf::Vector2f(x1, y1 - 1));
		this->verTabH[j + 1][1] = sf::Vertex(sf::Vector2f(x2, y2 - 1));

		this->verTabH[j + 2][0] = sf::Vertex(sf::Vector2f(x1, y1 + 1));
		this->verTabH[j + 2][1] = sf::Vertex(sf::Vector2f(x2, y2 + 1));
		y1 = y1 + 40;
		y2 = y2 + 40;
		j = j + 3;
	}
	x1 = 40;
	y1 = 40;
	x2 = 40;
	y2 = 760;
	j = 0;
	for (int i = 0; i < 19; i++) {
		this->verTabV[j][0] = sf::Vertex(sf::Vector2f(x1, y1));
		this->verTabV[j][1] = sf::Vertex(sf::Vector2f(x2, y2));

		this->verTabV[j + 1][0] = sf::Vertex(sf::Vector2f(x1 - 1, y1));
		this->verTabV[j + 1][1] = sf::Vertex(sf::Vector2f(x2 - 1, y2));

		this->verTabV[j + 2][0] = sf::Vertex(sf::Vector2f(x1 + 1, y1));
		this->verTabV[j + 2][1] = sf::Vertex(sf::Vector2f(x2 + 1, y2));
		x1 = x1 + 40;
		x2 = x2 + 40;
		j = j + 3;
	}

}

GomokuA::~GomokuA() {
	delete (this->infoE);
	delete (this->infoS);
	delete (this->infoW);
	std::cout << "Bye";
}
