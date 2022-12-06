/*
 * Lhdeccic.cpp
 */

#include "Lhdeccic.h"

//*********************************************************************
// Default constructor for Lhdeccic class, sets b, t0 and K0 so as to *
// define: y'(t) + y(t) = 0, y(0) = 1.                                *
//*********************************************************************
Lhdeccic::Lhdeccic()
{
	set_b(1);							// set b = 1
	set_t0(0);							// set t0 = 0
	set_K0(1);							// set K0 = 1
	setLabel("y");						// Label="y", fname="signal_y"
}
		
//*********************************************************************
// Alternate constructor for Lhdeccic class, sets b, t0 and K0 to the *
// values of the parameters.                                          *
//*********************************************************************
Lhdeccic::Lhdeccic(double b_in, double t0_in, double K0_in)
{
	set_b(b_in);						// set b to b_in
	set_t0(t0_in);						// set t0 to t0_in
	set_K0(K0_in);						// set K0 to K0_in
	setLabel("y");						// Label="y", fname="signal_y"
}
		
//*********************************************************************
// set_b sets b to the values of the parameter.                       *
//*********************************************************************
void Lhdeccic::set_b(double b_update)
{	b = b_update;		}

//*********************************************************************
// set_t0 sets t0 to the values of the parameter.                     *
//*********************************************************************
void Lhdeccic::set_t0(double t0_update)
{	t0 = t0_update;		}

//*********************************************************************
// set_K0 sets K0 to the values of the parameter.                     *
//*********************************************************************
void Lhdeccic::set_K0(double K0_update)
{	K0 = K0_update;		}

//*********************************************************************
// get_b returns the value of b.                                      *
//*********************************************************************
double Lhdeccic::get_b() const
{	return b;		}

//*********************************************************************
// get_t0 returns the value of t0.                                    *
//*********************************************************************
double Lhdeccic::get_t0() const
{	return t0;		}

//*********************************************************************
// get_K0 returns the value of K0.                                    *
//*********************************************************************
double Lhdeccic::get_K0() const
{	return K0;		}

//*********************************************************************
// Mutator function for signal label of diff. eqn. and sol'n.         *
//*********************************************************************
void Lhdeccic::setLabel(string L)
{	
	label = L;							// Set label to input string
	solution.setLabel(label);			// Set label for solution
}					

//*********************************************************************
// Accessor functions for signal label and filename template.         *
//*********************************************************************
string Lhdeccic::getLabel() const		// Returns signal label
{	return label;	}

//*********************************************************************
// getSolnPtr returns a pointer to the solution signal object.        *
//*********************************************************************
Signal * Lhdeccic::getSolnPtr()
{
	return &solution;
}

//*********************************************************************
// getSolnPtr returns a string containing an equation for the         *
// solution signal, e.g. y(t) = 5.00 exp( -(t - 1.00) / 3.00 ).       *
//*********************************************************************
string Lhdeccic::get_soln_eqn() const
{
	return getLabel() + "(t) = " + solution.getExpr();
}

//*********************************************************************
// textNum creates a string for use in the mathematical expression    *
// and figure title.  Numbers less than 100 are converted to a string *
// in fixed-point notation with 3 significant digits.  Larger values  *
// are truncated as int.  Works only if the double to be converted    *
// is at least 0.01                                                   *
//*********************************************************************
string Lhdeccic::textNum(double x) const
{
	if (x >= 100)
		return std::to_string(int(x));		// Large nums trunc. as int
	else
	{
		string x_exp = std::to_string(x);	// Small nums get 3 digits
		return x_exp.substr(0, 4 + (x<0));	// 4 chars, or 5 if x<0
	}
}	

//*********************************************************************
// report_diffy_q_solution writes an equation describing the solution *
// signal to the output file.                                         *
//*********************************************************************
void Lhdeccic::report_diffy_q_solution(ofstream &outFile) const
{
	outFile << "Solution\n";				// header
	outFile << "--------\n";				// line of dashses
	outFile << get_soln_eqn() << "\n\n";	// eqn for soln
	solution.writeSignalToFile();			// write soln to file
}
