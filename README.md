# LinkedList


This `NList` class is built on a doubly-linked list using a basic node structure. It accepts any simple arithmetic type T or any complex class T.

## Examples

An integer list can be initalized as follows

```c++
NList<int> integerList;
```

The list is a template and can be used with any class 

```c++
class T;
NList<T> classList;
```

Here's an example using the list to store characters 

```c++
#include "List.hpp"

int main(){

List<char> charList;

charList.push_back('d');  // adds 'd'
charList.push_back('x');  // adds 'x'
charList.push_front('a'); // adds 'a'
charList.pop_back();      // removes 'x'

charList.displayList();
}
```

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

The following functions require some additional specifications added to your class. See [Defining Numeric Classes](##Defining Numeric Classes) for more imformation. If they are called without the specifications, they will return false.

Function        | Description    				  | Return type
-------------   | ----------------------------------------------- |------------
displayList     | displays the entire list with std::cout	  | boolean
sortAscending   | sort the list in ascending order                | boolean 
SortDescending  | sort the list in descending order               | boolean

### Section 3 - Functions with preconditions

These functions require that indexing is enabled on your list. By default, the list does not use indexing, so it must be enabled by calling `enableIndexing`. These functions will throw an error if indexing is disabled. 

Function        | Description    				  | Return type
-------------   | ----------------------------------------------- |------------
at              | returns the object stored at passed index	  | T
operator[]      | exact same behavior as the at function          | T 

## Defining Numeric Classes

In order to call functions from [Section 2](### Section 2 - Functions with specifications) in the `NList` class, you must define the numeric limits of your custom class. This is only necessary if the list is storing custom complex classes, not simple arithmetic ones such as `int` and `char` or even classes predefined in the standard library such as `std::string`. If your class has no easily defined limits or is not arithmetic, you cannot use any of the functions listed in [Section 2](### Section 2 - Functions with specifications). However, if the class has limits, you must include the following template in your class' header file. 

```c++
// YOURCLASS defininitons here { ... };

template<> class std::numeric_limits<YOURCLASS> {		// define numeric limits for class

public:
	static Fraction min() { return YOURCLASSMIN; };		// define min
	static Fraction max() { return YOURCLASSMAX; };		// define max
	static Fraction is_specialized() { return true; };	// must return true
};
```
Once this code has been included in your class header, the functions listed in [Section 2](### Section 2 - Functions with specifications) become available. To see an example of this template in use, refrence `DLinkedList/LinkedList/ListVS/Fraction.hpp`. 

## Speed and Efficiency 

This List function is designed to be efficient, faster than the Vector and List classes from the C++ standard library. Here is a comparison of the three classes and the speeds at which their common functions execute. In this output, `List` refers the linked list class from this repo, `std List` is from the C++ library, and `Vector` also comes from the library. 

```
All times measured in mircoseconds...
Indexing is enabled on the linked list...

TEST 1: push_back 100 integer objects
List:           48 µs
std List:       274 µs
Vector:         174 µs

TEST 2: pop_back 50 integer objects
List:           3 µs
std List:       343 µs
Vector:         54 µs

TEST 3: push_front 100 integer objects
List:           118 µs
std List:       292 µs
Vector:         N/A

TEST 4: pop_front 50 integer objects
List:           48 µs
std List:       335 µs
Vector:         N/A
```

This test file can be found in this repo at `LinkedList/List/List/TimeTestingList.cpp`. Note that indexing is enabled on the linked list, which does slow it down, and without it the speeds are even lower. 

## Further Customization

If you wish to add more to your class' limits template, I recommend that you reference [this helpful resource from cplusplus.com]
(http://www.cplusplus.com/reference/limits/numeric_limits/). Any additional functions should be added to the List class located at  `LinkedList/List/List/List.hpp`. The layout of the file is a standard template, with function declarations at the top and definitions below; define any new functions in this same manner. 
