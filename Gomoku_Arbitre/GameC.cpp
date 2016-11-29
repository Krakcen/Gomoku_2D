#include "stdafx.h"
#include "GameC.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int GomokuA::checkMouseClick(int x, int y) {

	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			if ((x < this->coordMatr[i][j][0] + 13) && (x > this->coordMatr[i][j][0] - 13) && (y < this->coordMatr[i][j][1] + 13) && (y > this->coordMatr[i][j][1] - 13)) {
				//Before Checking
				sf::CircleShape circle(200);
				this->stoneTab[i][j] = circle;
				this->stoneTab[i][j].setRadius(13);
				this->stoneTab[i][j].setPointCount(100);
				this->stoneTab[i][j].setPosition(this->coordMatr[i][j][0] - 12, this->coordMatr[i][j][1] - 12);
				if (this->getPlayer() == 0) {
					this->goMatr[i][j] = 'B';
					this->setPlayer(1);
					this->stoneTab[i][j].setFillColor(sf::Color(0, 255, 255));

					this->playerT.setString("Red Turn");
					this->playerT.setFillColor(sf::Color(255, 0, 0));
				}
				else {
					this->goMatr[i][j] = 'R';
					this->setPlayer(0);
					this->stoneTab[i][j].setFillColor(sf::Color(255, 0, 0));

					this->playerT.setString("Blue Turn");
					this->playerT.setFillColor(sf::Color(0, 255, 255));
				}
				this->displayBoard();
				return (0);
			}
		}
	}
	return (1);
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

sf::Font GomokuA::getFont() {
	return (this->font);
}

sf::Text GomokuA::getText() {
	return (this->playerT);
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
	this->playerT.setFont(this->font);
	this->playerT.setString("Blue Turn");
	this->playerT.setCharacterSize(40);
	this->playerT.setFillColor(sf::Color(0, 255, 255));
	this->playerT.setStyle(sf::Text::Bold);
	this->playerT.setPosition(860, 90);


	//Init Go Matrix
	this->goMatr.resize(19);
	for (int i = 0; i < 19; ++i)
		this->goMatr[i].resize(19);
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			this->goMatr[i][j] = '0';
		}
	}

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
	std::cout << "Bye";
}
