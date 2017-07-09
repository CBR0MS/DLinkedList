# LinkedList


This `NList` class is built on a doubly-linked list using a basic node structure. It accepts any simple arithmetic type T or any complex class T. It is designed to be faster than the `std::Vector` and `std::List` classes in the C++ standard library.

## Examples

An integer list can be initalized as follows

```c++
NList<int> integerList;
```

The list is a template and can be used with any class 

```c++
class anyClass;
NList<anyClass> classList;
```

Using the list to store characters

```c++
#include "List.hpp"

int main(){

NList<char> charList;

charList.push_back('d');  // adds 'd'
charList.push_back('x');  // adds 'x'
charList.push_front('a'); // adds 'a'
charList.pop_back();      // removes 'x'

charList.displayList();	  // display the list
}
```

## Indexing

The `NList` class allows the use of indexing through `operator[](const int* index)`. Passing an index to this function will return the data stored at that position in the list. The list uses a standard indexing system starting with index 0. Note that by default, indexing is *disabled*, and must be manually set on in order to use functions listed in [Section 3](#section-3---functions-with-preconditions). To enable indexing, call the void function `NList::enableIndexing()`. 

### Performance and Efficiency with Indexing

When indexing is enabled, adding and removing values from the list will be slower, as the indecies must be updated on every call. The `NList` uses a secondary dynamic array to store pointers, and whenever a node is added to the list, the array must be updated. When adding and removing values from the list, it is recommended that `NList::push_back()` and `NList::pop_back()` are used, as they will complete faster due to the nature of updating the index array. If the use of indexing is not desired, ensure that `NList::enableIndexing()` is never called, as it will slow down the list process consiterably. If the use of indexing is no longer needed partway through a program, it can be disabled with `NList::disableIndexing()`. To see a speed comparison of the `NList` and other dynamic containers in C++ reference [Speed and Efficiency](#speed-and-efficiency). 


## Public Functions


### Section 1 - Functions with no preconditions

Function        | Description    				  | Return type
-------------   | ----------------------------------------------- |------------
NList           | default constructor				  | void
assign          | add a specified value to entire container       | void 
push_back       | add a value to the back of the list             | void
pop_back        | remove the last list value			  | void
push_front      | add a value to the front of the list     	  | void
pop_front       | remove the first value in the list 		  | void
enableIndexing  | enables the use of indexing and [] operator     | void   
disableIndexing | disables the use of indexing			  | void
erase           | removes all instances of the passed value 	  | void
clear           | removes the entire contents of the list	  | void
clearAllExcept  | removes all except the passed value		  | void
expandCapacity  | makes the capacity larger by intervals of 1000  | void
size 		| returns the size of the list			  | int
currentCapacity | returns the capacity of the list		  | unsigned long
maxtCapacity 	| returns recommended max capacity of list        | unsigned long
maxCapacity     | returns max possible capacity of the list	  | unsigned long
isEmpty		| if the list has any contents			  | boolean
operator+ 	| combines two list objects into one		  | NList


### Section 2 - Functions with specifications

The following functions require some additional specifications added to your class. See [Defining Numeric Classes](#defining-numeric-classes) for more information. If they are called without the specifications, they will return false.

Function        | Description    				  | Return type
-------------   | ----------------------------------------------- |------------
displayList     | displays the entire list with std::cout	  | boolean
sortAscending   | sort the list in ascending order                | boolean 
SortDescending  | sort the list in descending order               | boolean


### Section 3 - Functions with preconditions

These functions require that indexing is enabled on your list. By default, the list does not use indexing, so it must be enabled by calling `NList::enableIndexing()`. These functions will throw an error if indexing is disabled. 

Function        | Description    				  | Return type
-------------   | ----------------------------------------------- |------------
at              | returns the object stored at passed index	  | T
operator[]      | returns the object stored at passed index       | T 


## Defining Numeric Classes

In order to call functions from [Section 2](#section-2---functions-with-specifications) in the `NList` class, you must define the numeric limits of your custom class. This is only necessary if the list is storing custom complex classes, not simple arithmetic ones such as `int` and `char` or even classes predefined in the standard library such as `std::string`. If your class has no easily defined limits or is not arithmetic, you cannot use any of the functions listed in [Section 2](#section-2---functions-with-specifications). However, if the class has limits, you must include the following template in your class' header file. 

```c++
// YOURCLASS defininitons here { ... };

template<> class std::numeric_limits<YOURCLASS> {		// define numeric limits for class

public:
	static Fraction min() { return YOURCLASSMIN; };		// define min
	static Fraction max() { return YOURCLASSMAX; };		// define max
	static Fraction is_specialized() { return true; };	// must return true
};
```
Once this code has been included in your class header, the functions listed in [Section 2](#section-2---functions-with-specifications) become available. To see an example of this template in use, refrence [the fraction class](https://github.com/CBR0MS/DLinkedList/blob/master/LinkedList/NList%20Files/Fraction.hpp). 

Note that numeric class limits are needed for `NList` to sort and display the entire list more efficiently. Providing limits unlocks this functionality, but does not slow down any other processes. 


## Speed and Efficiency 

This List function is designed to be efficient, faster than the Vector and List classes from the C++ standard library. Here is a sample comparison of the three classes and the speeds at which their common functions execute. 

```
All times measured in mircoseconds...Lower is better...
Indexing is enabled on the linked list...

TEST 1: push_back 100 integer objects
NList:           48 µs
std::List:       274 µs
std::Vector:     174 µs

TEST 2: pop_back 50 integer objects
NList:           3 µs
std::List:       343 µs
std::Vector:     54 µs

TEST 3: push_front 100 integer objects
NList:           118 µs
std::List:       292 µs
std::Vector:     N/A

TEST 4: pop_front 50 integer objects
NList:           48 µs
std::List:       335 µs
std::Vector:     N/A
```

Find this test file [here](https://github.com/CBR0MS/DLinkedList/blob/master/LinkedList/NList%20Files/TESTM_NListTime.cpp). Note that during testing, indexing was enabled on NList.

## Files

```
/DLinkedList/
|  
|--/LinkedList/
|    |    
|    |--/ListVSProj/                # full visual studio project
|    |    | ...
|    |    
|    |--/ListXCProj/                # full Xcode project
|    |    | ...
|    |     
|    |--/NListFiles/
|    |     |
|    |     |--Fraction.cpp          # example class to be stored in NList
|    |     |--Fraction.hpp          # example class to be stored in NList
|    |     |--NList.hpp             # NList full class template 
|    |     |--TESTM_NListTime.cpp   # a few tests to run on NList
|
|--LICENSE 
|--README.md

```
