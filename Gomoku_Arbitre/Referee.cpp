//tmp
#include"stdafx.h"
#include <iostream>

#include "Referee.h"

//#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

/*
Doc:

{ ret_id, pair_bool, [pair x, pair y], [pair x2, pair y2], etc... }

return values (checkPlay):
0 : valid play
1 : Invalid Position, Stone Already Here
2 : Blue Wins
3 : Red Wins
*/

int* Referee::getRetPlay(int val, int* tab, int y, int x) {
	int* retV = new int[34];
	int count = 0;
	int j = 2;
	int i = 1;

	retV[0] = val;
	if (tab[0] == 0)
		retV[1] = 0;
	else {
		while (i < 9) {
			if (tab[i] == 1) {
				count++;
				if (i == 1) {
					retV[j] = x + 1;
					retV[j + 1] = y;
					retV[j + 2] = x + 2;
					retV[j + 3] = y;
				}
				else if (i == 2) {
					retV[j] = x - 1;
					retV[j + 1] = y;
					retV[j + 2] = x - 2;
					retV[j + 3] = y;
				}
				else if (i == 3) {
					retV[j] = x;
					retV[j + 1] = y - 1;
					retV[j + 2] = x;
					retV[j + 3] = y - 2;
				}
				else if (i == 4) {
					retV[j] = x;
					retV[j + 1] = y + 1;
					retV[j + 2] = x;
					retV[j + 3] = y + 2;
				}
				else if (i == 5) {
					retV[j] = x - 1;
					retV[j + 1] = y - 1;
					retV[j + 2] = x - 2;
					retV[j + 3] = y - 2;
				}
				else if (i == 6) {
					retV[j] = x - 1;
					retV[j + 1] = y + 1;
					retV[j + 2] = x - 2;
					retV[j + 3] = y + 2;
				}
				else if (i == 7) {
					retV[j] = x + 1;
					retV[j + 1] = y - 1;
					retV[j + 2] = x + 2;
					retV[j + 3] = y - 2;
				}
				else if (i == 8) {
					retV[j] = x + 1;
					retV[j + 1] = y + 1;
					retV[j + 2] = x + 2;
					retV[j + 3] = y + 2;
				}
				j = j + 4;
			}
		i++;
		}
		retV[1] = count;
		retV[j] = 42;
	}
	return (retV);
}
/*
1: H D
2: H G
3: V H
4: V B
5: D GH
6: D GB
7: D DH
8: D DB
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

int* Referee::checkPair(char** board, int y, int x, char pStone) {
	int* tab = new int[9];
	char stone;

	if (pStone == 'B')
		stone = 'R';
	if (pStone == 'R')
		stone = 'B';

	for (int i = 0; i < 9; i++) {
		tab[i] = 0;
	}

	//Horizontal Droite
	if (x <= 15) {
		if ((board[y][x + 1] == stone) && (board[y][x + 2] == stone) && (board[y][x + 3] == pStone)) {
			tab[0] = 1;
			tab[1] = 1;
		}
	}
	//Horizontal Gauche
	if (x >= 3) {
		if ((board[y][x - 1] == stone) && (board[y][x - 2] == stone) && (board[y][x - 3] == pStone)) {
			tab[0] = 1;
			tab[2] = 1;
		}
			
	}
	//Vertical Haut
	if (y >= 3) {
		if ((board[y - 1][x] == stone) && (board[y - 2][x] == stone) && (board[y - 3][x] == pStone)) {
			tab[0] = 1;
			tab[3] = 1;
		}
	}
	//Vertical Bas
	if (y <= 15) {
		if ((board[y + 1][x] == stone) && (board[y + 2][x] == stone) && (board[y + 3][x] == pStone)) {
			tab[0] = 1;
			tab[4] = 1;
		}
	}
	//Diagonale Gauche Haut
	if ((y >= 3) && (x >= 3)) {
		if ((board[y - 1][x - 1] == stone) && (board[y - 2][x - 2] == stone) && (board[y - 3][x - 3] == pStone)) {
			tab[0] = 1;
			tab[5] = 1;
		}
	}
	//Diagonale Gauche Bas
	if ((y <= 15) && (x >= 3)) {
		if ((board[y + 1][x - 1] == stone) && (board[y + 2][x - 2] == stone) && (board[y + 3][x - 3] == pStone)) {
			tab[0] = 1;
			tab[6] = 1;
		}
	}
	//Diagonale Droite Haut
	if ((y >= 3) && (x <= 15)) {
		if ((board[y - 1][x + 1] == stone) && (board[y - 2][x + 2] == stone) && (board[y - 3][x + 3] == pStone)) {
			tab[0] = 1;
			tab[7] = 1;
		}
	}
	//Diagonale Droite Bas
	if ((y <= 15) && (x <= 15)) {
		if ((board[y + 1][x + 1] == stone) && (board[y + 2][x + 2] == stone) && (board[y + 3][x + 3] == pStone)) {
			tab[0] = 1;
			tab[8] = 1;
		}
	}

	return (tab);
}

int* Referee::checkPlay(char** board, int y, int x, int p) {
	char** tmp;
	int* tab;
	int* tabRet;
	char pStone;
	int win;

	if (p == 0)
		pStone = 'B';
	else
		pStone = 'R';
	tmp = this->dupMatr(board, y, x, pStone);

	//Check Pair
	tab = this->checkPair(tmp, y, x, pStone);

	//Already Taken
	if (board[y][x] != '0') {
		return (getRetPlay(1, tab, y, x));
	}

	//Check Win
	win = this->checkWin(tmp, y, x, pStone);
	if (win == 1)
		return (this->getRetPlay(p + 2, tab, y, x));

	return (this->getRetPlay(0, tab, y, x));
}

Referee::Referee() {

}

Referee::~Referee() {

}