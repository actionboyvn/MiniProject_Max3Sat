#pragma once
#include <iostream>
#include <random>
#include <vector>
#include <stdlib.h> 
#include <time.h> 
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
};//class  CGAIndividual


inline CGAIndividual::CGAIndividual()
{

}

inline CGAIndividual::CGAIndividual(int iNumberVariables)
{
	i_number_variables = iNumberVariables;
	pb_genotype = new bool[i_number_variables] {false};
	d_fitness = 0;
}

inline CGAIndividual::~CGAIndividual()
{
	delete[] pb_genotype;
}

inline int CGAIndividual::iGetNumberVariables()
{
	return i_number_variables;
}

inline int CGAIndividual::iGetNumberSatisfiedClauses()
{
	return i_number_satisfied_clauses;
}

inline void CGAIndividual::vSetNumberSatisfiedClauses(int iRes)
{
	i_number_satisfied_clauses = iRes;
}

inline bool * CGAIndividual::pbGetGenotype()
{
	return pb_genotype;
}

inline void CGAIndividual::vRandomiseGenotype()
{
	srand(time(NULL));
	for (int i = 0; i < i_number_variables; i++) pb_genotype[i] = rand() % 2;
}

inline void CGAIndividual::vSetGeneAt(int i_offset, bool bGeneToSet)
{
	pb_genotype[i_offset] = bGeneToSet;
}

inline bool CGAIndividual::bGetGeneAt(int iOffset)
{
	return pb_genotype[iOffset];
}

inline void CGAIndividual::vInherite(CGAIndividual * pcParent)
{
	if (pcParent->iGetNumberVariables() != i_number_variables) return;
	for (int i = 0; i < i_number_variables; i++) pb_genotype[i] = pcParent->bGetGeneAt(i);
}

inline pair<CGAIndividual*, CGAIndividual*> CGAIndividual::pCrossover(CGAIndividual *pcParent1, CGAIndividual *pcParent2, double dCrossoverProbability)
{
	CGAIndividual *pc_child1 = new CGAIndividual(pcParent1->iGetNumberVariables());
	CGAIndividual *pc_child2 = new CGAIndividual(pcParent2->iGetNumberVariables());
	srand(time(NULL));
	double d_rand_probability = rand() % 101 * 1.0 / 100;
	if (d_rand_probability <= dCrossoverProbability) {
		// Uniform crossover
		for (int i = 0; i < pcParent1->iGetNumberVariables(); i++)
			if (rand() % 2 == 0) {
				pc_child1->vSetGeneAt(i, pcParent1->bGetGeneAt(i));
				pc_child2->vSetGeneAt(i, pcParent2->bGetGeneAt(i));
			}
			else {
				pc_child1->vSetGeneAt(i, pcParent2->bGetGeneAt(i));
				pc_child2->vSetGeneAt(i, pcParent1->bGetGeneAt(i));
			}
	}
	else {
		pc_child1->vInherite(pcParent1);
		pc_child2->vInherite(pcParent2);
	}
	pair<CGAIndividual*, CGAIndividual*> p_children = make_pair(pc_child1, pc_child2);
	pc_child1 = nullptr;
	pc_child2 = nullptr;
	delete pc_child1;
	delete pc_child2;

	return p_children;
}

inline void CGAIndividual::vMutation(double dMutationProbability)
{
	srand(time(NULL));
	double d_rand_probability = rand() % 101 * 1.0 / 100;
	if (d_rand_probability > dMutationProbability) return;
	for (int i = 0; i < i_number_variables; i++)
		if (rand() % 2 == 0) pb_genotype[i] = 1 - pb_genotype[i];
}

inline void CGAIndividual::vOptimiseOneClause(CClause cClause)
{
	bool b_is_satisfied = false;
	int i_first_variable, i_second_variable, i_third_variable;
	i_first_variable = cClause.iGetFirstVariable();
	i_second_variable = cClause.iGetSecondVariable();
	i_third_variable = cClause.iGetThirdVariable();
	if (i_first_variable >= 0 && pb_genotype[i_first_variable] == true || i_first_variable < 0 && pb_genotype[-i_first_variable] == false ||
		i_second_variable >= 0 && pb_genotype[i_second_variable] == true || i_second_variable < 0 && pb_genotype[-i_second_variable] == false ||
		i_third_variable >= 0 && pb_genotype[i_third_variable] == true || i_third_variable < 0 && pb_genotype[-i_third_variable] == false)
		b_is_satisfied = true;
	if (!b_is_satisfied) {
		pb_genotype[abs(i_first_variable)] = 1 - pb_genotype[abs(i_first_variable)];
		pb_genotype[abs(i_second_variable)] = 1 - pb_genotype[abs(i_second_variable)];
		pb_genotype[abs(i_third_variable)] = 1 - pb_genotype[abs(i_third_variable)];
	}
}

inline void CGAIndividual::vSetFitness(double dFitness)
{
	d_fitness = dFitness;
}

inline double CGAIndividual::dGetFitness()
{
	return d_fitness;
}