/*
 * Signal.h
 */

#ifndef SIGNAL_H
#define SIGNAL_H

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
using std::string;
using std::vector;
using std::cout;

// Class specification for a time-domain signal
class Signal
{
	private:
		unsigned int nSamp;				// Number of samples
		double fs;						// Sampling frequency
		double t0;						// Initial time
		string label;					// label, e.g. x for x(t)
		string ofname;					// Output file name template
		string expression;				// Math expression for signal
		vector<double> s;				// Signal vector
		vector<double> t;				// Time vector

	public:
		// default constructor, N = 101, fs = 100 Hz, t0 = 0
		Signal();
		// alternate constructor, accepts N, fs, t0
		Signal(unsigned int, double, double);

		// Accessors and mutators for nSamp, fs, t0
		void setNumSamples(unsigned int);		// Set parameters.
		void setSampleRate(double);
		void setInitialTime(double);
		unsigned int getNumSamples() const;		// Get parameters
		double getSampleRate() const;
		double getInitialTime() const;

		// Mutators and accessors for label, filename template
		void setLabel(string);			// Set signal label
		string getLabel() const;		// Return signal label
		string getFilename() const;		// Return filename template

		// Mutator and accessor for mathematical expression
		void setExpr(string);			// Set math expression
		string getExpr() const;			// Return math expression

		// Accessors for signal & time vectors
		vector<double> getSigVec() const;
										// Return signal vector
		vector<double> getTimeVec() const;
										// Return time vector
		double getSigVec(unsigned int) const;
										// Return signal element
		double getTimeVec(unsigned int) const;
										// Return time element

		// Create different types of signals.
		void fillTimeVector();			// Fill time array
		void makeConstSignal(double);	// Create constant signal
		void makeSinusoid(double, double, double);
										// Create sinusoidal signal
		void makeExponential(double, double);
										// Create exponential signal

		// Overloaded operators
		const Signal operator= ( const Signal & );	// = 
		Signal operator + (const Signal &);			// +
		Signal operator * (const Signal &);			// *

		// Output functions
		void writeSignalToFile() const;	// Signal info -> .txt
		string textNum(double) const;	// string conversion for expr
		void quantize();				// Round signal values
};

#endif
