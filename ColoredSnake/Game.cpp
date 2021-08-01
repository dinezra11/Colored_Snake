// Author: Din Ezra

#include "Game.h"

Game::Game() : snake(0, 0, 'O', ""), food(0, 0, '*', "")
{
	// Default Constructor, getting the screen's size

	CONSOLE_SCREEN_BUFFER_INFO screenBuffer;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screenBuffer);
	windowWidth = (int)(screenBuffer.srWindow.Right - screenBuffer.srWindow.Left);
	windowHeight = (int)(screenBuffer.srWindow.Bottom - screenBuffer.srWindow.Top + 1);
	
	activeBlocks = 0;
	isGameOn = false;
	srand(time(nullptr));		// Initialize random generator
}

void Game::initializeGame()
{
	/* ************************
	   * Initialize the game! *
	   ************************ */

	// Reset snake from previous session
	snake.setPosition(windowWidth / 2, windowHeight / 2);
	snake.setDirection(0, 1);
	snake.setSnakeColor("");
	snake.removeBodyWhole();

	resetObject(food, "");

	activeBlocks = 0;
	isGameOn = true;
}

void Game::play()
{
	int action = menu();

	if (action == PLAY) {
		// Game is On!

		initializeGame();

		thread controllerThread(getPlayerInput, &snake, &isGameOn);
		thread blocksThread(generateBlocks, block, &activeBlocks, snake.getColor(), &isGameOn, windowWidth, windowHeight);
		while (isGameOn) {
			// Game Loop

			system("cls");
			printGame();
			this_thread::sleep_for(5ms);
			snake.update();
			collisionDetection();
		} // Game Loop

		system("cls");
		cout << COLOR_RESET << "Game over! Your score is: " << snake.getSize() << endl;
		cout << "Game has ended. Please wait a few moments for the program to terminate safely." << endl;
		blocksThread.join();			// Wait for the thread to finish
		cout << "Press any key to quit. Thanks for playing :)" << endl;
		controllerThread.join();		// Wait for the thread to finish
	}
	else if (action == EXIT) {
		system("cls");
		cout << COLOR_RESET << "Thank you for playing the game! :)" << endl;
	}
}

int Game::menu()
{
	// Implementation of the game's main menu.

	int option = 1;
	bool menuOn = true;

	while (menuOn) {
		system("cls");
		printTitle();
		printMenu(option);
		
		switch (_getch()) {
		case 'W':
		case 'w': option--;
			break;
		case 'S':
		case 's': option++;
			break;
		case 32: if (option == PLAY || option == EXIT) menuOn = false;
			   else if (option == RULES) printRules();
			   else if (option == CREDITS) printCredits();
			break;
		}

		// Keep option inside menu boundries.
		if (option > EXIT)
			option = PLAY;
		if (option < PLAY)
			option = EXIT;
	}

	return option;
}

void Game::printTitle() const
{
	// Print the title of the game.

	cout << TITLE_COLOR << "\t\tColored Snake Game!" << endl;
	cout << "\tChoose an option from the menu below" << endl << endl;
}

void Game::printMenu(int option) const
{
	// Print the options of the menu.
	// The color of the text depends on the current option.

	if (option == PLAY)
		cout << CHOOSE_COLOR << " > ";
	else
		cout << OPTION_COLOR << "   ";
	cout << "Play!" << endl;

	if (option == RULES)
		cout << CHOOSE_COLOR << " > ";
	else
		cout << OPTION_COLOR << "   ";
	cout << "How To Play" << endl;

	if (option == CREDITS)
		cout << CHOOSE_COLOR << " > ";
	else
		cout << OPTION_COLOR << "   ";
	cout << "Credits" << endl;

	if (option == EXIT)
		cout << CHOOSE_COLOR << " > ";
	else
		cout << OPTION_COLOR << "   ";
	cout << "Exit" << endl;

	cout << endl << TITLE_COLOR << "Use 'w' (up) and 's' (down) to navigate. (Space to choose)" << endl;
}

void Game::printRules() const
{
	// Print the "How to Play" page.

	system("cls");
	printTitle();
	cout << REGULAR_COLOR << "This is a unique Snake game." << endl;
	cout << "Your hungry snake has a very specific type of food that he desires to eat, represented by a certain color." << endl;
	cout << "Your goal is to help your snake to eat as many * as he can have! Enjoy :) " << endl;
	cout << "Use the keys 'w', 's', 'd', 'a' to control the snake. Don't forget to avoid obsticles!" << endl;
	cout << endl << "Press enter to go back to the menu.." << endl;
	getchar();
}

void Game::printCredits() const
{
	// Print a brief explanation about who created this game.

	system("cls");
	printTitle();
	cout << REGULAR_COLOR << "The game has been programmed in C++ language, by Din Ezra." << endl;
	cout << "Thank you very much for playing the game and I hope you enjoy!" << endl;
	cout << endl << "Press enter to go back to the menu.." << endl;
	getchar();
}

void Game::printGame()
{
	// Print all game's components

	snake.printSnake();
	food.print();
	for (int i = 0; i < activeBlocks; i++)
		block[i].print();
}

void Game::resetObject(Object& obj, string color)
{
	// Reset an object (food/obsticle) and set its position randomaly.

	obj.setPosition((rand() % windowWidth - 1) + 2, (rand() % windowHeight - 1) + 1);
	obj.setSymbol('*');
	obj.setColor(color);
}

bool Game::checkCollision2Points(Point pos1, Point pos2) const
{
	// Collision detection. Return true if both objects are at the same position.

	if (pos1.getX() == pos2.getX() && pos1.getY() == pos2.getY())
		return true;

	return false;
}

void Game::collisionDetection()
{
	/* Collision Detection function!
	   All of the collision related logic are implemented here.
	   isGameOver will be set to 'false' if game over has been detected. */
	Point snakePos = snake.getPosition();

	// Check collision between Snake & Food
	if (checkCollision2Points(snakePos, food.getPosition())) {
		snake.addBody();
		resetObject(food, snake.getColor());
		if (rand() % 10 == 5) {
			snake.setSnakeColor(Game::generateRandomColor(snake.getColor()));
			food.setColor(snake.getColor());
		}
	}

	// Check collision between Snake & Blocks
	for (int i = 0; i < activeBlocks; i++) {
		if (checkCollision2Points(snakePos, block[i].getPosition())) {
			if (snake.getColor() == block[i].getColor()) {
				snake.addBody();
				resetObject(block[i], snake.getColor());
			}
			else
				isGameOn = false;
		}
	}

	// Check collision between Snake & Snake's Body
	for (int i = 0; i < snake.getSize() - 2; i++)
		if (checkCollision2Points(snakePos, snake.getPartPosition(i)))
			isGameOn = false;

	// Check collision between Snake & Screen's Borders
	if (snakePos.getX() < 0 || snakePos.getX() > windowWidth || snakePos.getY() < 0 || snakePos.getY() == windowHeight)
		isGameOn = false;
}

void Game::getPlayerInput(Snake* player, bool* isGameOn)
{
	// Get player's input while the game is running. -> This method will run on different thread.

	while ((*isGameOn)) {
		switch (_getch())
		{
		case 'w':
		case 'W':
			player->setDirection(0, -1); // Go Up
			break;

		case 's':
		case 'S':
			player->setDirection(0, 1); // Go Down
			break;

		case 'a':
		case 'A':
			player->setDirection(-1, 0); // Go Left
			break;

		case 'd':
		case 'D':
			player->setDirection(1, 0); // Go Right
			break;
		default: *isGameOn = false;
			break;
		}
	}
}

void Game::generateBlocks(Object block[MAX_BLOCKS], int* activeBlocks, string snakeColor, bool* isGameOn, int winWidth, int winHeight)
{
	// Generating the blocks, in random color and random position. -> This method will run on different thread.
	// The player will need to avoid touching them.

	// At the start of the game - generate the blocks.
	if ((*activeBlocks) == 0) {
		for (int i = 0; i < MAX_BLOCKS; i++) {
			block[i].setPosition((rand() % winWidth - 1) + 2, (rand() % winHeight - 1) + 1);
			block[i].setSymbol('*');
			block[i].setColor(generateRandomColor(snakeColor));
			(*activeBlocks)++;

			if (!(*isGameOn))
				break;
			this_thread::sleep_for(3s);
		}
	}

	// While the game is running, tranfer the blocks to another location, one by one.
	int j = 0;
	while ((*isGameOn)) {
		if (j >= MAX_BLOCKS)
			j = 0;

		block[j].setPosition((rand() % winWidth - 1) + 2, (rand() % winHeight - 1) + 1);
		block[j].setColor(generateRandomColor(snakeColor));

		j++;

		if (!(*isGameOn))
			break;
		this_thread::sleep_for(3s);
	}
}

string Game::generateRandomColor(string snakeColor)
{
	// Generating and return a random color name.
	// Don't return the snake of the color, because it is the valid food color.

	string color;

	do {
		switch (rand() % 8) {
		case 1: color = COLOR_RED;
			break;
		case 2: color = COLOR_GREEN;
			break;
		case 3: color = COLOR_YELLOW;
			break;
		case 4: color = COLOR_BLUE;
			break;
		case 5: color = COLOR_PURPLE;
			break;
		case 6: color = COLOR_CYAN;
			break;
		default: color = COLOR_RESET;
			break;
		}
	} while (color == snakeColor);

	return color;
}