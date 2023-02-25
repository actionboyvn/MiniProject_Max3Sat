#include "CClause.h"
#include "CMax3SatProblem.h"
#include "CGAOptimizer.h"
#include "Timer.h"

#include <exception>
#include <iostream>
#include <time.h> 

using namespace TimeCounters;

using namespace std;

#define dMAX_TIME 15 * 60


void vRunExperiment(CMax3SatProblem *pcMax3SatProblem)
{
	try
	{
		CTimeCounter c_time_counter;

		double d_time_passed;

		CGAOptimizer c_optimizer(pcMax3SatProblem);

		c_time_counter.vSetStartNow();


		c_optimizer.vInitialize();
		c_optimizer.vSetCrossoverProbability(0.5);
		c_optimizer.vSetMutationProbability(0.5);

		c_time_counter.bGetTimePassed(&d_time_passed);
		
		while (d_time_passed <= dMAX_TIME)
		{
			
			c_optimizer.vRunIteration();
			
			c_optimizer.pcGetBestFound();

			cout << c_optimizer.pcGetBestFound()->dGetFitness() << endl; 
			
			c_time_counter.bGetTimePassed(&d_time_passed);
		}

	}
	catch (exception &c_exception)
	{
		cout << c_exception.what() << endl;
	}
}


void main(int iArgCount, char **ppcArgValues)
{
	CMax3SatProblem  c_max3satproblem;		
	if (c_max3satproblem.bLoad("m3s_350_0.txt") == true)
	{				
		cout << c_max3satproblem.iGetNumberClauses() << endl;
		vRunExperiment(&c_max3satproblem);
	}

}