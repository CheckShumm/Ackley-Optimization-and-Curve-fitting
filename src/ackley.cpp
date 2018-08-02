/*
 * ackley.cpp
 *
 *  Created on: Apr 7, 2016
 *      Author: natha
 */


#include <vector>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include "ackley.h"
#include <algorithm>

#include <iostream>
using namespace std;

ackley::ackley()
{
	x = 0;
	y = 0;
	fitness_score = 0;
	mp = 8;
	mr = 0.10;
	population_size = 500;
}


ackley::ackley(double x, double y)
{
	this-> x = x;
	this-> y = y;
	population_size = 500;
	mp = 8;
	mr = 0.10;
}

// *********** Initialize Population ************** \\

void ackley::initialize()
{
	double newX;
	double newY;

	srand(time(NULL));

	for(int i=0; i<population_size; i++)
	{

		newX = (double)(rand()%60)-30;
		newY = (double)(rand()%60)-30;

		ackley test(newX,newY);

		population.push_back(test);

	}

}

// *********** Fitness ************\\

void ackley::fitness(vector<ackley> &group)
{
	for(int i =0; i <group.size(); i++)
	{
		/*fitness score
		 * the function "solve" will solve the function for all individuals
		 * of the population and assign a fitness score to them.
		 */
		group[i].solve();


	}
}


// ******** Tournament ************* \\

void ackley::tournament()
{
	//tournament contestant ids
	int id1, id2, id3;

	//randomly select contestants.

	id1 = rand()%population.size();
	id2 = rand()%population.size();
	id3 = rand()%population.size();

	if((population[id1].score() < population[id2].score()) && (population[id1].score() < population[id3].score()))
	{
		 parent.push_back(population[id1]);

	}
	else if( (population[id2].score() < population[id3].score()))
		{

		 parent.push_back(population[id2]);

		}
	else
		{
		 parent.push_back(population[id3]);
		}
}

// ************* crossover *********** \\

void ackley::crossover()
{

	//create new variables
	double x,y,x2,y2;

	int first, second;
	first = rand()%50;
	second = rand()%50;


	double ax1,ax2,ay1,ay2;
	ax1 = ((rand()%150)/100.00) - 0.25;
	ax2 = ((rand()%150)/100.00) - 0.25;
	ay1 = ((rand()%150)/100.00) - 0.25;
	ay2 = ((rand()%150)/100.00) - 0.25;

	x = parent[first].get_x() + ax1*(parent[second].get_x()- parent[first].get_x());
	x2 = parent[first].get_x() + ax2*(parent[second].get_x()- parent[first].get_x());

	y = parent[first].get_y() + ay1*(parent[second].get_y()- parent[first].get_y());
	y2 = parent[first].get_y() + ay2*(parent[second].get_y()- parent[first].get_y());


	//create new child
	ackley child(x,y);
	ackley child2(x2,y2);

	pool.push_back(child);
	pool.push_back(child2);

}

// ************** muatate ************** \\

void ackley::mutate(ackley &var)
{
	double newX, newY;
	double s;	//randomized mutation variable
	s = (double)((rand()%200)-100)/100;

	double r;	//mutation variable
	r = mr*30;

	double u; //randomized mutation variable
	u = (double)(rand()%100)/100;
	double a;	//random mutation variable
	a= pow(2,(-u*mp));

//	cout << "JUST CHECKING" << s*r*a << endl;
//	cout << "s: " << s << "  r: " << r << "  a: " << a << endl;

	newX = var.get_x() + s*r*a;
	newY = var.get_y() + s*r*a;

//	cout << "OLD X: " << var.get_x() << " OLD Y:  " << var.get_y() << endl;

	var.set_x(newX);
	var.set_y(newY);


//	cout << "NEW X: " << var.get_x() << " NEW Y: " << var.get_y() << endl;

}




// ************ Generate next population ************* \\

void ackley::generate_next()
{

	//add parents to the pool

	for(int i = 0; i<parent.size(); i ++)
	{
		pool.push_back(parent[i]);
	}

	//evaluate fitness and keep top S individuals

	//sorts the pool of offspring and parents from lowest value to highest
	//note we want lower values
	//putting fitness values in a vector

	//evaluate fitness of pool of offspring and parents

	//cout << " @#!#!@#!@ NEXT POP FITNESS !@#!@#" << endl;
	for(unsigned int i=0; i <pool.size(); i++)
	{
		pool[i].solve();
	}

	for(unsigned int i =0; i<pool.size(); i++)
	{
		fitness_value.push_back(pool[i].score());

	}

	//sorting the fitness values

	sort(fitness_value.begin(),fitness_value.end());

	//keep top population

	while(nextPop.size()<population.size())
	{

	for(unsigned int i=0; i <population.size(); i++)
	{
		for(unsigned int j=0; j<pool.size();j++)
		{

			if(pool[j].score() == fitness_value[i])
			{
				nextPop.push_back(pool[j]);
			}
		}

	}

	}
//	for(int i=0; i<fitness_value.size(); i++)
//	cout << "number  " << i << "  " << nextPop[i].score() << endl;

}

void ackley::solve()
{
	double finalAnswer; // holds the value of f(x,y);
	double p1, p2; // splitting the function into parts (easier to write)
	double e = 2.71828;

	p1 = -20*pow(e,(-0.2*sqrt(0.5*(pow(x,2) + pow(y,2)))));
	p2 = -pow(e,(0.5*(cos(2*pi*x) + cos(2*pi*y))));

	finalAnswer = p1 + p2 + e + 20;

	this->fitness_score = finalAnswer;




	//cout << "THIS IS FITNESS " << fitness << endl;
}

double ackley::score()
{
	return this->fitness_score;
}



void ackley::set_x(double x)
{
	this-> x = x;
}

void ackley::set_y(double y)
{
	this->y = y;
}

double ackley::get_x()
{
	return x;
}

double ackley::get_y()
{
	return y;
}


