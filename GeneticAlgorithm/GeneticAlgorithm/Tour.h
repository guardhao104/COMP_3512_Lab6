#pragma once
#include "City.h"

class Tour {
private:
	double distance;
	int city_number;
	City **permutation;
public:
	Tour() : distance(0), city_number(0)
	{
		permutation = new City*[0];
	};
	Tour(int citys, City city_permutation[])
	{
		city_number = citys;
		permutation = new City*[city_number];
		for (int i = 0; i < city_number; ++i)
		{
			permutation[i] = &(city_permutation[i]);
		}
		update_distance();
	};
	Tour(int citys, City* city_permutation[])
	{
		city_number = citys;
		permutation = new City*[city_number];
		for (int i = 0; i < city_number; ++i)
		{
			permutation[i] = city_permutation[i];
		}
		update_distance();
	}
	Tour(const Tour& orgtour)
	{
		distance = orgtour.distance;
		city_number = orgtour.city_number;
		permutation = new City*[city_number];
		for (int i = 0; i < city_number; ++i)
		{
			permutation[i] = (orgtour.permutation[i]);
		}
	}
	~Tour() { delete[] permutation; };
	double get_distance() const { return distance; };
	int get_city_number() const { return city_number; };
	Tour& operator=(Tour src)
	{
		using std::swap;
		swap(distance, src.distance);
		swap(city_number, src.city_number);
		swap(permutation, src.permutation);
		return *this;
	}

	//Calculate the total distance traveled on the specified tour of cities.
	//PRE		permutation should contains a set of city_number cities
	//POST		distance will be updated
	void update_distance()
	{
		double alldistance = 0.0;
		for (int i = 0; i < city_number; ++i)
		{
			alldistance += permutation[i]->distance(*permutation[(i + 1) % city_number]);
		}
		distance = alldistance;
	}

	//Shuffles the cities in this tour of cities.
	//PARAM		shuffle_times is the argument that how many times should a city be shuffled
	//PRE		shuffles > 0
	//POST		the cities in tour have been shuffled
	void shuffle_cities(int shuffle_times)
	{
		for (int i = 0; i < shuffle_times; ++i)
		{
			int index_one = rand() % city_number;
			int index_two = rand() % city_number;
			swap_cities(index_one, index_two);
		}
		update_distance();
	}

	//Swaps the cities at the specified indices in the permutation.
	//PARAM		int index
	//PARAM		int index
	//PRE		both indices >= 0
	//PRE		both indices < city_number
	//POST		the cities at the specified indices in the permutation have been swapped.
	void swap_cities(int index_one, int index_two)
	{
		City* temp = permutation[index_one];
		permutation[index_one] = permutation[index_two];
		permutation[index_two] = temp;
	}

	//Make new tour by combo with anohter tour.
	//PARAM		another tour that give first part of cities
	//PRE		two tours should have same size on cities
	//POST		NULL
	//RETURN	a new tour as a child of two tours
	Tour make_child(const Tour& companion) const
	{
		Tour child = Tour(city_number, permutation);
		int boundary_index = rand() % city_number;
		for (int i = boundary_index; i < city_number; ++i)
		{
			int index = 0;
			int flag = 1;
			while (flag)
			{
				flag = 0;
				for (int j = 0; j < i; ++j)
				{
					if (companion.permutation[index] == child.permutation[j])
					{
						++index;
						flag = 1;
						break;
					}
				}
			}
			child.permutation[i] = companion.permutation[index];
		}
		child.update_distance();
		return child;
	}
};