/*
 * ece0301_fall2019_inclass04_step06.cpp
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
	// If the first line is Wheatstone, this is a wheatstone bridge
	// problem.  Read & report Vs, Is, R1-R5.
	else if (lineFromFile == "Wheatstone")
	{
		// report that we have detected voltage divider
		circuitSolutionsFile << "-----\n";
		circuitSolutionsFile << "Circuit #1 (Wheatstone Bridge)\n";
		circuitSolutionsFile << "---\n";
		
		// variables for source voltage and source current
		double Vs, Is;
		// variables for resistances
		int R1, R2, R3, R4, R5;
		
		// read Vs, Is, R1-R5 from file and report values	
		circuitFile >> Vs;
		circuitSolutionsFile << "Source voltage: Vs = " << Vs << " Volts.\n";			
		circuitFile >> Is;
		circuitSolutionsFile << "Source current: Is = " << Is << " Amperes.\n";			
		circuitFile >> R1;
		circuitSolutionsFile << "Resistor: R1 = " << R1 << " Ohms.\n";			
		circuitFile >> R2;
		circuitSolutionsFile << "Resistor: R2 = " << R2 << " Ohms.\n";
		circuitFile >> R3;
		circuitSolutionsFile << "Resistor: R3 = " << R3 << " Ohms.\n";
		circuitFile >> R4;
		circuitSolutionsFile << "Resistor: R4 = " << R4 << " Ohms.\n";
		circuitFile >> R5;
		circuitSolutionsFile << "Resistor: R5 = " << R5 << " Ohms.\n\n";

		// declare variables for the coefficients a, b, c, d, e
		// in equation (3), and compute their values
		double a = 1 + 1.0*R4/R2, b = Vs - Is*R4;
		double c = 1 + 1.0*R5/R3, d = Vs + Is*R5;
		double e = 1.0*R1/R2, f = 1.0*R1/R3;
		
		// report values for a, b, c, d, e for debugging
		// cout << "a = " << a << ", b = " << b << ", c = " << c << "\n";
		// cout << "d = " << d << ", e = " << e << ", f = " << f << "\n";

		// declare variables for the coefficients w, x, y, z,
		// and compute their values
		double w = (a+e)/b, x = f/b;
		double y = e/d, z = (c+f)/d;

		// report values for w, x, y, z for debugging
		// cout << "w = " << w << ", x = " << x << "\n";
		// cout << "y = " << y << ", z = " << z << "\n";
		
		// declare variables for resistor voltages V2 and V3, and
		// compute their values from w, x, y, z by equations (4-5)
		double V3 = (y-w) / (x*y - w*z), V2 = (1 - x*V3) / w;
		
		// declare variable for V1 and compute from V2, V3, e, f,
		// using equation (3)
		double V1 = e*V2 + f*V3;
		
		// declare variables for V4 and V5, and compute using
		// equations (1-2)
		double V4 = Vs - V1 - V2, V5 = Vs - V1 - V3;
		
		// declare variables for resistor currents, and compute
		// using Ohm's law.
		double I1=V1/R1, I2=V2/R2, I3=V3/R3, I4=V4/R4, I5=V5/R5;
		
		// report all resistor voltages and currents
		circuitSolutionsFile << "Resistor voltage: V1 = " << V1 << " Volts.\n";			
		circuitSolutionsFile << "Resistor current: I1 = " << I1 << " Amperes.\n";			
		circuitSolutionsFile << "Resistor voltage: V2 = " << V2 << " Volts.\n";			
		circuitSolutionsFile << "Resistor current: I2 = " << I2 << " Amperes.\n";			
		circuitSolutionsFile << "Resistor voltage: V3 = " << V3 << " Volts.\n";			
		circuitSolutionsFile << "Resistor current: I3 = " << I3 << " Amperes.\n";			
		circuitSolutionsFile << "Resistor voltage: V4 = " << V4 << " Volts.\n";			
		circuitSolutionsFile << "Resistor current: I4 = " << I4 << " Amperes.\n";			
		circuitSolutionsFile << "Resistor voltage: V5 = " << V5 << " Volts.\n";			
		circuitSolutionsFile << "Resistor current: I5 = " << I5 << " Amperes.\n\n";
	}
	
	return 0;
}

