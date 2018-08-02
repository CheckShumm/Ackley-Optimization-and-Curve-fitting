/*
 * curve.cpp
 *
 *  Created on: Apr 7, 2016
 *      Author: natha
 */

#include <vector>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include "curve.h"
#include <algorithm>

#include <iostream>
using namespace std;

curve::curve()
{
	srand(time(NULL));
	a=0;
	b=0;
	c=0;
	d=0;
	fitness_score = 0;
	mp = 12;
	mr = 0.005;
}


curve::curve(double a, double b, double c, double d)
{
this-> a = a;
this-> b = b;
this-> c = c;
this-> d = d;

fitness_score = 0;
mp = 12;
mr = 0.005;

}

void curve::solve(double yCo[])
{
	double finalAnswer;
	double holder;

	for(int n=0; n<20;n++)
	{

		//simple 3rd degree polynomial
		// n can replace x, as it increments by 1.
		y[n] = a*(pow(n,3)) + b*(pow(n,2)) + c*n + d;
		holder = pow((yCo[n] - y[n]),2);
		finalAnswer += holder;
	}

	finalAnswer = finalAnswer/20;
	this->fitness_score = finalAnswer;
}

double curve::score()
{
	return fitness_score;
}

void curve::initialize()
{

		for(int i=0; i<population_size; i++)
		{
			double newA,newB,newC,newD;

			newA = (double)((rand()%10)-5);
			newB = (double)((rand()%10)-5);
			newC = (double)((rand()%10)-5);
			newD = (double)((rand()%10)-5);

			curve temp(newA,newB,newC,newD);
			population.push_back(temp);

		}

}

void curve::fitness(vector<curve>& group)
{
	for(unsigned int i =0; i <group.size(); i++)
	{
		/*fitness score
		 * the function "solve" will solve the function for all individuals
		 * of the population and assign a fitness score to them.
		 */
		//group[i].solve();
	}
}

void curve::tournament()
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

void curve::crossover()
{

	//create new variables
	double a,b,c,d;
	double a2,b2,c2,d2;

	int first, second;
	first = rand()%50;
	second = rand()%50;


	double aa,ab,ac,ad;
	double aa2,ab2,ac2,ad2;
	aa = ((rand()%150)/100.00) - 0.25;
	ab = ((rand()%150)/100.00) - 0.25;
	ac = ((rand()%150)/100.00) - 0.25;
	ad = ((rand()%150)/100.00) - 0.25;

	aa2 = ((rand()%150)/100.00) - 0.25;
	ab2 = ((rand()%150)/100.00) - 0.25;
	ac2 = ((rand()%150)/100.00) - 0.25;
	ad2 = ((rand()%150)/100.00) - 0.25;

	a = parent[first].getA() + aa*(parent[second].getA()- parent[first].getA());
	a2 = parent[first].getA() + aa2*(parent[second].getA()- parent[first].getA());

	b = parent[first].getB() + ab*(parent[second].getB()- parent[first].getB());
	b2 = parent[first].getB() + ab2*(parent[second].getB()- parent[first].getB());

	c = parent[first].getC() + ac*(parent[second].getC()- parent[first].getC());
	c2 = parent[first].getC() + ac2*(parent[second].getC()- parent[first].getC());

	d = parent[first].getD() + ad*(parent[second].getD()- parent[first].getD());
	d2 = parent[first].getD() + ad2*(parent[second].getD()- parent[first].getD());

	//create new child
	curve child(a,b,c,d);
	curve child2(a2,b2,c2,d2);

	pool.push_back(child);
	pool.push_back(child2);

}

void curve::mutate(curve& var)
{
	double newA, newB, newC, newD;
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

	newA = var.getA() + s*r*a;
	newB = var.getB() + s*r*a;
	newC = var.getC() + s*r*a;
	newD = var.getD() + s*r*a;
	//	cout << "OLD X: " << var.get_x() << " OLD Y:  " << var.get_y() << endl;

	var.setA(newA);
	var.setB(newB);
	var.setC(newC);
	var.setD(newD);


	//	cout << "NEW X: " << var.get_x() << " NEW Y: " << var.get_y() << endl;
}

void curve::join()
{
	//add parents to the pool

	for(int i = 0; i<parent.size(); i ++)
	{
		pool.push_back(parent[i]);
	}

}

void curve::generate_next()
{

	//evaluate fitness and keep top S individuals

	//sorts the pool of offspring and parents from lowest value to highest
	//note we want lower values
	//putting fitness values in a vector

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

void curve::clean()
{
	parent.erase(parent.begin(),parent.end());
	pool.erase(pool.begin(), pool.end());
    nextPop.erase(nextPop.begin(), nextPop.end());
	fitness_value.erase(fitness_value.begin(), fitness_value.end());
}
