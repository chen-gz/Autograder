/*
 * Folhdeccic.h
 */

#ifndef FOLHDECCIC_H
#define FOLHDECCIC_H

#include "Lhdeccic.h"

// Class specification for a first-order differential equation
// (linear and homogeneous, with constant coefficients, and an 
// initial condition).  This is a derived class with the class
// for a differential equation of unspecified order as the base
// class.
class Folhdeccic : public Lhdeccic
{
	private:
	public:
		// default constructor
		Folhdeccic();
		// alternate constructor, accepts b, t0, K0
		Folhdeccic(double, double, double);

		// Mutators for b, t0, K0
		virtual void set_b(double);		// set b
		virtual void set_t0(double);	// set t0
		virtual void set_K0(double);	// set K0

		// fill solution signal with exponential values
		virtual void fillSoln();		

		// return text for differential equation
		virtual string get_diffy_q() const;
		// return text for initial condition
		virtual string get_init_cond() const;
		// write differential equation info to output file
		virtual void report_diffy_q(ofstream &) const;	
};

#endif


