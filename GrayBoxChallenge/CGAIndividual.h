#pragma once
#include <iostream>
#include <random>
#include <vector>
#include <stdlib.h> 
#include <time.h> 
#include "CClause.h"
#include "CMax3SatProblem.h"

using namespace std;

class  CGAIndividual
{
public:
	CGAIndividual();
	CGAIndividual(int iNumberVariables);
	~CGAIndividual();

	int iGetNumberVariables();
	int iGetNumberSatisfiedClauses();
	void vSetNumberSatisfiedClauses(int iRes);
	void vRandomiseGenotype();
	bool *pbGetGenotype();
	void vSetGeneAt(int iOffset, bool bGeneToSet);
	bool bGetGeneAt(int iOffset);
	void vInherite(CGAIndividual *pcParent);

	pair<CGAIndividual*, CGAIndividual*> pCrossover(CGAIndividual *pcParent1, CGAIndividual *pcParent2, double dCorssoverProbability);
	void vMutation(double dMutationProbability);
	void vOptimiseOneClause(CClause cClause);

	void vSetFitness(double dFitness);
	double dGetFitness();

private:
	int i_number_variables;
	int i_number_satisfied_clauses;
	double d_fitness;
	bool *pb_genotype;
};

