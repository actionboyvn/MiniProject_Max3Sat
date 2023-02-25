#include "CClause.h"

CClause::CClause(int iFirstVariable, int iSecondVariable, int iThirdVariable)
{
	i_first_variable = iFirstVariable;
	i_second_variable = iSecondVariable;
	i_third_variable = iThirdVariable;
}

int CClause::iGetFirstVariable()
{
	return i_first_variable;
}

int CClause::iGetSecondVariable()
{
	return i_second_variable;
}

int CClause::iGetThirdVariable()
{
	return i_third_variable;
}