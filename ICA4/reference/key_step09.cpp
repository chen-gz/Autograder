/*
 * ece0301_fall2019_inclass04_step08.cpp
 */

#include <iostream>
// need fstream library for file stream operations
#include <fstream>
// need cmath library for abs()
#include <cmath>
using namespace std;

int main()
{
	// file stream object for circuit input
	ifstream circuitFile;

	// use the file stream object to open the circuits file.
	circuitFile.open("divider_wheatstone_circuits.txt");
	
	// string object to store lines read from file
	string lineFromFile;

	// file stream object for output of circuit solutions
	ofstream circuitSolutionsFile;

	// use the output file stream object to open the output file
	circuitSolutionsFile.open("divider_wheatstone_solutions.txt");
	
	// Write introductory message to output file
	circuitSolutionsFile << "ECE 0301: Circuit Solver for Voltage Divider\n";
	circuitSolutionsFile << "and Wheatstone bridge example circuits.\n";

	// Variable to count the number of circuits solved.
	int circuitIndex = 0;
	
	while (circuitFile >> lineFromFile)
	{
		// if the first line is not "Divider" or "Wheatsone",
		// print an error message and return from main with -1
		if ( (lineFromFile != "Divider") && (lineFromFile != "Wheatstone") )
		{
			cout << "ERROR! Invalid header.\n";
			return -1;
		}

		// Increment circuit count.
		circuitIndex++;

		// If the first line is Divider, this is a voltage divider
		// problem.  Read and report Vs, R1, R2.
		if (lineFromFile == "Divider")
		{
			// report that we have detected voltage divider
			circuitSolutionsFile << "-----\n";
			circuitSolutionsFile << "Circuit #" << circuitIndex << " (Voltage Divider)\n";
			
			// variables for source voltage and resistances
			double Vs;
			int R1, R2;
			// variable for resistor multiplier n
			int n;
			
			// read Vs, R1, R2, n from file
			circuitFile >> Vs;
			circuitFile >> R1;
			circuitFile >> R2;
			circuitFile >> n;

			// declare variables for I, V1, V2
			double I, V1, V2;
			// Double for loop over 1, 2, ... n for multipler of 
			// resistor values.  In each iteration, we solve the
			// voltage divider problem with R1 = n1*R1 and R2 = n2*R2.
			for (int n1 = 1; n1 <= n; n1++)
				for (int n2 = 1; n2 <= n; n2++)
				{
					// display R1 = n1*R1 and R2 = n2*R2
					circuitSolutionsFile << "---\n";
					circuitSolutionsFile << "Source voltage: Vs = " << Vs << " Volts.\n";
					circuitSolutionsFile << "Resistor: R1 = " << n1*R1 << " Ohms.\n";			
					circuitSolutionsFile << "Resistor: R2 = " << n2*R2 << " Ohms.\n\n";
					// compute I, V1, V2
					I = Vs/(n1*R1 + n2*R2), V1 = I*n1*R1, V2 = I*n2*R2;
					// display I, V1, V2
					circuitSolutionsFile << "Loop current: I = " << I << " Amperes.\n";
					circuitSolutionsFile << "Resistor voltage: V1 = " << V1 << " Volts.\n";			
					circuitSolutionsFile << "Resistor voltage: V2 = " << V2 << " Volts.\n";
				}		
		}
		// If the first line is Wheatstone, this is a wheatstone bridge
		// problem.  Read & report Vs, Is, R1-R5.
		else if (lineFromFile == "Wheatstone")
		{
			// report that we have detected voltage divider
			circuitSolutionsFile << "-----\n";
			circuitSolutionsFile << "Circuit #" << circuitIndex << " (Wheatstone Bridge)\n";
			
			// variables for source voltage and source current
			double Vs, Is;
			// variables for resistances
			int R1, R2, R3, R4, R5;
			// variable for resistor multiplier n
			int n;
			
			// read Vs, Is, R1-R5 from file and report values	
			circuitFile >> Vs;
			circuitFile >> Is;
			circuitFile >> R1;
			circuitFile >> R2;
			circuitFile >> R3;
			circuitFile >> R4;
			circuitFile >> R5;

			// detect cases where Wheatstone bridge circuit algorithm
			// will fail with divide-by-zero
			if ( ( R2 == 0 ) || ( R3 == 0 ) )
			{
				// print error message and exit with -1
				cout << "ERROR! Unstable floating-point division.\n";
				return -1;
			}

			circuitFile >> n;

			// 5-level for loop over 1, 2, ... n for multipler of 
			// resistor values.  In each iteration, we solve the
			// voltage divider problem with R1 = n1*R1 ... R5 = n5*R5.
			for (int n1 = 1; n1 <= n; n1++)
				for (int n2 = 1; n2 <= n; n2++)
					for (int n3 = 1; n3 <= n; n3++)
						for (int n4 = 1; n4 <= n; n4++)
							for (int n5 = 1; n5 <= n; n5++)
							{
								// detect cases where Wheatstone bridge circuit algorithm
								// will fail with unstable division by a small denominator
								if ( ( abs(Vs - Is*R4) < 1e-13 ) || ( abs(Vs + Is*R5) < 1e-13 ) )
								{
									// print error message and exit with -1
									cout << "ERROR! Unstable floating-point division.\n";
									return -1;
								}

								// Write Vs & Is to output file
								circuitSolutionsFile << "---\n";			
								circuitSolutionsFile << "Source voltage: Vs = " << Vs << " Volts.\n";			
								circuitSolutionsFile << "Source current: Is = " << Is << " Amperes.\n";			

								// write R1 = n1*R1 ... R5 = n5*R5 to output file
								circuitSolutionsFile << "Resistor: R1 = " << n1*R1 << " Ohms.\n";			
								circuitSolutionsFile << "Resistor: R2 = " << n2*R2 << " Ohms.\n";
								circuitSolutionsFile << "Resistor: R3 = " << n3*R3 << " Ohms.\n";
								circuitSolutionsFile << "Resistor: R4 = " << n4*R4 << " Ohms.\n";
								circuitSolutionsFile << "Resistor: R5 = " << n5*R5 << " Ohms.\n\n";

								// declare variables for the coefficients a, b, c, d, e
								// in equation (3), and compute their values
								double a = 1 + 1.0*n4*R4/(n2*R2), 
									b = Vs - Is*n4*R4;
								double c = 1 + 1.0*n5*R5/(n3*R3), 
									d = Vs + Is*n5*R5;
								double e = 1.0*n1*R1/(n2*R2), 
									f = 1.0*n1*R1/(n3*R3);
								
								// declare variables for the coefficients w, x, y, z,
								// and compute their values
								double w = (a+e)/b, x = f/b;
								double y = e/d, z = (c+f)/d;
								
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
								double I1=V1/(n1*R1), I2=V2/(n2*R2), I3=V3/(n3*R3), I4=V4/(n4*R4), I5=V5/(n5*R5);
								
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
								circuitSolutionsFile << "Resistor current: I5 = " << I5 << " Amperes.\n";
							}
		}
	}
	
	return 0;
}

