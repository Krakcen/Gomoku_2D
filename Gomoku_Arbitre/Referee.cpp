//tmp
#include"stdafx.h"
#include <iostream>

#include "Referee.h"


/*
Doc:

return values (checkPlay):
0 : valid play
1 : Invalid Position, Stone Already Here
2 : Blue Wins
3 : Red Wins
*/

char** Referee::dupMatr(char** matr, int y, int x, char p) {
	char** tmpB;

	tmpB = new char*[19];
	for (int i = 0; i < 19; i++) {
		tmpB[i] = new char[19];
	}
	for (int k = 0; k < 19; k++) {
		for (int j = 0; j < 19; j++) {
			tmpB[k][j] = matr[k][j];
		}
	}
	tmpB[y][x] = p;
	return (tmpB);
}

int Referee::checkWin(char** board, int y, int x, char pStone) {
	int count = 1;
	int tmpY = y;
	int tmpX = x + 1;

	//Horizontal Win
	while ((tmpX < 19) && (board[tmpY][tmpX] == pStone)) {
		count++;
		if (count == 5)
			return (1);
		tmpX++;
	}
	tmpX = x - 1;
	while ((tmpX >= 0) && (board[tmpY][tmpX] == pStone)) {
		count++;
		if (count == 5)
			return (1);
		tmpX--;
	}
	count = 1;

	//Vertical Win
	tmpY = y + 1;
	tmpX = x;
	while ((tmpY < 19) && (board[tmpY][tmpX] == pStone)) {
		count++;
		if (count == 5)
			return (1);
		tmpY++;
	}
	tmpY = y - 1;
	while ((tmpY >= 0) && (board[tmpY][tmpX] == pStone)) {
		count++;
		if (count == 5)
			return (1);
		tmpY--;
	}
	count = 1;

	// \ Diagonal Win
	tmpY = y + 1;
	tmpX = x + 1;
	while ((tmpY < 19) && (tmpX < 19) && (board[tmpY][tmpX] == pStone)) {
		count++;
		if (count == 5)
			return (1);
		tmpY++;
		tmpX++;
	}
	tmpY = y - 1;
	tmpX = x - 1;
	while ((tmpY >= 0) && (tmpX >= 0) && (board[tmpY][tmpX] == pStone)) {
		count++;
		if (count == 5)
			return (1);
		tmpY--;
		tmpX--;
	}
	count = 1;

	// / Diagonal Win
	tmpY = y + 1;
	tmpX = x - 1;
	while ((tmpY < 19) && (tmpX >= 0) && (board[tmpY][tmpX] == pStone)) {
		count++;
		if (count == 5)
			return (1);
		tmpX--;
		tmpY++;
	}
	tmpY = y - 1;
	tmpX = x + 1;
	while ((tmpY >= 0) && (tmpX < 19) && (board[tmpY][tmpX] == pStone)) {
		count++;
		if (count == 5)
			return (1);
		tmpY--;
		tmpX++;
	}

	//No Win
	return (0);
}

int Referee::checkPlay(char** board, int y, int x, int p) {
	char** tmp;
	char pStone;
	int win;

	std::cout << "in progress" << std::endl;

	if (p == 0)
		pStone = 'B';
	else
		pStone = 'R';
	tmp = this->dupMatr(board, y, x, pStone);


	//Already Taken
	if (board[y][x] != '0')
		return (1);

	//Check Win
	win = this->checkWin(tmp, y, x, pStone);
	if (win == 1)
		return (p + 2);
}

Referee::Referee() {

}

Referee::~Referee() {

}