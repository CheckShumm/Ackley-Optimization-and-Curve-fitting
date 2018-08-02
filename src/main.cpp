/*
 * main.cpp
 *
 *  Created on: Apr 7, 2016
 *      Author: natha
 */

#include <vector>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include "ackley.h"
#include "curve.h"
#include <algorithm>

#include <iostream>
using namespace std;

int main()
{

//declaring general variables
	bool solution;		// end condition for genetic algorithm
	int counter=0;		// generation counter
	int generations = 100;	// number of generations
	double avg_fitness;		// stores value of average fitness score of a generation
	int h = 1;			// code end condition
	char choice;		// selector between curve and optimization

	cout << "COEN 244  | Final Project" << endl;
	cout << "Genetic Algorithm Optimization and Curve Fitting" << endl;
	cout << "by: Nathan Shummoogum" << endl;
	cout << "ID: 40004336 " << "\n"<<endl;

	cout << "The optimization problem in this code will solve for the Ackley function." << endl;
	cout << "The global minima of the Ackley function is ideally 0." << endl;
	cout << "\n" << "The curve fitting problem in this code can solve for multiple different sets" << endl;
	cout << "to select a set of points proceed to the curve fitting section, and follow instructions" << "\n" << endl;
	cout << "Note the number of generations is capped at 100."
	while(h!=0)	// end condition for code
	{
	// getting choice from the user, ackley or curve?
	cout << "enter 'a' to solve the Ackley fuction" <<endl;
	cout << "enter 'c' to solve the curve fitting function" << endl;
	cin >> choice;


if(choice == 'a')
{

////////////////////////////////////////////////////////////////////////////////
/*
 *
 * 			SOLVING OPTIMIZATION PROBLEM
 *
 *
 */
////////////////////////////////////////////////////////////////////////////////


	ackley a1;	//creatinga general object, used to call ackley functions.

	a1.initialize();	// initialize the population

	while((generations > counter) && (solution == false))	// genetic algorithm end condition
	{
	///////////////////////////////////////////////////////////
	//			Evaluate the fitness scores

	a1.fitness(a1.population);

	///////////////////////////////////////////////////////////
	//			Find suitable parents

		for(int i=0; i<50; i++)
		{
			a1.tournament();
		}

	///////////////////////////////////////////////////////////
	// 			Mutation and Crossover

		for(unsigned int i=0; i<a1.population.size()*5;i++)
		{
			a1.crossover();
		}

		a1.fitness(a1.pool);


		for(unsigned int i=0; i<a1.pool.size(); i++)
		{
			a1.mutate(a1.pool[i]);
		}

	a1.fitness(a1.pool);

	/////////////////////////////////////////////////////////////
	//			Generate new Population

		a1.generate_next();

		//clear the intiial population
		a1.population.erase(a1.population.begin(),a1.population.end());

		// add the next population into the old population vector
		for(int i=0; i<a1.population_size; i++)
		{
			a1.population.push_back(a1.nextPop[i]);
		}
		//erase old next population vector.
		a1.nextPop.erase(a1.nextPop.begin() ,a1.nextPop.end());

		//re-evaluate fitness

		for(unsigned int i=0; i<a1.population.size(); i++)
		{
			a1.population[i].solve();
		}


		//print functions for clear representation of the genetic algorithm

		cout <<"generation:" << counter << endl;
		cout <<"lowest value of f(x,y) = " << a1.population[0].score() << endl;
		cout <<"highest value of f(x,y) = " << a1.population[a1.population.size()-1].score() << endl;

		//find average fitness
		for(unsigned int i=0; i<a1.population.size(); i++)
		{
			avg_fitness += a1.population[i].score();
		}

		avg_fitness = avg_fitness/(a1.population.size());
		cout <<"average value of f(x,y) = " << avg_fitness << "\n" << endl;

		if(a1.population[0].score() < 0.001)
		{
			cout << "Solution found!" << "\n" << endl;
			cout << "Ackley function global minima: " << a1.population[0].score() << endl;
			solution = true;
		}

		//cleaning the rest of vectors
		a1.pool.erase(a1.pool.begin(), a1.pool.end());
		a1.fitness_value.erase(a1.fitness_value.begin(),a1.fitness_value.end());
		a1.parent.erase(a1.parent.begin(), a1.parent.end());
		//update generation counter
		counter++;


	}

}
else if(choice == 'c')
{
////////////////////////////////////////////////////////////////////////////////
/*
 *
 * 			SOLVING CURVE FITTING PROBLEM
 *
 *
 */
////////////////////////////////////////////////////////////////////////////////

curve c1;

double ia,ib,ic,id; //Ideal a,b,c,d values

double yCo[20];

char select;
cout << "select a letter from a-j, each letter corresponds to a set of x-y coordinates" << endl;
cin >> select;

srand(time(NULL));

/*
 * The following switch case statement below is used as a test for the genetic algorithm
 * we can select multiple different sets of x,y coordinates to be tested.
 * some work better then others but this is just proof that the code works as intended.
 */

switch(select)
{
case 'a':
{
	double tempA[20] = {1,4,15,40,85,156,259,400,585,820,1111,1464,1885,2380,2955,3616,4369,5220,6175,7240};
	ia = 1;
	ib = 1;
	ic = 1;
	id = 1;
	for(int i=0; i<20; i++)
		yCo[i] = tempA[i];
	break;
}
case 'b':
{
	double tempB[20] = {4,16,60,160,340,624,1036,1600,2340,3280,4444,5856,7540,9520,11820,14464,17476,20880,24700,28960};
	ia = 4;
	ib = 4;
	ic = 4;
	id = 4;

	for(int i=0; i<20; i++)
	yCo[i] = tempB[i];
	break;
}
case 'c':
{
	double tempC[20] = {4,10,26,58,112,194,310,466,668,922,1234,1610,2056,2578,3182,3874,4660,5546,6538,7642};
	ia = 1;
	ib = 2;
	ic = 3;
	id = 4;

	for(int i=0; i<20; i++)
		yCo[i] = tempC[i];
	break;
}
case 'd':
{
	double tempD[20] = {2,2,2,8,26,62,122,212,338,506,722,992,1322,1718,2186,2732,3362,4082,4898,5816};
	ia = 1;
	ib = -3;
	ic = 2;
	id = 2;

	for(int i=0;i<20;i++)
		yCo[i] = tempD[i];
	break;
}
case 'e':
{
	double tempE[20] = {-1,-4,-15,-40,-85,-156,-259,-400,-585,-820,-1111,-1464,-1885,-2380,-2955,-3616,-4369,-5220,-6175,-7240};
	ia = -1;
	ib = -1;
	ic = -1;
	id = -1;

	for(int i=0; i<20; i++)
		yCo[i] = tempE[i];
}
case 'f':
{
	double tempF[20] = {5,0,-29,-112,-279,-560,-985,-1584,-2387,-3424,-4725,-6320,-8239,-10512,-13169,-16240,-19755,-23744,-28237,-33264};
	ia = -5;
	ib = 3;
	ic = -3;
	id = 5;

	for(int i=0; i<20; i++)
		yCo[i] = tempF[i];
}

case 'g':
{
	double tempG[20] = {1.5,6,22.5,60,127.5,234,388.5,600,877.5,1230,1666.5,2196,2827.5,3570,4432.5,5424,6553.5,7830,9262.5,10860};
	ia = 1.5;
	ib = 1.5;
	ic = 1.5;
	id = 1.5;

	for(int i=0; i<20; i++)
		yCo[i] = tempG[i];
	break;
}

case 'h':
{
	double tempH[20] = {2.5,5.5,27.5,92.5,224.5,447.5,785.5,1262.5,1902.5,2729.5,3767.5,5040.5,6572.5,8387.5,10509.5,12962.5,15770.5,18957.5,22547.5,26564.5};
	ia = 4;
	ib = -2.5;
	ic = 1.5;
	id = 2.5;

	for(int i=0; i<20; i++)
		yCo[i] = tempH[i];
	break;
}

case 'i':
{
	double tempI[20] = {3,9,19,33,51,73,99,129,163,201,243,289,339,393,451,513,579,649,723,801};
	ia = 0;
	ib = 2;
	ic = 4;
	id = 3;

	for(int i=0; i<20; i++)
		yCo[i] = tempI[i];
	break;
}
case 'j':
{
	double tempJ[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	ia = 0;
	ib = 0;
	ic = 0;
	id = 0;

	for (int i=0; i<20; i++)
		yCo[i] = tempJ[i];
	break;
}
default:
{
	cout <<" please only enter a letter from a-j" << " \n" << "Thank you!" << endl;
}
}

//initialize the population
	c1.initialize();


//begin the genetic algorithm
	while((generations>counter) && solution == false)
	{

		///////////////////////////////////////////////////////////
		//			Evaluate the fitness scores

		for(unsigned int i =0; i <c1.population.size(); i++)
		{
			/*fitness score
			 * the function "solve" will solve the function for all individuals
			 * of the population and assign a fitness score to them.
			 */
			c1.population[i].solve(yCo);
		}

		///////////////////////////////////////////////////////////
		//			Find suitable parents

			for(int i=0; i<50; i++)
			{
				c1.tournament();
			}

		///////////////////////////////////////////////////////////
		// 			Mutation and Crossover

			for(unsigned int i=0; i<c1.population.size()*5;i++)
			{
				c1.crossover();
			}

			for(unsigned int i =0; i <c1.pool.size(); i++)
				{
					/*fitness score
					 * the function "solve" will solve the function for all individuals
					 * of the population and assign a fitness score to them.
					 */
					c1.pool[i].solve(yCo);
				}

			for(unsigned int i=0; i<c1.pool.size(); i++)
			{
				c1.mutate(c1.pool[i]);
			}

			for(unsigned int i =0; i <c1.pool.size(); i++)
						{
							/*fitness score
							 * the function "solve" will solve the function for all individuals
							 * of the population and assign a fitness score to them.
							 */
							c1.pool[i].solve(yCo);
						}


		c1.join();
		c1.generate_next();
		//evaluate fitness of pool of offspring and parents

		//cout << " @#!#!@#!@ NEXT POP FITNESS !@#!@#" << endl;
		for(unsigned int i=0; i <c1.pool.size(); i++)
		{
			c1.pool[i].solve(yCo);
		}


		//clean old populatin.
			c1.population.erase(c1.population.begin(),c1.population.end());

		//add the next population to the old population  vector.

			for(int i=0; i<c1.population_size; i++)
			{
				c1.population.push_back(c1.nextPop[i]);
			}

		//erase the old newpopulation vector.

			c1.nextPop.erase(c1.nextPop.begin() ,c1.nextPop.end());
			//re-evaluate fitness

			for(unsigned int i=0; i<c1.population.size(); i++)
			{
				c1.population[i].solve(yCo);
			}


		//print functions for user clarity.

			cout <<"generation:" << counter << endl;
			cout <<"lowest value of MSE = " << c1.population[0].score() << endl;
			cout <<"highest value of MSE = " << c1.population[c1.population.size()-1].score() << endl;

			//find average fitness
					for(unsigned int i=0; i<c1.population.size(); i++)
					{
						avg_fitness += c1.population[i].score();
					}

					avg_fitness = avg_fitness/(c1.population.size());
					cout <<"average value of MSE = " << avg_fitness << "\n" << endl;

					cout << "  a:" << c1.population[0].getA();
					cout << "  b:" << c1.population[0].getB();
					cout << "  c:" << c1.population[0].getC();
					cout << "  d:" << c1.population[0].getD() << endl;

					//cleaning other functions
					c1.clean();
					cout << "\n";

			// End Condition
			if(c1.population[0].score() < 0.05)
			{
				solution = true;
				cout << "\n" << "\n" << "Solution Found!!" << endl;
				cout <<"MSE: " << c1.population[0].score() << "\n" << endl;
				cout <<"Best fitting polynomial is:" << endl;
				cout <<"y = " << c1.population[0].getA() << "(x^3) + " << c1.population[0].getB() << "(x^2) + ";
				cout << c1.population[0].getC() << "x + " << c1.population[0].getD() << endl;

				cout << "\n";
				cout <<"ideal value: " << ia <<"  |  ";
				cout <<"a = " << c1.population[0].getA() << endl;
				cout <<"ideal value: " << ib << "  |  ";
				cout <<"b = " << c1.population[0].getB()<< endl;
				cout <<"ideal value: " << ic << "  |  ";
				cout <<"c = " << c1.population[0].getC() << endl;
				cout <<"ideal value: " << id << "  |  ";
				cout <<"d = " << c1.population[0].getD() << endl;
				cout << "\n";

			}

			//update generation counter
			counter++;

			if(counter == generations)
			{
				cout << "\n" << "\n" << "Did not reach end condition!" << endl;

				cout <<"MSE: " << c1.population[0].score() << "\n" << endl;
				cout <<"Best fitting polynomial is:" << endl;
				cout <<"y = " << c1.population[0].getA() << "(x^3) + " << c1.population[0].getB() << "(x^2) + ";
				cout << c1.population[0].getC() << "x + " << c1.population[0].getD() << endl;

				cout << "\n";
				cout <<"ideal value: " << ia <<"  |  ";
				cout <<"a = " << c1.population[0].getA() << endl;
				cout <<"ideal value: " << ib << "  |  ";
				cout <<"b = " << c1.population[0].getB()<< endl;
				cout <<"ideal value: " << ic << "  |  ";
				cout <<"c = " << c1.population[0].getC() << endl;
				cout <<"ideal value: " << id << "  |  ";
				cout <<"d = " << c1.population[0].getD() << endl;

				cout << "\n" <<"The genetic algorithm was unlucky..." << "\n"
				<< "retry this function for a more accurate solution" << endl;
				cout << "\n";

						}


		}//c1 generation

		}

	cout << "if you would like to select another set of points, enter 1." << endl;
	cout << "if you have finished using the program, enter 0." << endl;
	cin >>h;

	//reset conditions
	counter = 0;
	solution = false;
}
}

// end of main
