#pragma once
#include "City.h"

class Tour {
private:
	double fitness;
	int city_number;
	City *permutation;
public:
	Tour() : fitness(0), city_number(0) {};
	Tour(int citys, City city_permutation[])
	{
		fitness = 0;
		city_number = citys;
		permutation = new City[city_number];
		for (int i = 0; i < city_number; ++i)
		{
			permutation[i] = city_permutation[i];
		}
	};
	Tour(const Tour& orgtour)
	{
		fitness = orgtour.fitness;
		city_number = orgtour.city_number;
		permutation = new City[city_number];
		for (int i = 0; i < city_number; ++i)
		{
			permutation[i] = orgtour.permutation[i];
		}
	}
	~Tour() { delete permutation; };

	//Return the total distance traveled on the specified tour of cities.
	//PRE		permutation should contains a set of city_number cities
	//POST		NULL
	//RETURN	the total distance as a double
	double total_distance() const
	{
		double distance = 0.0;
		for (int i = 0; i < city_number; ++i)
		{
			distance += permutation[i].distance(permutation[(i + 1) % city_number]);
		}
		return distance;
	}

	//Shuffles the cities in this tour of cities.
	//PARAM		shuffles is the argument that how far should a city be shuffled
	//PRE		shuffles > 0
	//POST		the cities in tour have been shuffled
	void shuffle_cities(int shuffles)
	{
		for (int i = 0; i < shuffles; ++i)
		{
			int index_one = rand() % city_number;
			int index_two = rand() % city_number;
			swap_cities(index_one, index_two);
		}
	}

	//Swaps the cities at the specified indices in the permutation.
	//PARAM		int index
	//PARAM		int index
	//PRE		both indices >= 0
	//PRE		both indices < city_number
	//POST		the cities at the specified indices in the permutation have been swapped.
	void swap_cities(int index_one, int index_two)
	{
		City temp = permutation[index_one];
		permutation[index_one] = permutation[index_two];
		permutation[index_two] = temp;
	}

};