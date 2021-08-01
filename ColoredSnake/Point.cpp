// Author: Din Ezra

#include "Point.h"

Point::Point()
{
	// Default Constructor

	this->x = 0;
	this->y = 0;
}

Point::Point(int xCord, int yCord)
{
	// Constructor with parameters

	setPoint(xCord, yCord);
}

Point::Point(const Point& other)
{
	// Copy Constructor

	setPoint(other);
}

void Point::setX(int xCord)
{
	// Set interface for X coordinate.

	this->x = xCord;
}

void Point::setY(int yCord)
{
	// Set interface for Y coordinate.

	this->y = yCord;
}

void Point::setPoint(int xCord, int yCord)
{
	// Set the object's coordinates to match the parameters.

	setX(xCord);
	setY(yCord);
}

void Point::setPoint(const Point& p)
{
	// Copy the parameter's coordinates into the object's.

	setX(p.getX());
	setY(p.getY());
}

Point& Point::operator=(const Point& other)
{
	// Copy operator definition for Point objects

	if (this != &other)
		this->setPoint(other);

	return *this;
}

void Point::resetPoint()
{
	// Reset the coordinates to (0, 0).

	this->x = 0;
	this->y = 0;
}

void Point::print() const
{
	// Print the coordinates details as a string. Format: "(x, y)"

	cout << "(" << x << ", " << y << ")";
}
