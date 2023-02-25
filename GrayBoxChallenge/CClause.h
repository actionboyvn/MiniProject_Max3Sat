#pragma once
class CClause {
public:
	CClause(int iFirstVariable, int iSecondVariable, int iThirdVariable);
	int iGetFirstVariable();
	int iGetSecondVariable();
	int iGetThirdVariable();
private:
	int i_first_variable;
	int i_second_variable;
	int i_third_variable;
};
