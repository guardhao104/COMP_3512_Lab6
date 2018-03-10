#pragma once
#include "Tour.h"

class Population
{
private:
	int generation;
	int population_size;
	Tour *tour_list;
public:
	Population() : population_size(0) {};
	Population(int size, Tour tour, int shuffle_times)
	{
		init_generation();
		population_size = size;
		tour_list = new Tour[population_size];
		for (int i = 0; i < population_size; ++i)
		{
			tour.shuffle_cities(shuffle_times);
			tour_list[i] = tour;
		}
	}
	Population(const Population& orgpopulation)
	{
		population_size = orgpopulation.population_size;
		tour_list = new Tour[population_size];
		for (int i = 0; i < population_size; ++i)
		{
			tour_list[i] = orgpopulation.tour_list[i];
		}
	}
	//~Population() { delete tour_list; };
	void init_generation() { generation = 1; };
	int get_generation() const { return generation; };
	void add_generation() { ++generation; };
	Tour *get_tour() const { return tour_list; };
	void set_tour(Tour list[]) 
	{
		for (int i = 0; i < population_size; ++i)
		{
			tour_list[i] = list[i];
		}
	}

	//Get the distance of the first tour in the list.
	//As usual this should be the shortest tour in this generation after determine_shortest() function.
	//RRE		tour_list should have value
	//POST		NULL
	double get_top_distance() const
	{
		return tour_list[0].get_distance();
	}

	//Swaps the order of two tours in the population.
	//PARAM		int index
	//PARAM		int index
	//PRE		both indexes >= 0
	//PRE		both indexes < population_size
	//POST		the order of two tours in tour_list have been swapped.
	void swap_tours_order(int index_one, int index_two)
	{
		Tour temp = tour_list[index_one];
		tour_list[index_one] = tour_list[index_two];
		tour_list[index_two] = temp;
	}

	//Determine which tour has the shortest distance and move this tour to first position.
	//PRE		NULL
	//POST		the shortest tour will be moved to the first position
	//RETURN	the shortest tour in the population
	Tour determine_shortest()
	{
		int index = 0;
		double shortest_distance = tour_list[index].get_distance();
		for (int i = 1; i < population_size; ++i)
		{
			if (tour_list[i].get_distance() < shortest_distance)
			{
				index = i;
				shortest_distance = tour_list[i].get_distance();
			}
		}
		if (index != 0)
		{
			swap_tours_order(0, index);
		}
		return tour_list[0];
	}

	//Find which tour has the shortest distance in a specified range.
	//PRE		range > 0
	//PRE		range should be the size of tour_range[]
	//POST		NULL
	//RETURN	the shortest tour in the specified range
	Tour find_shortest(int range, Tour tour_range[]) const
	{
		int index = 0;
		double shortest_distance = tour_range[index].get_distance();
		for (int i = 1; i < range; ++i)
		{
			if (tour_range[i].get_distance() < shortest_distance)
			{
				index = i;
				shortest_distance = tour_range[i].get_distance();
			}
		}
		return tour_range[index];
	}

	//Select a parent by randomly choose tours and find the shortest one in this range.
	//PRE		size > 0
	//PRE		size < population_size
	//POST		NULL
	//RETURN	the shortest tour in specified range
	Tour select_parent(int size) const
	{
		Tour *candidate = new Tour[size];
		for (int i = 0; i < size; ++i)
		{
			int k = rand() % population_size;
			candidate[i] = tour_list[k];
		}
		Tour shortest = find_shortest(size, candidate);
		delete candidate;
		return shortest;
	}

	//Make a new generation as follow steps:
	//	1. Generation number add one to record current generation.
	//	2. Choose two parents from two parent pool respectively.
	//		(The size of pool can be modified.)
	//	3. Use two parents to make childs to replace tours in the list except elites.
	//		(The number of elites can be modified.)
	//	4. Make some randomly mutates except elites.
	//		(The rate of mutation can be modified.)
	//PARAM		elites is the number of tours we want keep
	//PARAM		parent_pool_size is the size of the pool we choose parent from
	//PARAM		mutation_rate is the rate for mutation, the larger the bigger
	//PRE		elites < population_size
	//PRE		elites > 0
	//PRE		parent_pool_size < population_size
	//PRE		parent_pool_size > 0
	//PRE		mutation_rate > 0
	//POST		generation will add one
	//POST		tour_list will change to new list and keep elites without edit
	void make_new_generation(int elites, int parent_pool_size, double mutation_rate)
	{
		add_generation();

		for (int i = elites; i < population_size; ++i)
		{
			Tour parent_one = select_parent(parent_pool_size);
			Tour parent_two = select_parent(parent_pool_size);
			tour_list[i] = parent_two.make_child(parent_one);
		}

		for (int i = elites; i < population_size; ++i)
		{
			for (int j = 0; j < tour_list[i].get_city_number(); ++j)
			{
				double mutates = (double)rand() / (double)RAND_MAX;
				if (mutates <= mutation_rate)
				{
					int k = rand() % tour_list[i].get_city_number();
					tour_list[i].swap_cities(j, k);
				}
			}
			tour_list[i].update_distance();
		}
	}
};