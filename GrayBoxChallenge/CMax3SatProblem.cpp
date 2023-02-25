#include "CMax3SatProblem.h"
#include <algorithm>
#include <iostream>
#include <random>
#include <stdexcept>

CMax3SatProblem::CMax3SatProblem()
{
	v_clauses = new vector<CClause>;
	i_number_variables = 0;
	i_number_clauses = 0;
}

CMax3SatProblem::~CMax3SatProblem()
{
	v_clauses->clear();
	delete v_clauses;
}

bool CMax3SatProblem::bLoad(std::string sSourcePath)
{
	char c_bracket;
	int i_first_variable, i_second_variable, i_third_variable;
	int i_max_variable = 0;
	ifstream fin(sSourcePath, ios::in);
	if (!fin.is_open()) return false;

	while (!fin.eof()) {
		c_bracket = ' ';
		fin >> c_bracket;
		fin >> i_first_variable;
		fin >> i_second_variable;
		fin >> i_third_variable;
		fin >> c_bracket;
		if (c_bracket != ' ') {
			i_number_clauses++;
			v_clauses->push_back(CClause(i_first_variable, i_second_variable, i_third_variable));
			if (i_max_variable < abs(i_first_variable)) i_max_variable = abs(i_first_variable);
			if (i_max_variable < abs(i_second_variable)) i_max_variable = abs(i_second_variable);
			if (i_max_variable < abs(i_third_variable)) i_max_variable = abs(i_third_variable);
		}
	}
	fin.close();
	i_number_variables = i_max_variable + 1;
	return true;
}

int CMax3SatProblem::dEvaluate(bool* pbGenotype)
{
	int i_satisfied_clauses = 0;
	int i_first_variable, i_second_variable, i_third_variable;
	for (int j = 0; j < v_clauses->size(); j++) {
		i_first_variable = v_clauses->at(j).iGetFirstVariable();
		i_second_variable = v_clauses->at(j).iGetSecondVariable();
		i_third_variable = v_clauses->at(j).iGetThirdVariable();
		if (i_first_variable >= 0 && pbGenotype[i_first_variable] == true || i_first_variable < 0 && pbGenotype[-i_first_variable] == false ||
			i_second_variable >= 0 && pbGenotype[i_second_variable] == true || i_second_variable < 0 && pbGenotype[-i_second_variable] == false ||
			i_third_variable >= 0 && pbGenotype[i_third_variable] == true || i_third_variable < 0 && pbGenotype[-i_third_variable] == false)
			i_satisfied_clauses++;
	}
	return i_satisfied_clauses;
}

int CMax3SatProblem::iGetNumberVariables()
{
	return i_number_variables;
}

int CMax3SatProblem::iGetNumberClauses()
{
	return i_number_clauses;
}

vector<CClause>* CMax3SatProblem::pvGetClauses()
{
	return v_clauses;
}




