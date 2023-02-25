#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "CClause.h"
using namespace std;

class CMax3SatProblem
{
public:
	CMax3SatProblem();
	
	virtual ~CMax3SatProblem();

	bool  bLoad(string sSourcePath);

	int dEvaluate(bool *pbGenotype);

	int iGetNumberVariables();
	int iGetNumberClauses();
	vector<CClause> *pvGetClauses();
private:
	int i_number_variables;
	int i_number_clauses;
	vector<CClause> *v_clauses;

protected:

};
