/* Author: Din Ezra
	The class represents a point object, which has 2 integer values - x coordinate, and y coordinate.
	Used for object's positions or moving directions. */

#pragma once
#include <iostream>

using namespace std;

class Point {
private:
	int x;				// X - Coordinate
	int y;				// Y - Coordinate

public:
	Point();
	Point(int, int);
	Point(const Point& other);

	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int);
	void setY(int);
	void setPoint(int, int);
	void setPoint(const Point& p);

	Point& operator = (const Point&);

	void resetPoint();
	void print() const;
};