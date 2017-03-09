// Filename: Fraction.cpp
// Additional Files: Fraction.hpp
// Created by Christian Broms on 2/20/17
// Compiler: MS Visual Studio 2015

// See 'Fraction.hpp' for class information

#include "Fraction.hpp"
#include <iostream>
#include <sstream>
#include <string>

/***** CONSTRUCTORS & DESTRUCTOR *****/

Fraction::Fraction() {

	m_num = 1;
	m_denom = 1;
}

Fraction::Fraction(int p_num) {

	m_num = p_num;
	m_denom = 1;
}

Fraction::Fraction(const int& p_num, const int& p_denom) {

	m_num = p_num;
	m_denom = p_denom;
}

Fraction::~Fraction() {

}

/***** AUGMENTED ASSIGNMENTS *****/

void Fraction::operator+=(Fraction& rhs) {

	if (this->m_denom == rhs.m_denom) {

		this->m_num = rhs.m_num + this->m_num;
	}
	else {

		Fraction temp;
		temp.m_denom = this->m_denom;
		temp.m_num = this->m_num;
		this->m_denom *= rhs.m_denom;
		this->m_num *= rhs.m_denom;
		rhs.m_denom *= temp.m_denom;
		rhs.m_num *= temp.m_denom;

		this->m_num = rhs.m_num + this->m_num;
	}
}

void Fraction::operator-=(Fraction &rhs) {

	if (this->m_denom == rhs.m_denom) {

		this->m_num = this->m_num - rhs.m_num;
	}
	else {

		Fraction temp;
		temp.m_denom = this->m_denom;
		temp.m_num = this->m_num;
		this->m_denom *= rhs.m_denom;
		this->m_num *= rhs.m_denom;
		rhs.m_denom *= temp.m_denom;
		rhs.m_num *= temp.m_denom;

		this->m_num = this->m_num - rhs.m_num;
	}
}

void Fraction::operator*=(Fraction &rhs) {

	this->m_num = this->m_num * rhs.m_num;
	this->m_denom = this->m_denom * rhs.m_denom;
}

void Fraction::operator/=(Fraction &rhs) {

	this->m_num = this->m_num *= rhs.m_denom;
	this->m_denom = this->m_denom *= rhs.m_num;
}

void Fraction::operator+=(int rhs) {

	Fraction temp(rhs);
	temp.m_num *= this->m_denom;
	this->m_num = temp.m_num + this->m_num;
}

void Fraction::operator-=(int rhs) {

	Fraction temp(rhs);
	temp.m_num *= this->m_denom;
	this->m_num -= temp.m_num;
}

void Fraction::operator*=(int rhs) {

	Fraction temp(rhs);
	this->m_num *= temp.m_num;
	this->m_denom *= temp.m_denom;
}

void Fraction::operator/=(int rhs) {

	Fraction temp(rhs);
	this->m_num = this->m_num *= temp.m_denom;
	this->m_denom = this->m_denom *= temp.m_num;

}

Fraction Fraction::operator++() {

	this->m_num += m_denom;
	return *this;
}

Fraction Fraction::operator++(int p_dummy) {

	Fraction temp;
	temp.m_denom = this->m_denom;
	temp.m_num = this->m_num;
	this->m_num += m_denom;
	return temp;
}

Fraction Fraction::operator--() {
	this->m_num -= m_denom;
	return *this;
}

Fraction Fraction::operator--(int p_dummy) {

	Fraction temp;
	temp.m_denom = this->m_denom;
	temp.m_num = this->m_num;
	this->m_num -= m_denom;
	return temp;
}

/***** STREAMS *****/

std::ostream& operator<<(std::ostream& out, const Fraction& print) {

	// make an editable version of the fraction to be printed
	Fraction editable = print;

	if (editable.m_num / static_cast<double>(editable.m_denom) == 1) {
		// the fraction simplifies to 1

		out << 1;
	}
	else if (editable.m_num / static_cast<double>(editable.m_denom) > 1) {
		// some whole number(s) can be removed

		int whole = editable.m_num / editable.m_denom;
		editable.m_num -= whole * editable.m_denom;

		if (print.m_num == 0) {
			// the fraction simplifies to a whole number

			out << whole;
		}
		else {
			// try simplifying the fraction

			int divisor = editable.gcd(editable.m_num, editable.m_denom);

			if (divisor != 1) {
				editable.m_num /= divisor;
				editable.m_denom /= divisor;
			}
			if (editable.m_num != 0) {
				out << whole << '+' << editable.m_num << '/' << editable.m_denom;
			}
			else {
				out << whole;
			}
		}
	}
	else {
		// the fraction is less than 1

		int divisor = editable.gcd(editable.m_num, editable.m_denom);

		if (divisor != 1) {
			// try simplifying the fraction 

			editable.m_num /= divisor;
			editable.m_denom /= divisor;
		}
		if (editable.m_num != 0) {
			out << editable.m_num << '/' << editable.m_denom;
		}
		else {
			out << 0;
		}
	}

	return out;
}

std::istream& operator>>(std::istream& in, Fraction& read) {

	std::string str = "";
	char plus = ' ';
	char forwardSlash = ' ';

	in >> str;

	// make a stringstream to look for '+' and '/'
	std::stringstream ss(str);

	int whole = 0;
	int num = 0;
	int denom = 1;

	ss >> whole;

	if (!ss.eof()) {

		if (ss.peek() == '/') {
			// the fraction is less than 1

			num = whole;
			whole = 0;
			ss >> forwardSlash;
			ss >> denom;
		}
		else if (ss.peek() == '+') {
			// the fraction is greater than 1

			ss >> plus;
			ss >> num;
			ss >> forwardSlash;
			ss >> denom;
		}
	}
	// pass as an improper fraction
	num = num + whole * denom;
	read.m_num = num;
	read.m_denom = denom;

	return in;
}

/***** COMPARISON OPERATORS *****/

bool operator<(const Fraction& lhs, const Fraction& rhs) {

	return  lhs.m_num * rhs.m_denom < rhs.m_num * lhs.m_denom ? true : false;
}

bool operator<=(const Fraction& lhs, const Fraction& rhs) {

	return  lhs.m_num * rhs.m_denom <= rhs.m_num * lhs.m_denom ? true : false;
}

bool operator==(const Fraction& lhs, const Fraction& rhs) {

	return  lhs.m_num * rhs.m_denom == rhs.m_num * lhs.m_denom ? true : false;
}

bool operator>(const Fraction& lhs, const Fraction& rhs) {

	return  lhs.m_num * rhs.m_denom > rhs.m_num * lhs.m_denom ? true : false;
}

bool operator>=(const Fraction& lhs, const Fraction& rhs) {

	return  lhs.m_num * rhs.m_denom >= rhs.m_num * lhs.m_denom ? true : false;
}

bool operator!=(const Fraction& lhs, const Fraction& rhs) {

	return  lhs.m_num * rhs.m_denom != rhs.m_num * lhs.m_denom ? true : false;
}


/***** ARITHMETIC OPERATORS *****/

Fraction operator+(const Fraction &lhs, const Fraction& rhs) {

	Fraction temp;

	if (lhs.m_denom == rhs.m_denom) {

		temp.m_denom = lhs.m_denom;
		temp.m_num = lhs.m_num + rhs.m_num;
	}
	else {

		Fraction lhsE;
		lhsE = lhs;
		Fraction rhsE;
		rhsE = rhs;
		temp.m_num = lhsE.m_num * rhsE.m_denom + lhsE.m_denom * rhsE.m_num;
		temp.m_denom = lhsE.m_denom * rhsE.m_denom;
	}

	return temp;
}

Fraction operator-(const Fraction &lhs, const Fraction& rhs) {

	Fraction temp;

	if (lhs.m_denom == rhs.m_denom) {

		temp.m_denom = lhs.m_denom;
		temp.m_num = lhs.m_num - rhs.m_num;
	}
	else {

		Fraction lhsE;
		lhsE = lhs;
		Fraction rhsE;
		rhsE = rhs;
		temp.m_num = lhsE.m_num * rhsE.m_denom - lhsE.m_denom * rhsE.m_num;
		temp.m_denom = lhsE.m_denom * rhsE.m_denom;
	}

	return temp;
}

Fraction operator*(const Fraction &lhs, const Fraction& rhs) {

	Fraction temp;

	temp.m_num = lhs.m_num * rhs.m_num;
	temp.m_denom = lhs.m_denom * rhs.m_denom;

	return temp;
}

Fraction operator/(const Fraction& lhs, const Fraction& rhs) {

	Fraction temp;

	temp.m_num = rhs.m_denom * lhs.m_num;
	temp.m_denom = rhs.m_num * lhs.m_denom;

	return temp;
}

// find greatest common divisor using euclidean algorithm
int Fraction::gcd(const int& m, const int& n) {

	if (m % n == 0) {
		return n;
	}
	else {
		return gcd(n, m % n);
	}
}