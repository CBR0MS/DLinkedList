LinkedList
======

This list class is built on a doubly-linked list using a basic Node structure. It accepts any simple arithmetic type T or any complex class T.

Examples
------

An integer list can be initalized as follows

```c++
List<int> integerList;
```

The list is a template and can be used with any class 

```c++
class T;
List<T> classList;
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

*Important Note*
------

For proper functionality when using this list class with any complex class T, the header file 'classLimitsDefs.hpp' must be both
included *and* modified. This list class uses the limits template, which requires a limit definition for any non-simple arithmetic
type or class. When using the class template with a simple arithmetic type such as an int, char, or double, there is no need to use the
'classLimitsDefs.hpp' file. However, if you wish to use this list as a container for your own classes, include this header file and
modify as shown below

Modifying the Limits Template
------

When using a custom class type, the following must be modified to provide the list function with a max and min value. If not provided, the list could potentially skip values when calling `List::displayList()`. The values will remain in the list and acessable via the `[]` operator, but usage of this display function may not be dependable. To ensure it is, this is the template that must be edited in accordance with your class' value rage. 

```c++
#include "YourClass.hpp"
#include <limits>

template<> class std::numeric_limits<YourClass> {

public:
	static Fraction min() { return YourClass(CLASS_MIN); };
	static Fraction max() { return YourClass(CLASS_MAX); };
};
```

For example, a class `Fraction` of non-negative integer values would require the following initalizations:

```c++
#include "Fraction.hpp"
#include <limits>

template<> class std::numeric_limits<Fraction> {

public:
	static Fraction min() { return Fraction(0); };
	static Fraction max() { return Fraction(INT_MAX); };
};
```
This very useful fraction class is provided in this repo. 

Speed and Efficiency 
-----

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

Further Customization
-----

If you wish to add more to your class' limits template, I recommend that you reference [this helpful resource from cplusplus.com]
(http://www.cplusplus.com/reference/limits/numeric_limits/). Any additional functions should be added to the List class located at  `LinkedList/List/List/List.hpp`. The layout of the file is a standard template, with function declarations at the top and definitions below; define any new functions in this same manner. 
