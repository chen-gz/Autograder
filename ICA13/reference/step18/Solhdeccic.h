/*
 * Solhdeccic.h
 */

#ifndef SOLHDECCIC_H
#define SOLHDECCIC_H

#include "Lhdeccic.h"
using std::ofstream;

// Class specification for a second-order differential equation
// (linear and homogeneous, with constant coefficients, and an 
// initial condition).  This is a derived class with the class
// for a differential equation of unspecified order as the base
// class.
class Solhdeccic : public Lhdeccic
{
	private:
		double a;			// DE: y''(t) + ay'(t) + by(t) = 0
		double K1;			// IC: y(t0) = K0, y'(t0) = K1
	public:
		// default constructor
		Solhdeccic();
		// alternate constructor, accepts a, K1
		Solhdeccic(double, double, double, double, double);
		
		// Mutators for a, K1
		void set_a(double);				// set a
		void set_K1(double);			// set K1
		
		// Accessors for a, K1	
		double get_a() const;			// return a
		double get_K1() const;			// return K1

		// fill solution signal with values
		virtual void fillSoln();

		// return text for differential equation
		virtual string get_diffy_q() const;
		// return text for initial condition
		virtual string get_init_cond() const;
		// write differential equation info to output file
		virtual void report_diffy_q(ofstream &) const;
};

#endif


