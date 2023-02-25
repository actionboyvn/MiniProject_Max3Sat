#pragma once

#include "CMax3SatProblem.h"
#include "CGAIndividual.h"
#include <random>
#include <vector>
#include <stdlib.h> 
#include <time.h> 

using namespace std;

class CGAOptimizer
{
public:
	CGAOptimizer(CMax3SatProblem *pcMax3SatProblem);
	~CGAOptimizer();
	void vSetCrossoverProbability(double dCrossoverProbability);
	void vSetMutationProbability(double dMutationProbability);
	void vInitialize();
	void vRunIteration();

	CGAIndividual  *pcGetBestFound();

private:
	CMax3SatProblem *pc_max3SatProblem;
	CGAIndividual  *pc_best_found;
	vector<CGAIndividual*>  v_population;
	int i_population_size;
	double d_crossover_probability;
	double d_mutation_probability;
};
