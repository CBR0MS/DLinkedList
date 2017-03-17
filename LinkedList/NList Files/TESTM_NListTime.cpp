// File: TESTM_NListTime.cpp
// Aditional Required File(s): NList.hpp
// Compilers Used: MS Visual Studio 2015 & Xcode 8.2.1
// Created by Christian Broms on 3/08/17

/* FILE DESCRIPTION:
 *
 * This file compares the speeds of the List class to both the
 * vector and list in the C++ standard library. Times are measured in
 * microseconds using the high resolution clock and will vary from
 * each excecution and computer due to changes in processor speed and
 * background processes. Sample output in the README.md
 *
 * OTHER INFORMATION:
 *
 * This file and all others found with it are a part of the public
 * repository that can be found at https://github.com/CBR0MS/DLinkedList
 * Licensed with the MIT License.
 *
 */

#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <list>
#include "NList.hpp"

using namespace std;
using namespace std::chrono;

int main() {

	// three types of mutatable lists to test

	NList<int> L1;
	vector<int> V1;
	list<int> L2;

	//L1.enableIndexing(); // this will slow down the list, but allows indexing

	high_resolution_clock::time_point t1;
	high_resolution_clock::time_point t2;

	string st1 = " ";
	st1 += static_cast<char>(230);
	st1 += "s\n";

	cout << "All times measured in mircoseconds...\n";
	cout << "Indexing is enabled on the linked list...\n";

	// testing time for push_back function on all 
	// adding 100 integers to the lists

	cout << "\nTEST 1: push_back 100 integer objects\n";

	// linked list 

	t1 = high_resolution_clock::now();
	for (int i = 0; i < 100; i++) {
		L1.push_back(i);
	}
	t2 = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(t2 - t1).count();

	cout << "List: \t\t" << duration << st1;

	// std list

	t1 = high_resolution_clock::now();
	for (int i = 0; i < 100; i++) {
		L2.push_back(i);
	}
	t2 = high_resolution_clock::now();

	duration = duration_cast<microseconds>(t2 - t1).count();

	cout << "std List: \t" << duration << st1;

	// vector 

	t1 = high_resolution_clock::now();
	for (int i = 0; i < 100; i++) {
		V1.push_back(i);
	}
	t2 = high_resolution_clock::now();

	duration = duration_cast<microseconds>(t2 - t1).count();

	cout << "Vector: \t" << duration << st1;


	// testing time for pop_back function on all 
	// removing 50 integers from the lists

	cout << "\nTEST 2: pop_back 50 integer objects\n";

	// linked list 

	t1 = high_resolution_clock::now();
	for (int i = 0; i < 50; i++) {
		L1.pop_back();
	}
	t2 = high_resolution_clock::now();

	duration = duration_cast<microseconds>(t2 - t1).count();

	cout << "List: \t\t" << duration << st1;

	// std list

	t1 = high_resolution_clock::now();
	for (int i = 0; i < 50; i++) {
		L2.pop_back();
	}
	t2 = high_resolution_clock::now();

	duration = duration_cast<microseconds>(t2 - t1).count();

	cout << "std List: \t" << duration << st1;

	// vector 

	t1 = high_resolution_clock::now();
	for (int i = 0; i < 50; i++) {
		V1.pop_back();
	}
	t2 = high_resolution_clock::now();

	duration = duration_cast<microseconds>(t2 - t1).count();

	cout << "Vector: \t" << duration << st1;

	// testing time for push_front function on all 
	// adding 100 integers to the lists

	cout << "\nTEST 3: push_front 100 integer objects\n";

	// linked list 

	t1 = high_resolution_clock::now();
	for (int i = 0; i < 100; i++) {
		L1.push_front(i);
	}
	t2 = high_resolution_clock::now();

	duration = duration_cast<microseconds>(t2 - t1).count();

	cout << "List: \t\t" << duration << st1;

	// std list

	t1 = high_resolution_clock::now();
	for (int i = 0; i < 100; i++) {
		L2.push_front(i);
	}
	t2 = high_resolution_clock::now();

	duration = duration_cast<microseconds>(t2 - t1).count();

	cout << "std List: \t" << duration << st1;

	// vector 

	cout << "Vector: \tN/A \n";

	// testing time for pop_front function on all 
	// removing 50 integers to the lists

	cout << "\nTEST 4: pop_front 50 integer objects\n";

	// linked list 

	t1 = high_resolution_clock::now();
	for (int i = 0; i < 50; i++) {
		L1.pop_front();
	}
	t2 = high_resolution_clock::now();

	duration = duration_cast<microseconds>(t2 - t1).count();

	cout << "List: \t\t" << duration << st1;

	// std list

	t1 = high_resolution_clock::now();
	for (int i = 0; i < 50; i++) {
		L2.pop_front();
	}
	t2 = high_resolution_clock::now();

	duration = duration_cast<microseconds>(t2 - t1).count();

	cout << "std List: \t" << duration << st1;

	// vector 

	cout << "Vector: \tN/A \n";

	return 0;
}

