/*
 * Solhdeccic.cpp
 */

#include "Solhdeccic.h"
using std::to_string;

//*********************************************************************
// Default constructor for Solhdeccic class, calls the default        *
// constructor for the base class, and sets a, b, t0, K0 and K1 so as *
// to define: y''(t) + 3y'(t) + 2y(t) = 0, y(0) = 0, y'(0) = 1.       *
//*********************************************************************
Solhdeccic::Solhdeccic() : Lhdeccic::Lhdeccic()
{
	set_a(3);							// set a = 3
	set_b(2);							// set b = 2
	set_t0(0);							// set t0 = 0
	set_K0(0);							// set K0 = 0
	set_K1(1);							// set K1 = 1
	setLabel("y");						// Label="y", fname="signal_y"
	fillSoln();							// fill solution signal
}
		
//*********************************************************************
// Alternate constructor for Solhdeccic class, calls the constructor  *
// for the base class, and passes b, t0 and K0 to it.  Then sets a    *
// and K1 to the values of thos parameters.
//*********************************************************************
Solhdeccic::Solhdeccic(double a_in, double b_in, double t0_in, double K0_in, double K1_in)
	: Lhdeccic(b_in, t0_in, K0_in)
{
	set_a(a_in);						// set a
	set_K1(K1_in);						// set K1
	setLabel("y");						// Label="y", fname="signal_y"
	fillSoln();							// fill solution signal
}

//*********************************************************************
// set_a sets a to the value of the parameter.                        *
//*********************************************************************
void Solhdeccic::set_a(double a_update)
{	a = a_update;			}

//*********************************************************************
// set_K1 sets K1 to the value of the parameter.                      *
//*********************************************************************
void Solhdeccic::set_K1(double K1_update)
{	K1 = K1_update;			}

//*********************************************************************
// get_a returns the value of a.                                      *
//*********************************************************************
double Solhdeccic::get_a() const
{	return a;				}

//*********************************************************************
// get_K1 returns the value of K1.                                    *
//*********************************************************************
double Solhdeccic::get_K1() const
{	return K1;				}


//*********************************************************************
// get_diffy_q returns a string containing the differential equation  *
//*********************************************************************
string Solhdeccic::get_diffy_q() const
{
	// begin output string with second derivative of signal
	string eqn = getLabel() + "''(t)" ;

	// if the coefficient a is positive,
	if (a > 0)
		// append first derivative with + sign and coeff.
		eqn += " + " + textNum(a) + " " + getLabel() + "'(t)";
	// if the coefficient a is negative,
	else if (a < 0)
		// append first derivative with - sign and coeff.
		eqn += " - " + textNum(-a) + " " + getLabel() + "'(t)";

	// if the coefficient b is positive,
	if (get_b() > 0)
		// append signal with + sign and coeff.
		eqn += " + " + textNum(get_b()) + " " + getLabel() + "(t)";
	// if the coefficient a is negative,
	else if (get_b() < 0)
		// append signal with - sign and coeff.
		eqn += " - " + textNum(-get_b()) + " " + getLabel() + "(t)";

	// append RHS, i.e. " = 0"
	eqn += " = 0";
	return eqn;
}

//*********************************************************************
// get_init_cond returns a string containing the initial condition    *
//*********************************************************************
string Solhdeccic::get_init_cond() const
{
	// string to store init. cond.
	string ic;
	// assemble LHS of 1st condition
	ic = getLabel() + "(" + textNum(get_t0()) + ") = ";
	// append RHS of 1st condition and derivative
	ic += textNum(get_K0()) + ", " + getLabel() + "'(";
	// append remainder of 2nd condition
	ic += textNum(get_t0()) + ") = " + textNum(get_K1());
	return ic;
}

//*********************************************************************
// report_diffy_q writes a text version of the differential equation  *
// and initial conditions to the output file.                         *
//*********************************************************************
void Solhdeccic::report_diffy_q(ofstream &outFile) const
{
	// report differential equation
	outFile << "----------------------------------\n";
	outFile << "Second-Order Differential Equation\n";
	outFile << "----------------------------------\n";
	outFile << get_diffy_q() << "\n\n";

	// report initial conditions
	outFile << "Initial Condition\n";
	outFile << "-----------------\n";
	outFile << get_init_cond() << "\n\n";
}

//*********************************************************************
// fillSoln fills the solution signal with the correct values.  At    *
// this point, we are assuming the 2nd-order equation is underdamped, *
// so the solution is the sum of two exponentials.                    *
//*********************************************************************
void Solhdeccic::fillSoln()
{
	// pointer to the solution signal
	Signal * soln = getSolnPtr();
	// set no. of samples to specified no. of time constants
	soln -> setNumSamples(TAU_TO_PLOT * SAMPS_PER_TAU + 1);
	// set t0 for solution to t0 for diff. eqn.
	soln -> setInitialTime(get_t0());

	// temp variable for discriminant
	double d = a*a - 4*get_b();
	
	if (d > 0)
	{
		// exponential rates for two terms
		double lambda1 = (-get_a() + sqrt(d))/2;
		double lambda2 = (-get_a() - sqrt(d))/2;
		// set sample rate so that specified number of tau are computed
		soln -> setSampleRate(SAMPS_PER_TAU * abs(lambda1));
		// coefficients for the two exponential signals
		double c1 = (get_K0()*lambda2 - get_K1()) / (lambda2 - lambda1);
		double c2 = (-get_K0()*lambda1 + get_K1()) / (lambda2 - lambda1);
		// make the solution signal c1 * exp( lambda1 * t )
		soln -> makeExponential(c1, -1/lambda1);
		// make a second signal to store second exponential term
		Signal soln_term2 = *soln;
		// make the new signal c2 * exp( lambda2 * t )
		soln_term2.makeExponential(c2, -1/lambda2);
		// add the two signals, store back in solution
		*soln = *soln + soln_term2;
	}
	else if (d < 0)
	{
		// exponential rate and sinusoidal frequency
		double sigma = a/2, omega = sqrt(-d/4);
		// set sample rate so that specified number of tau are computed
		soln -> setSampleRate(SAMPS_PER_TAU * fabs(sigma));
		// make the solution signal exp( -sigma*t )
		soln -> makeExponential(1, 1/sigma);
		// make a second signal to store cosine term
		Signal soln_term2 = *soln;
		// make the second signal K0 * cos( omega * t )
		soln_term2.makeSinusoid(get_K0(), omega/(2*M_PI), 0);
		// coefficient for sine term
		double B = (get_K1() - sigma*get_K0()) / omega;
		// make a third signal to store sine term
		Signal soln_term3 = *soln;
		// make the third signal B * sin( omega * t )
		soln_term3.makeSinusoid(B, omega/(2*M_PI), -M_PI/2);
		// form the solution signal using operators
		*soln = *soln * (soln_term2 + soln_term3);
	}
	else
	{
		// exponential rate
		double lambda = -get_a()/2;
		// set sample rate so that specified number of tau are computed
		soln -> setSampleRate(SAMPS_PER_TAU * fabs(lambda));
		// coefficients for the two terms in ramp signal
		double c1 = get_K0();
		double c2 = get_K0()*get_a()/2 + get_K1();
		// make the solution signal c2 * (t - t0) + c1
		soln -> makeRamp(c2, c1);
		// make a second signal to store exponential term
		Signal soln_term2 = *soln;
		// make the new signal exp( lambda * t )
		soln_term2.makeExponential(1, -1/lambda);
		// multiply the two signals, store back in solution
		*soln = *soln * soln_term2;
	}
	// round signal samples to nearest integers
	soln -> quantize();
}






