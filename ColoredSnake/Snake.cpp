// Author: Din Ezra

#include "Snake.h"

Snake::Snake() : Object(), direction()
{
	// Default Constructor

	this->body = nullptr;
	this->bodySize = 0;
}

Snake::Snake(int xCord, int yCord, char symbol, string colorName) : Object(xCord, yCord, symbol, colorName), direction()
{
	// Constructor with parameters - Initialize the Snake!

	this->body = nullptr;
	this->bodySize = 0;
}

Snake::~Snake()
{
	// Destructor! Release the memory allocated for the body.

	for (int i = 0; i < bodySize; i++)
		if (body[i])
			delete body[i];
	
	delete[] body;
}

void Snake::setDirection(int xDir, int yDir)
{
	// Set interface for the direction (2 integer parameters)

	this->direction.setPoint(xDir, yDir);
}

void Snake::setSnakeColor(string colorName)
{
	// Change the color of the whole snake (head and body).

	this->setColor(colorName);
	for (int i = 0; i < bodySize; i++)
		body[i]->setColor(colorName);
}

void Snake::addBody()
{
	/* Add a body part to the "body" array.
		The position of the new part will be the position of the last previous part. */

	if (bodySize > 0) {
		Object** temp = new Object*[bodySize + 1];
		for (int i = 0; i < bodySize; i++)
			temp[i] = new Object(*body[i]);

		// Build the new body part.
		temp[bodySize] = new Object(*body[bodySize - 1]);

		// Release memory for previouse body and update it to the new one.
		for (int i = 0; i < bodySize; i++)
			delete body[i];
		delete[] body;

		body = temp;
		bodySize++;
	}
	else {
		// Make the first body part!
		body = new Object*[1];
		body[0] = new Object(*this);
		bodySize = 1;
	}
}

void Snake::removeBodyPart()
{
	// Remove the last body part.

	if (bodySize > 0) {
		delete body[bodySize - 1];
		bodySize--;
	}
}

void Snake::removeBodyWhole()
{
	// Remove the WHOLE snake's body.

	while (bodySize > 0)
		removeBodyPart();
}

void Snake::printSnake()
{
	// Print the head and the body of the snake.

	Object::print();

	for (int i = 0; i < bodySize; i++)
		body[i]->print();
}

void Snake::update()
{
	// Update the snake's position according to its direction.
	if (bodySize > 0) {
		for (int i = bodySize - 1; i > 0; i--)
			body[i]->setPosition(body[i - 1]->getPosition());

		body[0]->setPosition(this->getPosition());
	}

	/* Add the direction's coordinates to the position's coordinates.
		Action performed with the operator += defined in Point class. */
	this->setPosition(this->getPosition().getX() + this->getDirection().getX(), this->getPosition().getY() + this->getDirection().getY());
}
