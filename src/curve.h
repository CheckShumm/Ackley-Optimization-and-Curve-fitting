/*
 * curve.h
 *
 *  Created on: Apr 7, 2016
 *      Author: natha
 */

#ifndef CURVE_H_
#define CURVE_H_

#include <vector>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include "genetic.h"

#include <iostream>
using namespace std;

class curve: public genetic
{
private:

	char choice;
	double fitness_score;		// holds fitness score

	//PRE SET variables used in general curve function
	double a,b,c,d;

	//mutation variables
	double mp = 12;
	double mr = 0.005;

public:
	curve();

	curve(double,double,double,double);	//used to set a,b,c,d values


		void solve(double []);
		double score();
		void optimal();

		// define functions
		// define functions
		void initialize();				// initialize the population
		void fitness(vector<curve> &);	// give fitness score to individual
		void tournament();				// select parents based on fitness level.
		void crossover();				// intermediate recombination crossover algorithm
		void mutate(curve &);			// real valued mutation algorithm
		void generate_next();			// generates next population to be loop through the GA.

		void join();	//joins the parent and offspring pool
		void clean();	//cleans the vectors to be reused in the GA


	//GETTERS AND SETTERS
	double getA() const {
		return a;
	}

	void setA(double a) {
		this->a = a;
	}

	double getB() const {
		return b;
	}

	void setB(double b) {
		this->b = b;
	}

	double getC() const {
		return c;
	}

	void setC(double c) {
		this->c = c;
	}

	double getD() const {
		return d;
	}

	void setD(double d) {
		this->d = d;
	}

		//initial population size
		int population_size = 300;


		// the vectors can be seen as pools/populations at different stages of the GA
		vector<curve> population;
		vector<curve> parent;
		vector<curve> pool;
		vector<curve> nextPop;
		vector<double> fitness_value;

		double *y = new double [20];


};



#endif /* CURVE_H_ */
