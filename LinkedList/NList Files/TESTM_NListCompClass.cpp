#include "NList.hpp"
#include "Fraction.hpp"
#include <iostream>

using namespace std;

int main() {

	NList<Fraction> fracList;
//	fracList.enableIndexing();

	Fraction f1(5, 9);
	Fraction f2(8, 9);
	
	fracList.push_back(f1);
	fracList.push_back(f1);
	fracList.push_back(f1);
	fracList.push_back(f1);
	fracList.displayList();



	return 0;
}
