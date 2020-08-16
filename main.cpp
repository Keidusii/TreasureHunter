#include <iostream>
using namespace std;

#include <cmath>
#include <string>
#include "Game.h"
#include <fstream>

int printMenu();
int checkInput(int input);
void instructions();
int playGame(int difficulty);

// global variable high score
int highScore = 0;

// global variable for profile
Profile user;

//global variable for profile selected
bool profileSelected = false;
// Functions for game


int main() {
	cout << "TREASURE HUNTER" << endl;
	if (getProfiles() == 0 && !profileSelected) {
		string name = "";
		cout << "Enter Name: ";
		cin >> name;
		createProfile(name);
		profileSelected = true;
	}
	else {
		while (!profileSelected) {
			cout << "Choose profile: " << endl;
			printProfiles();
			int choice = 0;
			cin >> choice;
			while (choice < 1 || choice > getProfiles() + 2) {
				cout << "Invalid input. Try Again!" << endl;
				cout << "Choose profile: " << endl;
				cin >> choice;
			}
			if (choice == getProfiles() + 1) {
				string name = "";
				cout << "Enter Name: ";
				cin >> name;
				createProfile(name);
				profileSelected = true;
			}
			else if (choice == getProfiles() + 2) {
				int choice;
				cout << "Enter profile number you want to delete: ";
				cin >> choice;
				while (choice < 1 || choice > getProfiles()) {
					cout << "Invalid input. Try Again!" << endl;
					cout << "Enter profile number you want to delete: ";
					cin >> choice;
				}
				deleteProfile(choice);
				profileSelected = false;
			}
			else {
				selectProfile(choice);
				profileSelected = true;
			}
			
		}
	}
	system("cls");
	int choice = printMenu();
	system("cls");
	if (choice == 1) {
		int difficulty;
		cout << "1) Easy" << endl << "2) Medium" << endl << "3) Hard" << endl;
		cout << "Choose difficulty: ";
		cin >> difficulty;
		while (difficulty < 1 || difficulty > 3) {
			cout << "invalid input. Enter 1, 2, or 3." << endl;
			cin >> difficulty;
		}
			system("cls");
		playGame(difficulty);
	}
	else if (choice == 3) {
		cout << "STATS FOR " << user.getName() << ":" << endl;
		cout << "Games Played: " << user.getGames() << endl;
		cout << "Points: " << user.getPoints() << endl;
		system("pause");
		main();
	}
	else {
		instructions();
		main();
	}

	return 0; 
}

// Prints the menu and returns menu choice
int printMenu() {
	cout << "Welcome " << user.getName() << "!" << endl;
	cout << "TREASURE HUNTER" << endl;
	cout << "1) Play Game" << endl;
	cout << "2) Instructions" << endl;
	cout << "3) View Stats" << endl;
	cout << "Enter 1, 2, or 3" << endl;
	int menuChoice;
	cin >> menuChoice;
	int validChoice = checkInput(menuChoice);
	cout << endl << endl << endl << endl;
	return validChoice;
}

// Makes sure the menu choice is a valid input
int checkInput(int input) {
	while (input != 1 && input != 2 && input != 3) {
		cout << "Invalid Input" << endl << "Enter 1, 2, or 3" << endl;
		cin >> input;
	}
	return input;
}
 
// Prints the instructions
void instructions() {
	cout << "The goal is to get to position 35. You start at position 1. You get 10 Points every move." << endl <<
		 "Easy: 60 moves (final score * 0.50)" << endl << "Medium: 50 Moves (final score * 1.00)" << endl << "Hard: 40 moves (final score * 1.50)" << endl <<
		"You start out with 0 money, 5 energy, and 6 gas. The max amount of energy you can have is 5. The max gas is 6." << endl <<
		"At every move, you can harvest work, rest, or move forward. Working gives you $15 but spends 1 energy." << endl <<
		"Resting recharges energy by 3 spots. Moving forward moves you up one position but spends 1 gas." << endl <<
		"If you try to move forward but you are out of gas, you cannot move forward, and you will be charged" << endl <<
		"$75 and your tank will be full." << endl <<
		"If you do not have $35 you cannot move forward. If you run out of energy, you cannot work." << endl <<
		"Every 10 moves, you can visit a shop" << endl <<
		"Shop items -" << endl <<
		"1.	Juice($60): increases energy capacity by 2" << endl <<
		"2.	Bigger Tank($60): increases gas capacity by 2" << endl <<
		"3.	Extra moves($50/move): gives an extra move" << endl <<
		"4.	Traveler perk($75): each time you move forward, you move forward one extra position" << endl <<
		"Every 5 moves, you can visit a gas station. Gas cost $30 to fill the tank" << endl <<
		"You get 500 points for reaching position 10, 2500 for reaching position 20, and 10000 for reaching position 30." << endl <<
		"You get 50000 for winning the game." << endl <<
		"If win, Final score = score + money + moves * 1000" << endl <<
		"If lose, Final score = score" << endl << endl;

	system("pause");
	system("cls");

}

// Runs the game
int playGame(int difficulty) {
	Game game;
	if (difficulty == 1) {
		game.setMoves(60);
	}
	else if (difficulty == 2) {
		game.setMoves(50);
	}
	else {
		game.setMoves(40);
	}
	while (game.getPosition() > 0 && game.getPosition() <= 35) {
		if (game.getPosition() < 35) {
			// prints stats of each round
			cout << "Position: " << game.getPosition() << endl;
			cout << "Moves: " << game.getMoves() << endl;
			cout << "Money: $" << game.getMoney() << endl;
			cout << "Gas: " << game.getGas() << " moves" << endl;
			cout << "Energy: " << game.getEnergy() << " moves" << endl << endl;

			game.chooseMenu();

			cout << "-------------------------------------------" << endl << endl;
			// decreases moves by one
			game.decMove();

			// ends game if player runs out of moves
			if (game.getMoves() <= 0 && game.getPosition() != 35) {
				game.setPosition(0);
			}

			// adding 10 points and dollars after each move
			game.setScore(game.getScore() + 10);
		}
		// adding point for reaching milestones
		if (game.getPosition() == 10) {
			game.setScore(game.getScore() + 500);
		}

		if (game.getPosition() == 20) {
			game.setScore(game.getScore() + 2500);
		}

		if (game.getPosition() == 30) {
			game.setScore(game.getScore() + 10000);
		}
		// wins game if position == 35
		if (game.getPosition() >= 35) {
			game.setScore(game.getScore() + 50000 + (game.getMoves() * 1000));
			cout << "Congratulations! You win!" << endl;
			game.setPosition(0);
		}

		system("cls");
		
		
	}
	// sets multiplier for difficulties
	if (difficulty == 1) {
		game.setScore(game.getScore() * 0.50);
	}
	else if (difficulty == 3) {
		game.setScore(game.getScore() * 1.50);
	}
	// sets high score
	if (highScore < game.getScore()) {
		highScore = game.getScore();
	}
	user.setPoints(user.getPoints() + game.getScore());
	user.setGames(user.getGames() + 1);
	cout << "Saving, Please Wait..." << endl;
	saveProfile();
	cout << "Profile Saved" << endl;
	cout << "Game Over" << endl << "You Score: " << game.getScore() << endl
		<< "High score: " << highScore << endl << endl;
	cout << "Enter 1 to play again or 2 to stop playing" << endl;
	int reset;
	cin >> reset;
	if (reset == 1) {
		main();
	}
	else {
		cout << "Thanks for playing Treasure Hunter!" << endl;
		system("pause");
	}
	return 0;
}


	Game::Game() {
		money = 0;
		moves = 50;
		score = 0;
		position = 1;
		energy = 5;
		gas = 6;
		juiceQ = 0;
		juice = false;
		tankQ = 0;
		tank = false;
		travelerPerk = false;
	}
	
	Game::Game(int money_set, int moves_set) {
		money = money_set;
		moves = moves_set;
		score = money;
	}

	// setters
	void Game::setMoney(int n) {
		money = n;
	}

	void Game::setMoves(int a) {
		moves = a;
	}

	void Game::setScore(int s) {
		score = s;
	}

	void Game::setPosition(int p) {
		position = p;
	}

	void Game::setChoice(int c) {
		choice = c;
	}

	void Game::setJuice(bool j) {
		juice = j;
	}

	void Game::setJuiceQ(int j) {
		juiceQ = j;
	}

	void Game::setTank(bool t) {
		tank = t;
	}

	void Game::setTankQ(int t) {
		tankQ = t;
	}

	// getters
	int Game::getMoney() {
		return money;
	}
	
	int Game::getMoves() {
		return moves;
	}

	int Game::getScore() {
		return score;
	}

	int Game::getPosition() {
		return position;
	}

	int Game::getEnergy() {
		return energy;
	}

	int Game::getGas() {
		return gas;
	}

	int Game::getChoice() {
		return choice;
	}

	bool Game::getJuice() {
		return juice;
	}

	int Game::getJuiceQ() {
		return juiceQ;
	}

	bool Game::getTank() {
		return tank;
	}

	int Game::getTankQ() {
		return tankQ;
	}

	// Other functions
	void Game::decMove() {
		moves--;
	}

	void Game::decEnergy() {
		energy--;
	}

	void Game::decGas() {
		gas--;
	}

	void Game::work() {
		if (energy > 0) {
			money += 15;
			decEnergy();
		}
		else {
			cout << "You do not have enough energy, pick a different option." << endl;
			chooseMenu();
		}
	}

	void Game::moveForward() {
		if (gas > 0) {
			if (travelerPerk == true) {
				position += 2;
				decGas();
			}
			else {
				position++;
				decGas();
			}
		}
		else {
			int yesOrNo;
			if (money >= 75) {
				cout << "You do not have enough gas, would you like to pay the fee of $75 to fill up the tank?" << endl <<
					"1. Yes" << endl << "2. No" << endl << "Choice: ";
				cin >> yesOrNo;
				if (yesOrNo == 1) {
					if (travelerPerk == true) {
						money -= 75;
						gas = 6;
						position += 2;
					}
					else {
						money -= 75;
						gas = 6;
						position++;
					}
				}
				else {
					cout << "You do not have enough gas, pick a different option." << endl;
					chooseMenu();
				}
			}
			else {
				cout << "You do not have enough gas, pick a different option." << endl;
				chooseMenu();
			}
		}
	}

	void Game::rest() {
		if (getJuice() == true) {
			int maxEnergy = 5;
			maxEnergy += (2 * juiceQ);
			
			if (energy >= (maxEnergy - 3)) {
				energy = maxEnergy;
			}
			else {
				energy += 3;
			}
		}
		else {
			if (energy >= 2) {
				energy = 5;
			}
			else {
				energy += 3;
			}
		}
	}

	void Game::visitShop() {
		cout << "What would you like to buy?" << endl;
		cout << "1. Juice ($60) - Increases energy capacity by 2." << endl;
		cout << "2. Bigger Tank ($60) - Increases gas capacity by 2." << endl;
		cout << "3. Extra Moves ($50/move) - Gives you an extra move." << endl;
		if (travelerPerk == false) {
			cout << "4. Traveler Perk ($100) - Move forward double the positions." << endl;
		}
		cout << "5. Leave shop." << endl;
		cout << "You have $" << money << endl;
		cout << "Choice: ";
		int buy;
		cin >> buy;

		if (buy == 1) {
			if (money >= 60) {
				money -= 60;
				juice = true;
				juiceQ++;
				int maxEnergy = 5;
				maxEnergy += (2 * juiceQ);
				energy += 2;
				cout << "You have purchased Juice." << endl << endl;
				visitShop();
			}
			else {
				cout << "Insufficient funds. Choose another option.";
				visitShop();
			}
		}
		else if (buy == 2) {
			if (money >= 60) {
				money -= 60;
				tank = true;
				tankQ++;
				int maxGas = 6;
				maxGas += (2 * tankQ);
				gas += 2;
				cout << "You have purchased Bigger Tank." << endl << endl;
				visitShop();
			}
			else {
				cout << "Insufficient funds. Choose another option.";
				visitShop();
			}
		}
		else if (buy == 3) {
			int num = 0;
			cout << "How many moves would you like to buy?" << endl;
			cin >> num;
			if (money >= (50 * num)) {
				money -= (50 * num);
				moves += (num + 1);
				cout << "You have purchased " << num << " extra moves." << endl << endl;
				visitShop();
			}
			else {
				cout << "Insufficient funds. Choose another option.";
				visitShop();
			}
		}
		else if (buy == 4) {
			if (money >= 100) {
				money -= 100;
				travelerPerk = true;
				cout << "You have purchased Traveler Perk." << endl << endl;
				visitShop();
			}
			else {
				cout << "Insufficient funds. Choose another option.";
				visitShop();
			}
		}
	}

	void Game::visitGas() {
		if (getTank() == true) {
			if (money >= 30) {
				money -= 30;
				gas = 6 + (2 * tankQ);
				cout << "You filled your tank for $30." << endl;
			}
			else {
				cout << "You do not have enough money, pick a different option" << endl;
				chooseMenu();
			}
		}
		else {
			if (money >= 30) {
				money -= 30;
				gas = 6;
				cout << "You filled your tank for $30." << endl;
			}
			else {
				cout << "You do not have enough money, pick a different option" << endl;
				chooseMenu();
			}
		}
	}

	void Game::menu1() {
		cout << "What would you like to do?" << endl;
		cout << "1. Work" << endl << "2. Move forward" << endl << "3. Rest" << endl;
		cout << "Enter 1, 2, or 3" << endl;
		cout << "Choice: ";
		int choice;
		cin >> choice;
		setChoice(choice);
		if (getChoice() == 1) {
			work();
		}
		else if (getChoice() == 2) {
			moveForward();
		}
		else {
			rest();
		}
		cout << endl << endl;
	}

	void Game::menu5() {
		cout << "What would you like to do?" << endl << endl;
		cout << "1. Work" << endl << "2. Move Forward" << endl << "3. Rest" << endl << "4. Visit Gas Station" << endl;
		cout << "Enter 1, 2, 3, or 4" << endl;
		cout << "Choice: ";
		int choice;
		cin >> choice;
		setChoice(choice);
		if (getChoice() == 1) {
			work();
		}
		else if (getChoice() == 2) {
			moveForward();
		}
		else if (getChoice() == 3) {
			rest();
		}
		else if (getChoice() == 4) {
			visitGas();
		}
		cout << endl << endl;
	}

	void Game::menu10() {
		cout << "What would you like to do?" << endl;
		cout << "1. Work" << endl << "2. Move forward" << endl << "3. Rest" << endl << "4. Visit Gas Station" << endl
			<< "5. Visit Shop" << endl;
		cout << "Enter 1, 2, 3, 4, or 5" << endl;
		cout << "Choice: ";
		int choice;
		cin >> choice;
		setChoice(choice);
		if (getChoice() == 1) {
			work();
		}
		else if (getChoice() == 2) {
			moveForward();
		}
		else if (getChoice() == 3) {
			rest();
		}
		else if (getChoice() == 4) {
			visitGas();
		}
		else {
			visitShop();
		}
		cout << endl << endl;
	}

	void Game::chooseMenu() {
		// prints menu for every 10 turns
		if (getMoves() % 10 == 0) {
			menu10();
		}
		// prints for every 5 turns thats not divisible by 10
		else if (getMoves() % 5 == 0) {
			menu5();
		}
		// prints menu for every turn thats not divisible by 5 or 10
		else {
			menu1();
		}
	}
	//Profiles
	Profile::Profile() {
		profileName = "";
		userGames = 0;
		userPoints = 0;
	}

	Profile::Profile(string name, int games, int points) {
		profileName = name;
		userGames = games;
		userPoints = points;
	}

	void Profile::setName(string name) {
		profileName = name;
	}

	string Profile::getName() {
		return profileName;
	}

	void Profile::setGames(int games) {
		userGames = games;
	}

	int Profile::getGames() {
		return userGames;
	}

	void Profile::setPoints(int points) {
		userPoints = points;
	}

	int Profile::getPoints() {
		return userPoints;
	}

	void createProfile(string name) {
		user.setName(name);
		user.setGames(0);
		user.setPoints(0);
		ofstream profiles;
		ofstream p;
		ifstream pro;
		ifstream p2;
		string n;
		int games;
		int points;

		// format: name games points
		pro.open("profiles.txt");
		profiles.open("protemp.txt");
		while (pro >> n >> games >> points) {
			profiles << n << " " << games << " " << points << "\n";
		}
		pro.close();
		profiles.close();
		p.open("profiles.txt");
		p2.open("protemp.txt");
		while (p2 >> name >> games >> points) {
			p << name << " " << games << " " << points << "\n";
		}
		p << user.getName() << " " << user.getGames() << " " << user.getPoints() << "\n";
		p.close();
		p2.close();
	}

	int getProfiles() {
		ifstream profiles;
		profiles.open("profiles.txt");
		int count = 0;
		string name;
		int games;
		int points;
		while (profiles >> name >> games >> points) {
			count++;
		}
		profiles.close();
		return count;
	}

	void printProfiles() {
		ifstream profiles;
		profiles.open("profiles.txt");
		string name;
		int games;
		int points;
		int count = 1;
		while (profiles >> name >> games >> points) {
				cout << count << ") ";
				cout << name << endl;
				count++;
		}
		profiles.close();
		cout << count << ") Create new profile" << endl;
		count++;
		cout << count << ") Delete Profile" << endl;
	}
	
	void selectProfile(int choice) {
		ifstream profiles;
		profiles.open("profiles.txt");
		string name;
		int games;
		int points;
		int count = 0;
		while (count != choice) {
			profiles >> name >> games >> points;
			count++;
		}
		user.setName(name);
		user.setGames(games);
		user.setPoints(points);
	}

	void saveProfile() {
		ofstream profiles;
		ifstream profiles1;
		ofstream p0;
		ifstream p1;
		profiles1.open("profiles.txt");
		profiles.open("protemp.txt");

		string name = user.getName();
		int games = user.getGames();
		int points = user.getPoints();
		profiles << name << " " << games << " " << points << endl;
		while (profiles1 >> name >> games >> points) {
			if (name != user.getName()) {
				profiles << name << " " << games << " " << points << endl;
			}
		}
		profiles.close();
		profiles1.close();
		p1.open("protemp.txt");
		p0.open("profiles.txt");
		while (p1 >> name >> games >> points) {
			p0 << name << " " << games << " " << points << endl;
		}
		p1.close();
		p0.close();
	}

	void deleteProfile(int choice) {
		ofstream profiles;
		ofstream p;
		ifstream pro;
		ifstream p2;
		string n;
		int games;
		int points;
		string junkName;
		int junkGames;
		int junkPoints;
		// format: name games points
		pro.open("profiles.txt");
		profiles.open("protemp.txt");
		for (int i = 1; i < choice; i++) {
			pro >> n >> games >> points;
			profiles << n << " " << games << " " << points << "\n";
		}
		pro >> junkName >> junkGames >> junkPoints;
		while (pro >> n >> games >> points) {
			profiles << n << " " << games << " " << points << "\n";
		}
		pro.close();
		profiles.close();
		p.open("profiles.txt");
		p2.open("protemp.txt");
		while (p2 >> n >> games >> points) {
			p << n << " " << games << " " << points << "\n";
		}
		p.close();
		p2.close();
	}