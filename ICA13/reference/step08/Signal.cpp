/*
 * Signal.cpp
 */

#include "Signal.h"

//*********************************************************************
// Default constructor for Signal class, sets the number of samples   *
// to 101, sampling rate to 100 Hz and initial time to 0.             *
//*********************************************************************
Signal::Signal()
{
	setNumSamples(101);			// Set nSamp, vector sizes
	setSampleRate(100);			// Set sampling rate
	setInitialTime(0);			// Set initial time
	setLabel("x");				// Label="x", fname="signal_x"
	setExpr("0");				// Expression for zero signal
}

//*********************************************************************
// Alternate constructor for Signal class, accepts parameters for     *
// number of samples, sampling rate and initial time.                 *
//*********************************************************************
Signal::Signal(unsigned int N, double R, double T)
{
	setNumSamples(N);			// Set nSamp, vector sizes
	setSampleRate(R);			// Set sampling rate
	setInitialTime(T);			// Set initial time
	setLabel("x");				// Label="x", fname="signal_x"
	setExpr("0");				// Expression for zero signal
}

//*********************************************************************
// Mutator functions for num samples, sampling rate, initial time.    *
//*********************************************************************
//*********************************************************************
// setNumberSamples sets the number of samples to the value of the    *
// parameter, changes the sizes of the time and signal vectors to the *
// ne number of samples, and fills the time vector with values.       *
//*********************************************************************
void Signal::setNumSamples(unsigned int N)
{	
	nSamp = N;					// Set number of samples
	s.resize(nSamp, 0);			// Make size of s = nSamp
	t.resize(nSamp, 0);			// Make size of t = nSamp
	fillTimeVector();			// t = t0, t0+dt ... t0+(nSamp-1)*dt	
}

//*********************************************************************
// setSampleRate sets the sampling rate to the value of the parameter *
// and fills the time vector with values.                             *
//*********************************************************************
void Signal::setSampleRate(double R)
{	
	fs = R;						// Set sampling rate
	fillTimeVector();			// t = t0, t0+dt ... t0+(nSamp-1)*dt	
}

//*********************************************************************
// setInitialTime sets the initial time to the value of the parameter *
// and fills the time vector with values.                             *
//*********************************************************************
void Signal::setInitialTime(double T)	
{	
	t0 = T;						// Set initial time
	fillTimeVector();			// t = t0, t0+dt ... t0+(nSamp-1)*dt	
}

	
//*********************************************************************
// Accessor functions for num samples, sampling rate, initial time.   *
//*********************************************************************
unsigned int Signal::getNumSamples() const	// Returns numer of samples
{	return nSamp;	}

double Signal::getSampleRate() const		// Returns sampling rate
{	return fs;	}

double Signal::getInitialTime() const		// Returns initial time
{	return t0;	}

//*********************************************************************
// Mutator function for signal label.                                 *
//*********************************************************************
void Signal::setLabel(string L)			// Sets signal label, filename
{	
	label = L;							// Set label to input string
	ofname = "diff_eqn_soln_" + label;			// filename w/ label
}

//*********************************************************************
// Accessor functions for signal label and filename template.         *
//*********************************************************************
string Signal::getLabel() const			// Returns signal label
{	return label;	}

string Signal::getFilename() const		// Returns filename template
{	return ofname;	}


//*********************************************************************
// Mutator and accessor functions for mathematical expression.        *
//*********************************************************************
void Signal::setExpr(string E)			// Sets mathematical expression
{	expression = E;	}

string Signal::getExpr() const			// Returns math expression
{	return expression;	}


//*********************************************************************
// Accessor functions for signal vector and time vector.  Both are    *
// overloaded with versions that return a single element.             *
//*********************************************************************
vector<double> Signal::getSigVec() const		// Returns signal vector
{	return s;	}

vector<double> Signal::getTimeVec() const		// Returns time vector
{	return t;	}

double Signal::getSigVec(unsigned int n) const	// Returns signal element
{	return s[n];	}

double Signal::getTimeVec(unsigned int n) const	// Returns time element
{	return t[n];	}


//*********************************************************************
// fillTimeVector writes nSamp linearly-spaced values to the time     *
// vector: t0, t0 + 1/fs, t0 + 2/fs, ... , t0 + (nSamp-1)/fs          *
//*********************************************************************
void Signal::fillTimeVector()
{
	for (unsigned int n=0; n<nSamp; n++)	// Loop over elements
		t[n] = t0 + n/fs;					// Linearly spaced times
}

//*********************************************************************
// makeConstSignal writes a constant to all nSamp elements of the     *
// signal vector, and sets the expression accordingly.                *
//*********************************************************************
void Signal::makeConstSignal(double A)
{
	for (unsigned int n=0; n<nSamp; n++)	// Loop over elements
		s[n] = A;							// Set each element to A

	expression = textNum(A);				// Expression for s(t) = A
}

//*********************************************************************
// makeSinusoid writes samples of the sinusoidal signal               *
// x(t) = A cos(2 pi f0 t + phi) to an existing Signal object.  The   *
// math expression is also set accordingly.                           *
//*********************************************************************
void Signal::makeSinusoid(double A, double f0, double phi)
{
	double PI = 4*atan(1.0);				// Stores pi = 3.14159...
	for (unsigned int n=0; n<nSamp; n++)	// Loop over elements
		// Compute sinudoidal signal sample
		s[n] = A * cos(2*PI*f0 * t[n] + phi);

	// Assemble math expression for sinusoid
	expression = textNum(A) + " cos( ";
	expression += textNum(2*PI*f0) + " t ";
	expression += (phi >=0) ? "+ " : "- ";
	expression += textNum(abs(phi)) + " )";
}

//*********************************************************************
// makeExponential writes samples of the exponential signal           *
// x(t) = A exp( -(t - t0) / tau ) to an existing Signal object.  The *
// math expression is also set accordingly.                           *
//*********************************************************************
void Signal::makeExponential(double A, double tau)
{
	// loop over indices for time & signal vectors
	for (unsigned int n=0; n<nSamp; n++)
		// Compute exponential signal sample
		s[n] = A * exp( -(t[n] - t0) / tau );

	// assemble math expression for exponential
	expression = textNum(A);
	// "exp( " and sign for exponent
	if (tau > 0)
		expression += " exp( -";
	else
		expression += " exp( ";
	// "(t +/- t0) " unless t0 = 0, then "t "
	if (t0 < 0)
		expression += "(t + " + textNum(-t0) + ") ";
	else if (t0 > 0)
		expression += "(t - " + textNum(t0) + ") ";
	else
		expression += "t ";
	
	// include tau as denom if it's not 1
	if (tau != 1)
		expression += "/ " + textNum(fabs(tau)) + " ";
	expression += ")";
}


//*********************************************************************
// Overloaded = operator for the Signal class that sets all member    *
// variables for the calling object equal to the corresponding        *
// variables for the input object, EXCEPT FOR the label and filename  *
// template.  Takes advantage of the overloaded = operator for the    *
// vector and string classes, so that these types can be copied to    *
// the calling object by assignment.                                  *
//*********************************************************************
const Signal Signal::operator= ( const Signal &sig )
{
	if (this != &sig)						// If no self-assignment
	{
		nSamp = sig.getNumSamples();		// Copy number of samples
		fs = sig.getSampleRate();			// Copy sampling rate
		t0 = sig.getInitialTime();			// Copy initial time
		s = sig.getSigVec();				// Copy signal vector
		t = sig.getTimeVec();				// Copy time vector
		expression = sig.getExpr();			// Copy math expression
	}
	return *this;							// Return copied signal
}

//*********************************************************************
// Overloaded + operator for the Signal class.   Test to see if the   *
// number of samples, sampling frequency and initial time are all     *
// equal for the calling object and input object, which guarantees    *
// that the two signals are defined for the same time ranges.  If so, *
// the time values for the returned object are set equal to the time  *
// values for the calling object, and the signal samples for the      *
// returned object are set to the sum of the samples for the input    *
// and calling objects.  The expression for the returned object is    *
// formed as the concatenation of the expressions for the input and   *
// calling objects, with " + " inserted between them.                 *
//*********************************************************************
Signal Signal::operator + (const Signal &sigIn)
{
	// Tests if input signal and calling signal have same times
	if ((nSamp == sigIn.nSamp) && (fs == sigIn.fs) && (t0 == sigIn.t0))
	{
		Signal sigOut(nSamp, fs, t0);			// New signal, same vars
		for (unsigned int i=0; i<nSamp; i++)	// Loop over elements
		{
			sigOut.s[i] = getSigVec(i) + sigIn.getSigVec(i);
												// Add signals
			sigOut.t[i] = getTimeVec(i);		// Copy times
		}
		
		// Assemble expression for returned signal
		sigOut.expression = getExpr() + " + " + sigIn.getExpr();

		return sigOut;							// Return summed signal
	}
	else
	{
		// Exit with failure code if signals have different times
		cout << "ERROR!  Attempt to add incompatible signals.\n";
		exit(EXIT_FAILURE);
	}
}

//*********************************************************************
// Overloaded * operator for the Signal class.   Identical in all     *
// respects to the overloaded + operator defined above, except that   *
// the returned signal is the product of the input signal and the     *
// calling signal, and the expression is set accordingly.             *
//*********************************************************************
Signal Signal::operator * (const Signal &sigIn)
{
	// Tests if input signal and calling signal have same times
	if ((nSamp == sigIn.nSamp) && (fs == sigIn.fs) && (t0 == sigIn.t0))
	{
		Signal sigOut(nSamp, fs, t0);			// New signal, same vars
		for (unsigned int i=0; i<nSamp; i++)	// Loop over elements
		{
			sigOut.s[i] = getSigVec(i) * sigIn.getSigVec(i);
												// Multiply signals
			sigOut.t[i] = getTimeVec(i);		// Copy times
		}
		
		// Assemble expression for returned signal
		sigOut.expression = "(" + getExpr() + ")";
		sigOut.expression += "(" + sigIn.getExpr() + ")";

		return sigOut;							// Return product signal
	}
	else
	{
		// Exit with failure code if signals have different times
		cout << "ERROR!  Attempt to multiply incompatible signals.\n";
		exit(EXIT_FAILURE);
	}
}


//*********************************************************************
// textNum creates a string for use in the mathematical expression    *
// and figure title.  Numbers less than 100 are converted to a string *
// in fixed-point notation with 3 significant digits.  Larger values  *
// are truncated as int.  Works only if the double to be converted    *
// is at least 0.01                                                   *
//*********************************************************************
string Signal::textNum(double x) const
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
// writeSignalToFile writes a signal to a text file: nSamp, fs, t0,   *
// signal label, filename template, and mathematical expression.      *
// The filename template is used with ".txt" appended.                *
//*********************************************************************
void Signal::writeSignalToFile() const
{
	// Output file stream object
	std::ofstream SignalFile;
	// Open file with object
	SignalFile.open(ofname + ".txt");

	// Write title line
	SignalFile << "Time-Domain Signal Samples\n";
	// Write nSamp, fs, t0
	SignalFile << "N = " << nSamp << "\n";
	SignalFile << "fs = " << fs << "\n";
	SignalFile << "t0 = " << t0 << "\n";
	SignalFile << "Signal label: " << label << "\n";
	
	// Header line for math expression
	SignalFile << "Mathematical expression\n";

	// Write equation for signal
	SignalFile << label << "(t) = " << expression << "\n";;
	
	// Write header for signal samples
	SignalFile << "Time and signal samples in .csv format\n";
	SignalFile << "t, " << label <<"(t)\n";
	SignalFile << "-------\n";
	
	// Write time and signal samples to file, csv format
	for (unsigned int n=0; n<nSamp; n++)
		SignalFile << t[n] << ", " << s[n] << "\n";

	// Close file
	SignalFile.close();
}

//**************************************************
// quantize rounds all the signal values to the    *
// nearest integer.                                *
//**************************************************

void Signal::quantize()
{
	for (unsigned int n=0; n<nSamp; n++)
	{
		s[n] = round( s[n] );
	}	
}



