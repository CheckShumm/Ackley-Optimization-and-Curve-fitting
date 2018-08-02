/*
 * ackley.h
 *
 *  Created on: Apr 7, 2016
 *      Author: natha
 */

#ifndef ACKLEY_H_
#define ACKLEY_H_

#include <vector>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include "genetic.h"

#include <iostream>
using namespace std;

class ackley: public genetic
{

private:
	double pi = 3.14159; // define PI

	double x,y; 		// variables
	double fitness_score;		// holds fitness score

	//PRE SET variables used in general Ackley function
	double a = 20;
	double b = 0.2;
	double c = 2*pi;

	//mutation variables
	double mp = 8;
	double mr = 0.10;


public:
	ackley();
	ackley(double,double);

	void set_x(double);
	void set_y(double);

	double get_x();
	double get_y();

	void solve();
	double score();

	// define functions
	void initialize();				// initialize the population
	void fitness(vector<ackley> &);	// give fitness score to individual
	void tournament();				// select parents based on fitness level.
	void crossover();				// intermediate recombination crossover algorithm
	void mutate(ackley &);			// real valued mutation algorithm
	void generate_next();			// generates next population to be loop through the GA.

	//initial population size
		int population_size = 500;	//population size.

		// the vectors can be seen as pools/populations at different stages of the GA
		vector<ackley> population;
		vector<ackley> parent;
		vector<ackley> pool;
		vector<ackley> nextPop;
		vector<double> fitness_value;

};



#endif /* ACKLEY_H_ */
