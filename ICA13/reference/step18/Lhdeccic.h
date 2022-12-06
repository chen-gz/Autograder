/*
 * Lhdeccic.h
 */

#ifndef LHDECCIC_H
#define LHDECCIC_H

#include <iostream>
#include <fstream>
#include "Signal.h"
using std::cout;
using std::string;
using std::ofstream;

// number of samples to compute for each time constant
const int SAMPS_PER_TAU = 100;
// number of time constants to compute solution
const int TAU_TO_PLOT = 5;

// Class specification for a differential equation of unspecified
// order.  The equation will be linear and homogeneous, with constant 
// coefficients, and an initial condition.  This class is an abstract 
// base class, from which the classes for first-order and second-order
// differential equations are derived. 
class Lhdeccic
{
	private:
		double b;						// DE: y'(t) + b*y(t) = 0
		double t0, K0;					// IC: y(t0) = K0
		string label;					// label, e.g. x for x(t)
		Signal solution;				// signal object for solution
	public:
		// default constructor
		Lhdeccic();
		// alternate constructor, accepts b, t0, K0
		Lhdeccic(double, double, double);
		
		// Mutators for b, t0, K0
		virtual void set_b(double);		// set b
		virtual void set_t0(double);	// set t0
		virtual void set_K0(double);	// set K0
		// Accessors for b, t0, K0	
		double get_b() const;			// return b
		double get_t0() const;			// return t0
		double get_K0() const;			// return K0

		// Mutators and accessors for label, filename template
		void setLabel(string);			// set signal label
		string getLabel() const;		// return signal label
		
		// Functions for generating the solution
		Signal * getSolnPtr();			// returns ptr to sol'n
		// fill solution with values
		// pure virtual function using = 0 notation
		virtual void fillSoln() = 0;
		string get_soln_eqn() const;	// returns soln equation

		// Output functions
		string textNum(double) const;	// string conversion for expr
		// return text for differential equation
		// pure virtual function using = 0 notation
		virtual string get_diffy_q() const = 0;
		// return text for initial condition
		// pure virtual function using = 0 notation		
		virtual string get_init_cond() const = 0;
		// write differential equation info to output file
		// pure virtual function using = 0 notation
		virtual void report_diffy_q(ofstream &) const = 0;
		// write solution info to output file
		virtual void report_diffy_q_solution(ofstream &) const;
};

#endif


