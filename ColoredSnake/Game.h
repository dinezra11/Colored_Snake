/* Author: Din Ezra
	This is the main class of the game.
	It holds all of the components and logic of the game.
	It has 2 main parts:	- The main menu
							- The actual game
	In the actual game, there will be a different thread created in order to scan the input from the user while continue updating the game. */

#pragma once
#include <iostream>
#include <random>
#include <conio.h>				// For getch() function.
#include <windows.h>			// For getting the size of the console.
#include <thread>				// For creating a new thread for synchronized methods.
#include "Snake.h"
#include "Object.h"
#include "Colors.h"

// Game Constants
#define REFRESH_TIME 500						// The refresh time, in milliseconds
#define MAX_BLOCKS 5

// Menu Constants
#define REGULAR_COLOR COLOR_RESET
#define TITLE_COLOR COLOR_GREEN
#define OPTION_COLOR COLOR_CYAN
#define CHOOSE_COLOR COLOR_PURPLE
enum MENU_OPTIONS { PLAY = 1, RULES, CREDITS, EXIT };

using namespace std;
using namespace std::literals::chrono_literals;					// The namespace that holds the time constants. (seconds, milliseconds, etc..)

class Game {
private:
	// Game Variables and Constants
	int windowWidth;						// Game window's width
	int windowHeight;						// Game window's height

	// Game Objects
	Snake snake;
	Object food;
	Object block[MAX_BLOCKS];
	int activeBlocks;						// Sets how many blocks are active to be printed out.
	bool isGameOn;							// True if the game is in action, False if the game ends

public:
	Game();
	
	void play();

private:
	// Private Methods (So they won't be able to be called outside of the Game class)
	int menu();
	void printTitle() const;
	void printMenu(int option) const;
	void printRules() const;
	void printCredits() const;

	void initializeGame();
	void printGame();
	void resetObject(Object&, string);
	bool checkCollision2Points(Point pos1, Point pos2) const;
	void collisionDetection();

	// Static methods for managing game flow. Those method will be excecuted on a multiple threads.
	static void getPlayerInput(Snake*, bool*);
	static void generateBlocks(Object*, int*, string, bool*, int, int);
	static string generateRandomColor(string);
};