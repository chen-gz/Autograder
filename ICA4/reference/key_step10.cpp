/*
 * ece1170_spring2019_inclass04_step10.cpp
 */

#include <iostream>
// need fstream library for file stream operations
#include <fstream>
using namespace std;

int main()
{
	// file stream object for output of circuit solutions
	ofstream circuitSolutionsFile;

	// use the output file stream object to open the output file
	circuitSolutionsFile.open("divider_wheatstone_solutions.txt");
	
	// Display introductory message
	circuitSolutionsFile << "ECE 1170 – Circuit Solver for Voltage Divider\n";
	circuitSolutionsFile << "and Wheatstone bridge example circuits.\n\n";

	// file stream object for circuit input
	ifstream circuitFile;

	// use the file stream object to open the circuits file.
	circuitFile.open("divider_wheatstone_circuits.txt");
	
	// string object to store lines read from file
	string lineFromFile;

	while (circuitFile >> lineFromFile)
	{
		// if the first line is Divider, print that
		if (lineFromFile == "Divider")
			circuitSolutionsFile << lineFromFile << endl;
		// or, if the first line is Wheatstone, print that
		else if (lineFromFile == "Wheatstone")
			circuitSolutionsFile << lineFromFile << endl;
		// otherwise, print an error message and return from main with -1
		else
		{
			cout << "ERROR! Unrecognized circuit problem.\n";
			return -1;
		}

		// If the first line is Divider, this is a voltage divider
		// problem.  Read & report Vs, R1, R2, then solve the circuit.
		if (lineFromFile == "Divider")
		{
			// report that we have detected voltage divider
			circuitSolutionsFile << "This is a voltage divider problem.\n";
			
			// variables for source voltage and resistances
			double Vs;
			int R1, R2;
			// variable for resistor multiplier n
			int n;
			
			// read Vs, R1, R2, n from file and report values
			circuitFile >> Vs;
			circuitSolutionsFile << "Source voltage: Vs = " << Vs << " Volts.\n";			
			circuitFile >> R1;
			circuitSolutionsFile << "Resistor: R1 = " << R1 << " Ohms.\n";			
			circuitFile >> R2;
			circuitSolutionsFile << "Resistor: R2 = " << R2 << " Ohms.\n";
			circuitFile >> n;
			circuitSolutionsFile << "Number of resistor values: n = " << n << ".\n\n";

			// declare variables for I, V1, V2
			double I, V1, V2;
			// Double for loop over 1, 2, ... n for multipler of 
			// resistor values.  In each iteration, we solve the
			// voltage divider problem with R1 = n1*R1 and R2 = n2*R2.
			for (int n1 = 1; n1 <= n; n1++)
				for (int n2 = 1; n2 <= n; n2++)
				{
					// display R1 = n1*R1 and R2 = n2*R2
					circuitSolutionsFile << "Resistor: R1 = " << n1*R1 << " Ohms.\n";			
					circuitSolutionsFile << "Resistor: R2 = " << n2*R2 << " Ohms.\n";
					// compute I, V1, V2
					I = Vs/(n1*R1 + n2*R2), V1 = I*n1*R1, V2 = I*n2*R2;
					// display I, V1, V2
					circuitSolutionsFile << "Loop current: I = " << I << " Amperes.\n";
					circuitSolutionsFile << "Resistor voltage: V1 = " << V1 << " Volts.\n";			
					circuitSolutionsFile << "Resistor voltage: V2 = " << V2 << " Volts.\n\n";
				}		
		}
		// If the first line is Wheatstone, this is a wheatstone bridge
		// problem.  Read & report Vs, Is, R1-R5, then solve the problem.
		else if (lineFromFile == "Wheatstone")
		{
			// report that we have detected wheatstone bridge
			circuitSolutionsFile << "This is a Wheatstone bridge problem.\n";
			
			// variables for source voltage and source current
			double Vs, Is;
			// variables for resistances
			int R1, R2, R3, R4, R5;
			// variable for resistor multiplier n
			int n;

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
			circuitSolutionsFile << "Resistor: R5 = " << R5 << " Ohms.\n";

			// detect cases where Wheatstone bridge circuit algorithm
			// will fail with divide-by-zero
			if ( (R2 == 0) || (R3 == 0) )
			{
				// print error message and exit with -1
				cout << "The algorithhm to solve the Wheatstone bridge\n";
				cout << "circuit problem associated with this assignment\n";
				cout << "will generate a divide-by-zero error for the\n";
				cout << "selected component values.\n";
				
				return -1;
			}

			circuitFile >> n;
			circuitSolutionsFile << "Number of resistor values: n = " << n << ".\n\n";

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
								// will fail with divide-by-zero
								 if ( (Vs == Is*n4*R4) || (Vs == -Is*n5*R5) )
								 {
									// print error message and exit with -1
									cout << "The algorithhm to solve the Wheatstone bridge\n";
									cout << "circuit problem associated with this assignment\n";
									cout << "will generate a divide-by-zero error for the\n";
									cout << "selected component values.\n";
									
									return -1;
								 }

								// display R1 = n1*R1 - R5 = n5*R5
								circuitSolutionsFile << "Resistor: R1 = " << n1*R1 << " Ohms.\n";			
								circuitSolutionsFile << "Resistor: R2 = " << n2*R2 << " Ohms.\n";
								circuitSolutionsFile << "Resistor: R3 = " << n3*R3 << " Ohms.\n";
								circuitSolutionsFile << "Resistor: R4 = " << n4*R4 << " Ohms.\n";
								circuitSolutionsFile << "Resistor: R5 = " << n5*R5 << " Ohms.\n";

								// declare variables for the coefficients a, b, c, d, e
								// in equation (3), and compute their values
								double a = 1 + 1.0*n4*R4/(n2*R2), 
									b = Vs - Is*n4*R4;
								double c = 1 + 1.0*n5*R5/(n3*R3), 
									d = Vs + Is*n5*R5;
								double e = 1.0*n1*R1/(n2*R2), 
									f = 1.0*n1*R1/(n3*R3);
								
								// report values for a, b, c, d, e for debugging
								circuitSolutionsFile << "a = " << a << ", b = " << b << ", c = " << c << "\n";
								circuitSolutionsFile << "d = " << d << ", e = " << e << ", f = " << f << "\n";

								// declare variables for the coefficients w, x, y, z,
								// and compute their values
								double w = (a+e)/b, x = f/b;
								double y = e/d, z = (c+f)/d;

								// report values for w, x, y, z for debugging
								circuitSolutionsFile << "w = " << w << ", x = " << x << "\n";
								circuitSolutionsFile << "y = " << y << ", z = " << z << "\n";
								
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
								circuitSolutionsFile << "\nSolution:\n";
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
		}
	}

	return 0;
}

