/*
 * ece0301_fall2019_inclass04_step04.cpp
 */

#include <iostream>
// need fstream library for file stream operations
#include <fstream>
using namespace std;

int main()
{
	// file stream object for circuit input
	ifstream circuitFile;

	// use the file stream object to open the circuits file.
	circuitFile.open("divider_wheatstone_circuits.txt");
	
	// string object to store lines read from file
	string lineFromFile;

	// read the fist line from the file
	circuitFile >> lineFromFile;
	
	// if the first line is not "Divider" or "Wheatsone",
	// print an error message and return from main with -1
	if ( (lineFromFile != "Divider") && (lineFromFile != "Wheatstone") )
	{
		cout << "ERROR! Invalid header.\n";
		return -1;
	}

	// file stream object for output of circuit solutions
	ofstream circuitSolutionsFile;

	// use the output file stream object to open the output file
	circuitSolutionsFile.open("divider_wheatstone_solutions.txt");
	
	// Write introductory message to output file
	circuitSolutionsFile << "ECE 0301: Circuit Solver for Voltage Divider\n";
	circuitSolutionsFile << "and Wheatstone bridge example circuits.\n";

	// If the first line is Divider, this is a voltage divider
	// problem.  Read and report Vs, R1, R2.
	if (lineFromFile == "Divider")
	{
		// report that we have detected voltage divider
		circuitSolutionsFile << "-----\n";
		circuitSolutionsFile << "Circuit #1 (Voltage Divider)\n";
		circuitSolutionsFile << "---\n";
		
		// variables for source voltage and resistances
		double Vs;
		int R1, R2;
		
		// read Vs, R1, R2 from file and report values
		circuitFile >> Vs;
		circuitSolutionsFile << "Source voltage: Vs = " << Vs << " Volts.\n";			
		circuitFile >> R1;
		circuitSolutionsFile << "Resistor: R1 = " << R1 << " Ohms.\n";			
		circuitFile >> R2;
		circuitSolutionsFile << "Resistor: R2 = " << R2 << " Ohms.\n\n";

		// declare variables for I, V1, V2 and compute them
		double I = Vs/(R1 + R2);
		double V1 = I*R1, V2 = I*R2;
		
		// Report I, V1, V2 to user
		circuitSolutionsFile << "Loop current: I = " << I << " Amperes.\n";
		circuitSolutionsFile << "Resistor voltage: V1 = " << V1 << " Volts.\n";			
		circuitSolutionsFile << "Resistor voltage: V2 = " << V2 << " Volts.\n\n";
	}

	return 0;
}

