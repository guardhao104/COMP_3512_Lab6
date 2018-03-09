#pragma once
#include <string>
#include <math.h>

class City {
private:
	std::string name;
	int  x_coordinate;
	int  y_coordinate;
public:
	City() : name("unknown"), x_coordinate(0), y_coordinate(0) {};
	City(std::string cname, int x, int y) : name(cname), x_coordinate(x), y_coordinate(y) {};
	City(City& org_city) : name(org_city.name), x_coordinate(org_city.x_coordinate), 
						   y_coordinate(org_city.y_coordinate) {};
	~City() {};
	void set_name(std::string newname) { name = newname; };
	void set_x(int x) { x_coordinate = x; };
	void set_y(int y) { y_coordinate = y; };
	std::string get_name() const { return name; };
	int get_x() const { return x_coordinate; };
	int get_y() const { return y_coordinate; };


	// Calculate the distance between two cities.
	// PARAM	other_city is another city which we want to know the distance from this city to.
	// PRE		other_city should have valid x and y.
	// POST		NULL
	// RETURN	the distance between two cities
	double distance(const City& other_city) const
	{
		double quadratic_x = std::pow((double)(x_coordinate - other_city.get_x()), 2.0);
		double quadratic_y = std::pow((double)(y_coordinate - other_city.get_y()), 2.0);
		return std::sqrt(quadratic_x + quadratic_y);
	}


};