/* Author: Din Ezra
	The class represents an object. It has a position (Point object), a symbol to print (char) and a color code (string).
	Use the print() method to print this object into the console screen, according to its position, symbol and color. */

#pragma once
#include <iostream>
#include <string>
#include "Windows.h"
#include "Point.h"
#include "Colors.h"

class Object {
private:
	char symbol;					// The "graphics" of the object.
	Point position;					// The position where we want the object to be printed.
	string color;					// The color code of the object, presented in ANSI code.
	COORD printPosition;			// For changing the output position on screen.

public:
	Object();
	Object(int, int, char, string);
	Object(Point, char, string);
	Object(const Object& other);

	static string getColorCode(string);

	char getSymbol() const { return symbol; }
	Point getPosition() const { return position; }
	string getColor() const { return color; }
	void setSymbol(char);
	void setPosition(Point);
	void setPosition(int, int);
	void setColor(string);

	Object& operator= (const Object&);

	void print();
};