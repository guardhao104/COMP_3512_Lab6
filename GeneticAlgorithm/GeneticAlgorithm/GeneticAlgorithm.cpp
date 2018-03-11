#include "Population.h"
#include <iostream>
#include <ctime>
#include <iomanip>

#define CITIES_IN_TOUR	  20
#define POPULATION_SIZE	  30
#define MAP_BOUNDARY      1000    // Size of the map (X and Y)
#define SHUFFLES          32      // A shuffle consists of swaps

#define ITERATIONS        1000    // Number of loops for the algorithm
#define NUMBER_OF_ELITES  1       // The number of 'fittest' that remain
#define PARENT_POOL_SIZE  5       // Number of members randomly selected
#define MUTATION_RATE     0.15    // Chance of being mutated

using namespace std;

int main()
{
	City city_list[CITIES_IN_TOUR];
	string city_name[CITIES_IN_TOUR] = { "A", "B", "C", "D", "E", "F", "G", "H", 
		"I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T" };
	Population population;
	Tour best_tour;
	double best_distance;

	/* Declares and defines the master list of all the cities that we need to visit.
	The cities are named 'A', 'B', ... , and they each have a random X and Y
	coordinate */
	for (int i = 0; i < CITIES_IN_TOUR; ++i) {
		int x = rand() % (MAP_BOUNDARY + 1);
		int y = rand() % (MAP_BOUNDARY + 1);
		city_list[i] = City(city_name[i], x, y);
	}

	/* Seeds the random number generator.  When we want to generate random numbers
	in C, we start by seeding the pseudo-random number generator.  In this case,
	we are feeding it the time function as the seed.  We almost always do this. */
	srand(time(NULL));

	/* Initalize population and get start. */
	Tour tour = Tour(CITIES_IN_TOUR, city_list);
	population = Population(POPULATION_SIZE, tour, SHUFFLES);
	best_tour = population.determine_shortest();
	best_distance = best_tour.get_distance();
	cout << "Shortest distance in initial population: ";
	cout << setw(8) << fixed << setprecision(3) << best_distance << endl;

	/* Loop for doing algorithm. */
	while (population.get_generation() < ITERATIONS) 
	{
		population.make_new_generation(NUMBER_OF_ELITES, PARENT_POOL_SIZE, MUTATION_RATE);
		best_tour = population.determine_shortest();
		if (best_distance != best_tour.get_distance())
		{
			best_distance = best_tour.get_distance();
			cout << "New distance: ";
			cout << setw(8) << fixed << setprecision(3) << best_distance << endl;
		}
	}

	/* Get the lastest solution. */
	cout << "Shortest distance: ";
	cout << setw(8) << fixed << setprecision(3) << population.get_top_distance() << endl;

	system("pause");
	return 0;
}