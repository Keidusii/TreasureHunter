#ifndef GAME_H
#define GAME_H

#include <iostream>
using namespace std;

class Game {
public:
	Game();

	Game(int money_set, int moves_set);

	// setters
	void setMoney(int n);

	void setMoves(int a);

	void setScore(int s);

	void setPosition(int p);

	void setChoice(int c);

	void setJuice(bool j);

	void setJuiceQ(int j);

	void setTank(bool t);

	void setTankQ(int t);
	// getters
	int getMoney();

	int getMoves();

	int getPosition();

	int getScore();

	int getEnergy();

	int getGas();

	int getChoice();

	bool getJuice();

	int getJuiceQ();

	bool getTank();

	int getTankQ();
	// other functions
	void decMove();

	void decEnergy();

	void decGas();

	void work();

	void moveForward();

	void rest();

	void visitShop();

	void visitGas();

	void menu1();

	void menu5();

	void menu10();

	void chooseMenu();

private:
	int money;
	int moves;
	int score;
	int position;
	int energy;
	int gas;
	int choice;
	int juiceQ;
	int numProfiles;
	bool juice;
	int tankQ;
	bool tank;
	bool travelerPerk;
};

class Profile {
public:
	Profile();
	Profile(string name, int games, int points);
	void setName(string name);
	string getName();
	void setGames(int games);
	int getGames();
	void setPoints(int points);
	int getPoints();
private:
	int userGames;
	int userPoints;
	string profileName;
};

void createProfile(string name);

int getProfiles();

void printProfiles();

void selectProfile(int choice);

void saveProfile();

void deleteProfile(int choice);
#endif
