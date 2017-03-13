#include "NList.hpp"
#include "Fraction.hpp"
#include <iostream>

using namespace std;

int main() {

	NList<Fraction> fracList;

	Fraction f1(5, 9);
	
	fracList.push_back(f1);
	fracList.disableIndexing();
	fracList.displayList();
	return 0;
}