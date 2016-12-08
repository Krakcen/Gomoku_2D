#ifndef REFEREE_H_
#define REFEREE_H_

class Referee {
public:
	char** dupMatr(char**, int, int, char);
	int checkWin(char**, int, int, char);
	int checkPlay(char**, int, int, int);
	Referee();
	~Referee();
};

#endif /* REFEREE_H_ */
