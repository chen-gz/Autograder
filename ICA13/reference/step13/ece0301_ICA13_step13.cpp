/*
 * ece0301_ICA13_step13.cpp
 */

#include "Signal.h"
#include "Lhdeccic.h"
#include "Folhdeccic.h"
#include "Solhdeccic.h"

int main()
{
	// open output file for differential equations
	string otuputFileName = "ECE 0301 - Differential Equation Reports.txt";
	ofstream outFile;
	outFile.open(otuputFileName);

	// define y''(t) + 3 y'(t) + 2 y(t) = 0
	// y(0) = 0, y'(0) = 250
	Solhdeccic diffyQ0(3, 2, 0, 0, 250);
	// write diff. eqn. info to text file
	diffyQ0.report_diffy_q(outFile);
	// write solution info to output file
	diffyQ0.report_diffy_q_solution(outFile);
	
	return 0;
}
