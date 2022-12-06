/*
 * Folhdeccic.cpp
 */

#include "Folhdeccic.h"

//*********************************************************************
// Default constructor for Folhdeccic class, calls the constructor    *
// for the base class, and fills the solution signal.                 *
//*********************************************************************
Folhdeccic::Folhdeccic() : Lhdeccic::Lhdeccic()
{
	// fill solution signal with exponential signal
	fillSoln();
}
	
//*********************************************************************
// Alternate constructor for Folhdeccic class, calls the constructor  *
// for the base class, and passes the parameters to it.               *
//*********************************************************************
Folhdeccic::Folhdeccic(double b_in, double t0_in, double K0_in)
	: Lhdeccic::Lhdeccic(b_in, t0_in, K0_in)
{
	// fill solution signal with exponential signal
	fillSoln();
}

//*********************************************************************
// set_b sets b to the values of the parameter, and fills the         *
// solution signal with exponential values.                           *
//*********************************************************************
void Folhdeccic::set_b(double b_update)
{	
	Lhdeccic::set_b(b_update);
	fillSoln();
}

//*********************************************************************
// set_t0 sets t0 to the values of the parameter, and fills the       *
// solution signal with exponential values.                           *
//*********************************************************************
void Folhdeccic::set_t0(double t0_update)
{	
	Lhdeccic::set_t0(t0_update);
	fillSoln();
}

//*********************************************************************
// set_K0 sets K0 to the values of the parameter, and fills the       *
// solution signal with exponential values.                           *
//*********************************************************************
void Folhdeccic::set_K0(double K0_update)
{	
	Lhdeccic::set_K0(K0_update);
	fillSoln();
}

//*********************************************************************
// fillSoln fills the solution signal with exponential values, so     *
// that it is the correct solution to the differential equation.      *
//*********************************************************************
void Folhdeccic::fillSoln()
{
	//cout << "Inside fillSoln.\n";
	// pointer to solution signal
	Signal * soln = getSolnPtr();
	// time constant for exponential
	double tau = 1/get_b();
	// set no. of samples to specified no. of time constants
	soln -> setNumSamples(TAU_TO_PLOT * SAMPS_PER_TAU + 1);
	// set samp rate consistent with time constant
	soln -> setSampleRate(SAMPS_PER_TAU / fabs(tau));
	// set t0 for solution to t0 for diff. eqn.
	soln -> setInitialTime(get_t0());
	// create exponential signal K0 exp( -(t - t0) / tau )
	soln -> makeExponential(get_K0(), tau);
	// round solution signal values to integers
	soln -> quantize();
}

		
//*********************************************************************
// get_diffy_q returns a string containing the differential equation  *
//*********************************************************************
string Folhdeccic::get_diffy_q() const
{
	// begin output string with first derivative of signal
	string eqn = getLabel() + "'(t)" ;

	// if the coefficient is positive,
	if (get_b() > 0)
		// append signal with + sign and coeff.
		eqn += " + " + textNum(get_b()) + " " + getLabel() + "(t)";
	// if the coefficient is negative,
	else if (get_b() < 0)
		// append signal with - sign and coeff.
		eqn += " - " + textNum(-get_b()) + " " + getLabel() + "(t)";

	// append RHS, i.e. " = 0"
	eqn += " = 0";
	return eqn;
}

//*********************************************************************
// get_diffy_q returns a string containing the initial condition.     *
//*********************************************************************
string Folhdeccic::get_init_cond() const
{
	// string to store init. cond.
	string ic;
	// assemble LHS
	ic = getLabel() + "(" + textNum(get_t0()) + ") = ";
	// append RHS
	ic += textNum(get_K0());
	return ic;
}


//*********************************************************************
// report_diffy_q writes a text version of the differential equation  *
// and initial condition to the output file.                          *
//*********************************************************************
void Folhdeccic::report_diffy_q(ofstream &outFile) const
{
	// report differential equation
	outFile << "---------------------------------\n";
	outFile << "First-Order Differential Equation\n";
	outFile << "---------------------------------\n";
	outFile << get_diffy_q() << "\n\n";

	// report initial condition
	outFile << "Initial Condition\n";
	outFile << "-----------------\n";
	outFile << get_init_cond() << "\n\n";
}


