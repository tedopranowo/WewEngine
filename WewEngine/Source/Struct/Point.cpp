#include "Point.h"

Point::Point()
	: Point{ 0, 0 }
{
}

Point::Point(int x1, int y1)
	: x{ x1 }
	, y{ y1 }
{
}

Point::Point(const Point & point)
	: Point{ point.x, point.y }
{
}

Point Point::operator-(const Point & other) const
{
	return Point(this->x - other.x, this->y - other.y);
}

Point Point::operator+(const Point & other) const
{
	return Point(this->x + other.x, this->y + other.y);
}

Point Point::operator+=(const Point & other)
{
	this->x += other.x;
	this->y += other.y;

	return *this;
}

Point Point::operator-=(const Point & other)
{
	this->x -= other.x;
	this->y -= other.y;

	return *this;
}

Point Point::operator=(const Point & other)
{
	this->x = other.x;
	this->y = other.y;

	return *this;
}

bool Point::operator==(const Point & other) const
{
	return (this->x == other.x) && (this->y == other.y);
}

bool Point::operator<=(const int other) const
{
	int squaredDistance = x*x + y*y;
	return squaredDistance <= (other*other);
}

std::ostream & operator<<(std::ostream & output, const Point & point)
{
	output << point.x << ' ' << point.y;
	return output;
}

std::istream & operator >> (std::istream & input, Point& point)
{
	input >> point.x >> point.y;
	return input;
}

bool PointComp::operator()(const Point & left, const Point & right)
{
	return (left.y < right.y) || ((left.y == right.y) && (left.x < right.x));
}
