//Point.cpp
//
//by Tedo Pranowo

#pragma once

#include <ostream>
#include <istream>

struct Point
{
	int x;
	int y;

	Point();
	Point(int x1, int y1);
	Point(const Point& point);

	Point operator-(const Point& other) const;
	Point operator+(const Point& other) const;

	Point operator+=(const Point& other);
	Point operator-=(const Point& other);

	Point operator=(const Point& other);

	bool operator==(const Point& other) const;
	bool operator<=(const int other) const;

	friend std::ostream& operator << (std::ostream& output, const Point& point);
	friend std::istream& operator >> (std::istream& input, Point& point);
};

//Used for std::map
struct PointComp
{
	bool operator()(const Point& left, const Point& right);
};