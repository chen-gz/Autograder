/*
 * ece0301_fall2019_inclass04_step02.cpp
 */

#include <iostream>
// need fstream library for file stream operations
#include <fstream>
using namespace std;

int main()
{
	// Display introductory message
	cout << "ECE 0301: Circuit Solver for Voltage Divider\n";
	cout << "and Wheatstone bridge example circuits.\n\n";

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

	return 0;
}

