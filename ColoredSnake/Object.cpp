// Author: Din Ezra

#include "Object.h"

Object::Object() : position(0, 0)
{
	// Default Constructor

	this->symbol = ' ';
	setColor("reset");
}

Object::Object(int xCord, int yCord, char symbol, string colorName) : position(xCord, yCord)
{
	// Constructor with parameters (2 integers as position)

	this->symbol = symbol;
	setColor(colorName);
}

Object::Object(Point pos, char symbol, string colorName) : position(pos)
{
	// Constructor with parameters (Point as position)

	this->symbol = symbol;
	setColor(colorName);
}

Object::Object(const Object& other)
{
	this->symbol = other.symbol;
	this->position = other.position;
	this->color = other.color;
}

void Object::setSymbol(char symbol)
{
	// Set interface for symbol

	this->symbol = symbol;
}

void Object::setPosition(Point newPosition)
{
	// Set interface for position (Point parameter)

	this->position.setPoint(newPosition.getX(), newPosition.getY());
}

void Object::setPosition(int xCord, int yCord)
{
	// Set interface for position (2 integer parameters)

	this->position.setPoint(xCord, yCord);
}

void Object::setColor(string colorName)
{
	// Set interface for color (string parameter)

	this->color = getColorCode(colorName);
}

Object& Object::operator=(const Object& other)
{
	// Copy operator definition for Object's objects

	if (this != &other) {
		this->symbol = other.getSymbol();
		this->position.setPoint(other.getPosition().getX(), other.getPosition().getY());		// Copy the position with the operator= definition from Point.h
		this->color = other.getColor();
	}

	return *this;
}

void Object::print()
{
	// Set the output position according to object's position.
	printPosition.X = this->position.getX();
	printPosition.Y = this->position.getY();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), printPosition);

	// Print the object's symbol with it's color.
	cout << color << symbol;
}

string Object::getColorCode(string colorName)
{
	// Return the ANSI code of the desired color.

	if (colorName == "red" || colorName == COLOR_RED)
		return COLOR_RED;
	else if (colorName == "green" || colorName == COLOR_GREEN)
		return COLOR_GREEN;
	else if (colorName == "yellow" || colorName == COLOR_YELLOW)
		return COLOR_YELLOW;
	else if (colorName == "blue" || colorName == COLOR_BLUE)
		return COLOR_BLUE;
	else if (colorName == "purple" || colorName == COLOR_PURPLE)
		return COLOR_PURPLE;
	else if (colorName == "cyan" || colorName == COLOR_CYAN)
		return COLOR_CYAN;
	else
		return COLOR_RESET;
}
