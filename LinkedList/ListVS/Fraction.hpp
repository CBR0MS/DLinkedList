// Filename: Fraction.hpp
// Additional Files: Fraction.cpp
// Created by Christian Broms on 2/20/17
// Compiler: MS Visual Studio 2015

/* CLASS INFORMATION:
*
* This class is designed to hold a fraction, using two
* distinct integer values. All augmented assignments, streams,
* comparison, and arithmetic operators have been overloaded to
* allow easier usage of fraction objects. Fractions are easily
* declared and initiated, this class with accept one or two parameters
* and construct a fraction. Be aware that when printing the fraction
* object, it is automatically simplified, but it is always stored
* in a non simplified manner.
*
*/

#include <iostream>
#include <limits>

#ifndef FRACTION_HPP
#define FRACTION_HPP

class Fraction
{
public:

	/***** CONSTRUCTORS & DESTRUCTOR *****/

	Fraction();
	Fraction(int p_num);
	Fraction(const int& p_num, const int& p_denom);
	~Fraction();

	/***** AUGMENTED ASSIGNMENTS *****/

	void operator+=(Fraction& rhs);
	void operator-=(Fraction& rhs);
	void operator*=(Fraction& rhs);
	void operator/=(Fraction& rhs);
	void operator+=(int rhs);
	void operator-=(int rhs);
	void operator*=(int rhs);
	void operator/=(int rhs);
	Fraction operator++();
	Fraction operator++(int p_dummy);
	Fraction operator--();
	Fraction operator--(int p_dummy);

	/***** STREAMS *****/

	friend std::ostream& operator<<(std::ostream& out, const Fraction& print);
	friend std::istream& operator>>(std::istream& in, Fraction& read);

	/***** COMPARISON OPERATORS *****/

	friend bool operator<(const Fraction& lhs, const Fraction& rhs);
	friend bool operator<=(const Fraction& lhs, const Fraction& rhs);
	friend bool operator==(const Fraction& lhs, const Fraction& rhs);
	friend bool operator>(const Fraction& lhs, const Fraction& rhs);
	friend bool operator>=(const Fraction& lhs, const Fraction& rhs);
	friend bool operator!=(const Fraction& lhs, const Fraction& rhs);

	/***** ARITHMETIC OPERATORS *****/

	friend Fraction operator+(const Fraction& lhs, const Fraction& rhs);
	friend Fraction operator-(const Fraction& lhs, const Fraction& rhs);
	friend Fraction operator*(const Fraction& lhs, const Fraction& rhs);
	friend Fraction operator/(const Fraction& lhs, const Fraction& rhs);

private:

	int gcd(const int& m, const int& n);
	int m_num;
	int m_denom;

};

// adding the limits template and specifying max, min and specialized
// see the README.md for more information

template<> class std::numeric_limits<Fraction> {			// define numeric limits for class

public:
	static Fraction min() { return Fraction(0); };			// define min
	static Fraction max() { return Fraction(INT_MAX); };		// define max
	static Fraction is_specialized() { return true; };		// must return true

};

#endif /* FRACTION_HPP */