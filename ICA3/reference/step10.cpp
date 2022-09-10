/*
 * ece0301_ICA03_step10.cpp
 */

#include <iostream>
// iomanip library needed for setprecision() and fixed manipulators
#include <iomanip>
// cmath library needed for sin, cos, atan, sqrt
#include <cmath>
using namespace std;

int main()
{
	// Display introductory message
	cout << "ECE 0301 - Vectors in R2 and Complex Numbers\n";
	cout << "Please enter two numbers, separated by a space,\n";
	cout << "that will represent a vector or a complex number.\n\n";

	// Coordinates for vector 1
	double x1, y1;
	
	// Read coordinates of vector 1 from user
	cin >> x1 >> y1;
	
	// Report vector 1 coordinates to user
	cout << "You entered " << setprecision(3) << fixed << x1 << " and " << y1 << ".\n\n";

	// Prompt user to choose Cartesian or polar coordinates
	cout << "Are these numbers in Cartesian (C) or polar (p) ";
	cout << "coordinates?\n";
	cout << "Please enter a single character as your choice.\n";
	
	// Variable to store user's choice of coordinates
	string c_or_p;
	
	// Read user's choice of coordinates
	cin >> c_or_p;
	
	// Exit if user response is more than 1 character
	if (c_or_p.length() > 1)
	{
		cout << "ERROR! Invalid selection, exiting.\n";
		return -1;
	}
	// Exit if user response is not c, C, p, or P.
	if (c_or_p != "c" && c_or_p != "C" && c_or_p != "p" && c_or_p != "P")
	{
		cout << "ERROR! Invalid selection, exiting.\n";
		return -1;
	}

	// Variable to store pi.
	double pi = 4.0 * atan(1.0);
	
	// Variables to store polar coordinates
	double R1, theta1;
	
	// Report user's numbers in Cartesian and polar coordinates
	if (c_or_p == "C" || c_or_p == "c")
	{
		// Tell the user they entered Cartesian coordinates.
		cout << "You entered Cartesian coordinates." << endl;
		
		// Convert to ploar coordinates
		R1 = sqrt(x1*x1 + y1*y1);
		theta1 = atan(y1/x1);
		if (x1<0)
		{
			// Add or subtract pi from angle if needed.
			if (y1>=0)
				theta1 += pi;
			else
				theta1 -= pi;
		}
		// Display polar coordinates.
		cout << "The equivalent polar coordinates are:" << endl;
		cout << "R = " << R1 << ", theta = " << theta1 << endl;
	}
	else
	{
		// Tell the user they entered polar coordinates.
		cout << "You entered polar coordinates." << endl;

		// The user entered polar coordinates.  Copy x,y to R,theta
		R1 = x1;
		theta1 = y1;
		
		// Test for invalid magnitude (R<0) or phase (theta > pi
		// or theta < -pi).  Return with -1 if this happens
		if ( (R1 < 0) || (theta1 < -pi) || (theta1 > pi) )
		{
			cout << "ERROR! Invalid polar coordinates, exiting.\n";
			return -1;
		}

		// Convert to Cartesian coordinates		
		x1 = R1 * cos(theta1);
		y1 = R1 * sin(theta1);
		
		// Display Cartesian coordinates.
		cout << "The equivalent Cartesian coordinates are:" << endl;
		cout << "x = " << x1 << ", y = " << y1 << endl;
	}


	// Prompt user to enter two more numbers
	cout << "Please enter another pair of numbers, separated by a\n";
	cout << "space, to represent a second vector or complex number.\n\n";
	
	// Coordinates for vector 2
	double x2, y2;

	// Read coordinates of vector 2 from user
	cin >> x2 >> y2;
	
	// Report vector 2 coordinates to user
	cout << "You entered " << setprecision(3) << fixed << x2 << " and " << y2 << ".\n\n";

	// Prompt user to choose Cartesian or polar coordinates
	cout << "Are these numbers in Cartesian (C) or polar (p) ";
	cout << "coordinates?\n";
	cout << "Please enter a single character as your choice.\n";
	
	// Read user's choice of coordinates
	cin >> c_or_p;
	
	// Exit if user response is more than 1 character
	if (c_or_p.length() > 1)
	{
		cout << "ERROR! Invalid selection, exiting.\n";
		return -1;
	}
	// Exit if user response is not c, C, p, or P.
	if (c_or_p != "c" && c_or_p != "C" && c_or_p != "p" && c_or_p != "P")
	{
		cout << "ERROR! Invalid selection, exiting.\n";
		return -1;
	}

	// Variables to store polar coordinates
	double R2, theta2;
	
	// Report user's numbers in Cartesian and polar coordinates
	if (c_or_p == "C" || c_or_p == "c")
	{
		// Tell the user they entered Cartesian coordinates.
		cout << "You entered Cartesian coordinates." << endl;
		
		// Convert to ploar coordinates
		R2 = sqrt(x2*x2 + y2*y2);
		theta2 = atan(y2/x2);
		if (x2<0)
		{
			// Add or subtract pi from angle if needed.
			if (y2>=0)
				theta2 += pi; // FIXED 9/3/2022
			else
				theta2 -= pi; // FIXED 9/3/2022
		}
		// Display polar coordinates.
		cout << "The equivalent polar coordinates are:" << endl;
		cout << "R = " << R2 << ", theta = " << theta2 << endl;
	}
	else
	{
		// Tell the user they entered polar coordinates.
		cout << "You entered polar coordinates." << endl;

		// The user entered polar coordinates.  Copy x,y to R,theta
		R2 = x2;
		theta2 = y2;
		
		// Test for invalid magnitude (R<0) or phase (theta > pi
		// or theta < -pi).  Return with -1 if this happens
		if ( (R2 < 0) || (theta2 < -pi) || (theta2 > pi) )
		{
			cout << "ERROR! Invalid polar coordinates, exiting.\n";
			return -1;
		}

		// Convert to Cartesian coordinates		
		x2 = R2 * cos(theta2);
		y2 = R2 * sin(theta2);
		
		// Display Cartesian coordinates.
		cout << "The equivalent Cartesian coordinates are:" << endl;
		cout << "x = " << x2 << ", y = " << y2 << endl;
	}

	// Prompt user to select vectors or complex numbers
	cout << "\nDo the values you entered represent vectors (v) or ";
	cout << "complex numbers (c)?\n";
	cout << "Please enter a single character as your choice.\n";
	
	// string variable to store user selection
	string v_or_c;
	
	// Read user selection
	cin >> v_or_c;

	// Exit if user response is more than 1 character
	if (v_or_c.length() > 1)
	{
		cout << "ERROR! Invalid selection, exiting.\n";
		return -1;
	}
	// Exit if user response is not v, V, c, or C.
	if (v_or_c != "v" && v_or_c != "V" && v_or_c != "c" && v_or_c != "C")
	{
		cout << "ERROR! Invalid selection, exiting.\n";
		return -1;
	}
	
	// If user selects vectors, display both sets of coordinates
	// in vector format
	if (v_or_c == "v" || v_or_c == "V")
	{
		cout << "Cartesian:\t v1 = (" << x1 << ", " << y1 << ")\n";
		cout << "Polar:\t\t v1 = (" << R1 << ", " << theta1 << ")\n\n";
		cout << "Cartesian:\t v2 = (" << x2 << ", " << y2 << ")\n";
		cout << "Polar:\t\t v2 = (" << R2 << ", " << theta2 << ")\n\n";
		
		cout << "Which of the following vector sums or differences\n";
		cout << "would you like to compute?\n";
		cout << "(1) v1 + v2\n";
		cout << "(2) v1 - v2\n";
		cout << "(3) v2 - v1\n";
		cout << "(4) -v1 - v2\n\n";
	}
	// If user selects complex numbers, display both sets of 
	// coordinates, in complex number format.
	else
	{
		cout << "Cartesian:\t z1 = " << x1;
		cout << (y1 >= 0 ? " +" : " -") << " j " << abs(y1) << "\n";
		cout << "Polar:\t\t z1 = " << R1 << " exp(";
		cout << (theta1 >= 0 ? "j " : "-j ") << abs(theta1) << ")\n\n";

		cout << "Cartesian:\t z2 = " << x2;
		cout << (y2 >= 0 ? " +" : " -") << " j " << abs(y2) << "\n";
		cout << "Polar:\t\t z2 = " << R2 << " exp(";
		cout << (theta2 >= 0 ? "j " : "-j ") << abs(theta2) << ")\n\n";
		
		cout << "Which of the following sums or differences\n";
		cout << "would you like to compute?\n";
		cout << "(1) z1 + z2\n";
		cout << "(2) z1 - z2\n";
		cout << "(3) z2 - z1\n";
		cout << "(4) -z1 - z2\n\n";		
	}

	//Variable to store menu selection
	int sum_choice;
	//Variables to store coordinates of sum
	double x_sum, y_sum, R_sum, theta_sum;
	
	//Read user menu selection
	cin >> sum_choice;
	
	//Compute the selected sum or difference
	switch(sum_choice)
	{
		case 1:
			x_sum = x1 + x2;
			y_sum = y1 + y2;
			break;
		case 2:
			x_sum = x1 - x2;
			y_sum = y1 - y2;
			break;
		case 3:
			x_sum = x2 - x1;
			y_sum = y2 - y1;
			break;
		case 4:
			x_sum = -x1 - x2;
			y_sum = -y1 - y2;
			break;
		
		default:
			cout << "ERROR! Invalid selection, exiting.\n";
			return -1;
	}
	//Convert to polar coordinates
	R_sum = sqrt(x_sum*x_sum + y_sum*y_sum);
	theta_sum = atan(y_sum/x_sum);
	// Add or subtract pi from angle if needed.
	if (x_sum < 0)
	{
		if (y_sum >= 0)
			theta_sum += pi;
		else
			theta_sum -= pi;
	}
	
	if (v_or_c == "v" || v_or_c == "V")
	{
		//Report selected vector sum to the user
		cout << "Sum, Cartesian:\t v_sum = (" << x_sum << ", " << y_sum << ")\n";
		cout << "Sum, Polar:\t v_sum = (" << R_sum << ", " << theta_sum << ")\n\n";		
	}
	else
	{
		//Report selected complex number sum to the user
		cout << "Sum, Cartesian:\t z_sum = " << x_sum;
		cout << (y_sum >= 0 ? " +" : " -") << " j " << abs(y_sum) << "\n";
		cout << "Sum, Polar:\t z_sum = " << R_sum << " exp(";
		cout << (theta_sum>= 0 ? "j " : "-j ") << abs(theta_sum) << ")\n";
	}

	return 0;
}

