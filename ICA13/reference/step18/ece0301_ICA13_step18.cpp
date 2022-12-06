/*
 * ece0301_ICA13_step18.cpp
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

	// define g''(t) + 2 g'(t) + 101 g(t) = 0
	// g(-5) = 100, g'(-5) = -100
	Solhdeccic diffyQ0(2, 101, -5, 100, -100);
	diffyQ0.setLabel("g");
	// write diff. eqn. info to text file
	diffyQ0.report_diffy_q(outFile);
	// write solution info to output file
	diffyQ0.report_diffy_q_solution(outFile);
	
	return 0;
}
