#pragma once
#include "Tour.h"

class Population
{
private:
	static int generation;
	int gen_size;
	Tour *tour_list;
public:
	Population() : gen_size(0) {};
	Population(int size, Tour list[])
	{
		++generation;
		gen_size = size;
		tour_list = new Tour[gen_size];
		for (int i = 0; i < gen_size; ++i)
		{
			tour_list[i] = list[i];
		}
	}
	Population(const Population& orgpopulation)
	{
		gen_size = orgpopulation.gen_size;
		tour_list = new Tour[gen_size];
		for (int i = 0; i < gen_size; ++i)
		{
			tour_list[i] = orgpopulation.tour_list[i];
		}
	}
	~Population() { delete tour_list; };


};