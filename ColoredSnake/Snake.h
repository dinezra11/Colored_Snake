/* Author: Din Ezra
	This class represents the Snake object.
	It is inherited from the Object class, so the base variables represents the snake's head attributes.
	It also has a dynamic array of Object's objects, each member represents a part of the snake's body. */

#pragma once
#include "Object.h"

class Snake : public Object {
private:
	Object** body;			// A dynamic array for the snake's body.
	int bodySize;			// The body size. (How many members the "body" array has)
	Point direction;		// The current direction of the snake. Example: moving up = Point(0, -1), moving right = Point(1, 0)

public:
	Snake();
	Snake(int, int, char, string);
	~Snake();

	int getSize() const { return bodySize; }
	Point getPartPosition(int index) const { return body[index]->getPosition(); }		// Get interface for the position of a specific body part.
	Point getDirection() const { return direction; }
	void setDirection(int, int);
	void setSnakeColor(string);

	void addBody();
	void removeBodyPart();
	void removeBodyWhole();
	void printSnake();
	void update();
};