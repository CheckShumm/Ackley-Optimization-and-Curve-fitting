/*
 * genetic.h
 *
 *  Created on: Apr 7, 2016
 *      Author: natha
 */

#ifndef GENETIC_H_
#define GENETIC_H_

#include <vector>
#include <ctime>
#include <cmath>
#include <cstdlib>

#include <iostream>
using namespace std;

class genetic
{
protected:

	double fitness_score;	// stoes the fitness score of an individual
	double mr;				// mutation range
	double mp;				// mutation precesion
	int population_size;	// size of the population

public:

	// define functions
	virtual void initialize() = 0;		// initialize the population
	virtual void tournament() = 0;		// select parents based on fitness level.
	virtual void crossover() = 0;		// intermediate recombination crossover algorithm
	virtual void generate_next() = 0;	// generates next population to be loop through the GA.


};



#endif /* GENETIC_H_ */
