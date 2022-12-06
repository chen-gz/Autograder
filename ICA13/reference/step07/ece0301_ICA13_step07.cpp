/*
 * ece0301_ICA13_step07.cpp
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

	// define a 1st-order diff. eqn. w/ default parameters
	Folhdeccic diffyQ0;
	// write diff. eqn. info to output file
	diffyQ0.report_diffy_q(outFile);
	// write solution info to output file
	diffyQ0.report_diffy_q_solution(outFile);

	// define a 1st-order diff. eqn. w/ specified parameters
	Folhdeccic diffyQ1(10, -2.5, 1);
	diffyQ1.setLabel("x");
	// write diff. eqn. info to output file
	diffyQ1.report_diffy_q(outFile);
	// write solution info to output file
	diffyQ1.report_diffy_q_solution(outFile);

	outFile.close();
	
	return 0;
}
