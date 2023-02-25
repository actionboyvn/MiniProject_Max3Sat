#include "CGAOptimizer.h"

#include <cfloat>
#include <iostream>
#include <windows.h>

using namespace std;


CGAOptimizer::CGAOptimizer(CMax3SatProblem* pcMax3SatProblem)
{
	pc_max3SatProblem = pcMax3SatProblem;
	i_population_size = 0;
	pc_best_found = new CGAIndividual(pcMax3SatProblem->iGetNumberVariables());
}

CGAOptimizer::~CGAOptimizer()
{
	for (int i = 0; i < v_population.size(); i++) delete v_population.at(i);
	v_population.clear();
	delete pc_best_found;
}

void CGAOptimizer::vSetCrossoverProbability(double dCrossoverProbability)
{
	d_crossover_probability = dCrossoverProbability;
}

void CGAOptimizer::vSetMutationProbability(double dMutationProbability)
{
	d_mutation_probability = dMutationProbability;
}

void CGAOptimizer::vInitialize()
{

	i_population_size = 1e8 / pc_max3SatProblem->iGetNumberClauses();
	//i_population_size = 100;
	for (int i = 0; i < i_population_size; i++) {
		CGAIndividual* c_new_individual = new CGAIndividual(pc_max3SatProblem->iGetNumberVariables());
		c_new_individual->vRandomiseGenotype();
		v_population.push_back(c_new_individual);
		c_new_individual = nullptr;
		delete c_new_individual;
	}

}

void CGAOptimizer::vRunIteration()
{
	for (int i = 0; i < i_population_size; i++) {
		CGAIndividual* c_individual = v_population.at(i);
		int i_satisfied_clauses = pc_max3SatProblem->dEvaluate(c_individual->pbGetGenotype());
		c_individual->vSetNumberSatisfiedClauses(i_satisfied_clauses);
		c_individual->vSetFitness(double(i_satisfied_clauses) / double(pc_max3SatProblem->iGetNumberClauses()));
		if (pc_best_found->dGetFitness() < c_individual->dGetFitness()) {
			pc_best_found->vInherite(c_individual);
			pc_best_found->vSetFitness(c_individual->dGetFitness());
			pc_best_found->vSetNumberSatisfiedClauses(c_individual->iGetNumberSatisfiedClauses());
		}
		c_individual = nullptr;
		delete c_individual;
	}

	srand(time(NULL));
	vector<CGAIndividual*> v_population_new;
	CGAIndividual* pc_individual1, * pc_individual2;
	while (v_population_new.size() < v_population.size()) {

		//Parent1 selection
		pc_individual1 = v_population.at(rand() % v_population.size());
		pc_individual2 = v_population.at(rand() % v_population.size());
		CGAIndividual* pc_parent1;
		if (pc_individual1->dGetFitness() > pc_individual2->dGetFitness()) pc_parent1 = pc_individual1; else
			pc_parent1 = pc_individual2;

		//Parent2 selection
		pc_individual1 = v_population.at(rand() % v_population.size());
		pc_individual2 = v_population.at(rand() % v_population.size());
		CGAIndividual* pc_parent2;
		if (pc_individual1->dGetFitness() > pc_individual2->dGetFitness()) pc_parent2 = pc_individual1; else
			pc_parent2 = pc_individual2;

		//Child1, Child2 selection
		//Child1, Child2 crossover
		CGAIndividual* pc_child1, * pc_child2;
		pair<CGAIndividual*, CGAIndividual*> p_children = pc_parent1->pCrossover(pc_parent1, pc_parent2, d_crossover_probability);
		pc_child1 = p_children.first;
		pc_child2 = p_children.second;

		//Child1, Child2 mutation
		pc_child1->vMutation(d_mutation_probability);
		pc_child2->vMutation(d_mutation_probability);

		//Child1, Child2 one-clause optimalization
		int i_rand = rand() % pc_max3SatProblem->iGetNumberClauses();
		pc_child1->vOptimiseOneClause(pc_max3SatProblem->pvGetClauses()->at(i_rand));
		i_rand = rand() % pc_max3SatProblem->iGetNumberClauses();
		pc_child2->vOptimiseOneClause(pc_max3SatProblem->pvGetClauses()->at(i_rand));

		v_population_new.push_back(pc_child1);
		v_population_new.push_back(pc_child2);

		p_children.first = nullptr;
		p_children.second = nullptr;
		pc_parent1 = nullptr;
		pc_parent2 = nullptr;
		pc_child1 = nullptr;
		pc_child2 = nullptr;

		delete p_children.first;
		delete p_children.second;
		delete pc_parent1;
		delete pc_parent2;
		delete pc_child1;
		delete pc_child2;
	}

	for (int i = 0; i < v_population.size(); i++) delete v_population.at(i);
	v_population.clear();
	v_population = v_population_new;

	pc_individual1 = nullptr;
	pc_individual2 = nullptr;
	delete pc_individual1;
	delete pc_individual2;
}

CGAIndividual* CGAOptimizer::pcGetBestFound()
{
	return pc_best_found;
}

