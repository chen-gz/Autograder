/*
 * ece0301_ICA13_step08.cpp
 */

#include "Signal.h"
#include "Lhdeccic.h"
#include "Folhdeccic.h"

int main()
{
	// open output file for differential equations
	string otuputFileName = "ECE 0301 - Differential Equation Reports.txt";
	ofstream outFile;
	outFile.open(otuputFileName);

	// define a 1st-order diff. eqn. w/ specified parameters
	Folhdeccic diffyQ0(2, -1.25, 120);
	diffyQ0.setLabel("x");
	// write diff. eqn. info to output file
	diffyQ0.report_diffy_q(outFile);
	// write solution info to output file
	diffyQ0.report_diffy_q_solution(outFile);

	outFile.close();
	
	return 0;
}
