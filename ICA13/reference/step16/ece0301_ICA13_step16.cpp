/*
 * ece0301_ICA13_step16.cpp
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

	// define s''(t) + 4 s'(t) + 4 s(t) = 0
	// s(0) = -50, s'(0) = 500
	Solhdeccic diffyQ0(4, 4, 0, -50, 500);
	diffyQ0.setLabel("s");
	// write diff. eqn. info to text file
	diffyQ0.report_diffy_q(outFile);
	// write solution info to output file
	diffyQ0.report_diffy_q_solution(outFile);
	
	return 0;
}
