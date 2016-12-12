#include "stdafx.h"
#include "GameC.h"
#include <iostream>
#include <SFML/Graphics.hpp>

#include "lua/src/lua.hpp"

#include "Referee.h"

int createArray(lua_State *L, int** board) {
	lua_createtable(L, 19, 0);
	for (int i = 0; i < 19; i++) {
		lua_createtable(L, 19, 0);
	}
	/* Puts key of the first child table on-top of Lua VM stack: */
	lua_pushnumber(L, 1);

	/*Creates first child table of size 3 non-array elements: */
	lua_createtable(L, 0, 3);

	/* Fills the first child table: */
	lua_pushnumber(L, 1);
	lua_setfield(L, -2, "field1");

	lua_pushnumber(L, 2);
	/* setfield() pops the value from Lua VM stack. */
	lua_setfield(L, -2, "field2");

	lua_pushnumber(L, 3);
	lua_setfield(L, -2, "field3");

	/* Remember, child table is on-top of the stack.
	* lua_settable() pops key, value pair from Lua VM stack. */
	lua_settable(L, -3);

	/* Pushes they key value for the second child table: */
	lua_pushnumber(L, 2);

	/*Creates second child table of size  3 non-array elements: */
	lua_createtable(L, 0, 3);

	/* Fills the second child table: */
	lua_pushnumber(L, 10);
	lua_setfield(L, -2, "field1");

	lua_pushnumber(L, 20);
	lua_setfield(L, -2, "field2");

	lua_pushnumber(L, 30);
	lua_setfield(L, -2, "field3");

	/* Remember, child table is still on-top of the stack.
	* lua_settable pops the key, value pair from Lua VM stack
	* And puts child table into the parent. */
	lua_settable(L, -3);

	/* Returns number of output tables:
	* (1 multidimentional)            */
	return 1;
}

int GomokuA::checkIAPlay() {

/*	this->goMatr[i][j] = 'R';
	this->setPlayer(0);
	this->stoneTab[i][j].setFillColor(sf::Color(255, 0, 0));

	this->playerT.setString("Blue Turn");
	this->playerT.setFillColor(sf::Color(0, 255, 255));*/
	int **board;

	board = this->vecToInt(this->goMatr);
	lua_State *lua_state;
	lua_state = luaL_newstate();

	luaL_dofile(lua_state, "ia.lua");
	lua_getglobal(lua_state, "ia");
	lua_getglobal(lua_state, "search");
	lua_createtable(lua_state, 19, 0);



	lua_close(lua_state);

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
				if (result[0] == 2) {
					this->changeInfoText("BLUE Wins !", "SUCCESS");
				}
				if (result[0] == 3) {
					this->changeInfoText("RED Wins !", "SUCCESS");
				}

				sf::CircleShape circle(200);
				this->stoneTab[i][j] = circle;
				this->stoneTab[i][j].setRadius(13);
				this->stoneTab[i][j].setPointCount(100);
				this->stoneTab[i][j].setPosition(this->coordMatr[i][j][0] - 12, this->coordMatr[i][j][1] - 12);
				this->goMatr[i][j] = 'B';
				this->setPlayer(1);
				this->stoneTab[i][j].setFillColor(sf::Color(0, 255, 255));
				this->playerT.setString("Red Turn");
				this->playerT.setFillColor(sf::Color(255, 0, 0));
				//this->displayBoard();
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

sf::Sprite GomokuA::getEndScreen() {
	return (this->endScreenSprite);
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
	if (!this->endScreenTexture.loadFromFile("endscreen.png"))
		printG("couldnt load endscreen texture");

	this->boardSprite.setTexture(this->boardTexture);
	this->sideboardSprite.setTexture(this->sideboardTexture);
	this->sideboardSprite.setPosition(sf::Vector2f(800, 0));
	this->endScreenSprite.setTexture(this->endScreenTexture);

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
