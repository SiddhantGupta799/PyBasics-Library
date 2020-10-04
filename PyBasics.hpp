//  Author  - Siddhant Gupta.
//  Place   - Uttar Pradesh, India.
//  Completed On 22/09/2020.

// This PyBasics Library is a simulation of some basic Python and Kotlin functions. (most of them are inspired from Python)
// while implementing them the names were changed a little bit, as some keywords are reserved by C++.
// This Library Uses basic C++ functionality to reduce redundant typing by providing basic #includes
// and Input Output Functionailty


// Features (Funtions) :
// Range()      : provides a vector<double> can be used in range based for loops. with python like Syntax.
// Input()      : provides a single line Input feature returns a string
// Size()       : determine the size of the array, despite wherever used and in whatever context.
// Int()        : converts a string to integer
// Double()     : converts a string to double
// Str()        : converts any valid datatype to a string
// print()      : can print any no. of arguements
// println()    : can print any no. of arguements appends a new line
// Print()      : can print 1D, 2D Arrays and Vectors
// toVec()      : can convert an array to a vector.
// find()       : can find an entity in a collection of same type of entities (raw array or vector)

/**  -- String Manipulation Functions --  **/
// Upper()      : to Upper Case the whole String
// Lower()      : to Lower Case the whole String
// Capitalize() : to Capitalize a String
// Reverse()    : to Reverse a String
// Sort()       : to sort a string
// List()       : to convert a string to vector of characters
// Pad()        : to append a character at start and in the end of a string
// toString()   : to convert 1D array or vector to a string.

/**  -- Mapping Functions --  **/
// Map()        : can Apply any of the String Manipulations on a vector of strings, doesn't return anything
// MapArray()   : can Apply any of the String Manipulations on an Array of Strings, doesn't return anything

// Special Features for more READABILITY
// These are defined using Macros
// Aliased "std::cout<<"    as "say" and "ask"
// Aliased '<< " " <<'      as "with"
// Aliased "std::cin>>"     as "listen"
// Aliased ">>"             as "also"
// Aliased "<<std::endl;"   as "done" and "wrap" while using them no semiclon is required

/* 
Special Python features in C++
	- An overloaded (*) operator for string multiplication.
	- An "In" operator to find a value in a 1D array or vector can 
	  be used directly in an if statement to test presence of a value in its collection list.
*/
/*
Here in this Library there are three types of printers or outputstreams.
1. Print()     // note the Capitalization, This prints Special List DataTypes along with 1D and 2D Arrays
2. print()     // this can handle normal printings for different arguements.
3. println()   // it's a Kotlin like print statement that works like print() but appends a new line.
*/

#ifndef PYBASICS_HPP
#define PYBASICS_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

namespace Py {
// Important Macro
#define Size(x)  (sizeof(x) / sizeof((x)[0]))

// Some for fun Macros
// remember these are strictly optional to use.
// for output 
#define say std::cout<<
#define ask std::cout<<
#define show std::cout<<
#define with << " " <<
#define done <<std::endl;    // while using "done" or "wrap" it's not required to use a semicolon
#define wrap <<std::endl;

// for input
#define listen std::cin>>
#define also >>

// for filestream 
#define read ios::in
#define write ios::out
#define readwrite ios::in|ios::out

/* // For Preprocessors
These are just for fun preprocessors to make code more readable.

					"don't forget the semicolon"

use case: 

				string = name;					// declarations aren't changed
				int num;
you typed:		say "What's your name? " done;
or you typed:   say "What's your name? " wrap;
or you typed:   ask "What's your name? " done;
or you typed:   ask "What's your name? " wrap;
equivalent to:  std::cout << "What's your name? " << std::endl;

you typed:		listen name;
equivalent to:  std::cin >> name;

you typed:      listen name also num;
equivalent to:  std::cin >> name >> num;

you typed:      say "Hi! " with name done;
equivalent to:  std::cout << "Hi! " << name << std::endl;
*/


// =============================================== Functions: =============================================== 


// @brief Since Template Functions create linker issues therfore template type are implemented in .hpp file itself
//#######################################################################################################################
// Number List Generators (Implementation in PyBasics.cpp)
	
	template<typename T>
	vector <T> Range(T begin, T end, T step) {
		vector <T> rangeData;

		for (T i = begin; i < end; i += step) {
			rangeData.push_back(i);
		}

		return rangeData;
	}

	vector <double> Range(double end);
	vector <double> Range(double begin, double end);
	vector <int> Range(int end);
	vector <int> Range(int begin, int end);
//#######################################################################################################################
// Python Type String Multiplier
	string operator* (std::string str, int times); // Implementation in PyBasics.cpp
//#######################################################################################################################
// A Python like finder 
#define In <IN>  // Masking the "<In>" with "In"
/*
Important:
	The "In" operator or find() can take r-value references for int,double, float, long, chars and strings.
	for there matching type lists(array or vector) i.e. "char In char[]" or "char In vector<char>" or
	a "string In string[]" or a "string v vector<string>".

warning: don't use either an r-value or an l-value of intermixed types for "char" and "string".

Prohibited and  are subjected to give compiler errors:
For r-values:
		" 'a' In string[] "
		" 'a' In vector<string> "
		" "a" In char[] "
		" "a" In vector<char> "

For l-values:
	string a = "a";
		" a In char[] "
		" a In vector<char> "
	char ch = 'a';
		" ch In string[] "
		" ch In vector<string>"

//#######################################################################################################################
These functions are created to directly test the presence of an entity of a type  
in a vector or array of ""SAME"" type.

ex:  vector<string> names = {"ferb","phineas","candace","buford"};
	 string name = "candace";
	 if(find(name,names)){
		std::cout<<"Found it!"<<std::endl;
	 }else{
		std::cout<<"Not Found! "<<std::endl;
	 }
output:
	 Found it!

Similar case is there with Arrays.

Note: find() functions can be directly used if needed.

or else the complex but (easy to use) effective functionaility is already implemented down below.
*/

	// for 1D vectors
	template <typename T, typename U>
	bool find (T t, vector<U>& vec) {
		for (U& i : vec) {
			if (t == i) {
				return true;
			}
		}return false;
	}

	// for 1D Arrays
	template <typename T, typename U>
	bool find (U u, T& arr) {
		for (int i = 0; i < Size(arr);i++) {
			if (u == arr[i]) {
				return true;
			}
		}return false;
	}
// refer line no. 115, in the important section.
// =================== Driver Function for the operator "in" (self constructed operator) =================== 

	enum { IN };

	// momentary container for left side.
	template <typename Lhs, typename Operation>
	struct Obj_Container {
		Lhs __lhs;
	};

	// func1
	template<typename Lhs>
	Obj_Container<Lhs, decltype(IN)> operator<(const Lhs __lhs, decltype(IN)) {
		return { __lhs };  // returns an initializer list constructed object for the struct Obj_Container
	}

	// func2
	template<typename Lhs, typename Rhs>
	bool operator>(const Obj_Container<Lhs, decltype(IN)>& obj, Rhs& rhs) {
		return find(obj.__lhs, rhs);
	}
/*
How to use this?
	Ans:
		say you provided a value to find in an array.
		syntax you wrote:

		int array[] = {2,5,1,4,6,8};
		int num = 4;
		
		//and now put this in an if condition
		if(num In array){
			print("found it");
		}else{
			print("not found");
		}

	Output:
		found it

	How it worked?
	Ans:
		"In" as a preprocessor directive translates to <IN>
		now look at the condition in if statement

		num <IN> array

		Break this like this ((num < IN) > array)
		func1 operates on the inner parenthesis ( num < IN ) and returns {num} as an object for Obj_Container.
		(remember {} is a brace-enclosed-initializer-list for constructor of Obj_Container)
		Why func1 operated first?, because func1 has its parameter list as (const T& t, decltype(In))
		which translates to "operate on any kind of datatype, where the operator is < and right hand side is an enum (IN)"

		now the condition in if looks like this ( Obj_Container(Object) > array)

		now this is traced by func2, It operates on this condition and extracts the Obj_Container object's __lhs
		value and puts it along with right hand side value in find() function.

		Why func2 operated on this condition ( Obj_Container(Object) > array)?. because it has its param list as
		(const Obj_Container<Lhs, decltype(IN)>& obj, Rhs& rhs) which translates to "take the Obj_Container object
		on the left hand side extract its member and then put the right hand side value and extracted value in find() function"
*/

//#######################################################################################################################
// TypeCasters
	// Implementation in PyBasics.cpp
	int Int ( string s );
	int Int ( char ch );
	int Int ( double d );
	double Double ( string s );
	double Double (char ch);
	string Str(char ch);
	string Str(char const* str);
	string Str(string& s);  
	// does nothing but prevents Str(T t) from throwing a string to string conversion error

/* 
This Str() function converts any type of default datatype into string.
Note: uses the builtin to_string() function.
*/
	template <typename T>
	string Str ( T t ){
		return to_string(t);
	}

//#######################################################################################################################
// Input
// Implementation in PyBasics.cpp
	string Input ( string s = "" );

//#######################################################################################################################
// Printer
/*
Py namespace provides two type of print functions 
1. print()     // doesn't automatically appends a newline and the 'cout' buffer isn't flushed
2. println()   // does automatically appends a newline and flushes the 'cout' buffer

Note: can be supplied any valid literal value for printing. can also print user defined class objects if the 
class has a an overloaded '<<' operator
*/
	// this namespace is created to handle 4 or more arguements printings
	namespace print_container {

		std::ostream& Show(std::ostream& os); // Implemented in PyBasics.cpp

		template <typename T>
		std::ostream& Show(std::ostream& os, T&& t) {
			return os << std::forward<T>(t);
		}

		template <typename T, typename U, typename... Args>
		std::ostream& Show(std::ostream& os, T&& t, U&& u, Args&&... args) {
			return Show(Show(os, std::forward<T>(t)) << ' ', std::forward<U>(u), std::forward<Args>(args)...);
		}
	}

// These print statements also automatically append a newline but they can be made to not do this, by passing any character at the end of parameters.
/*
These functions are overloaded just to save the usage of namespace print_container.
and to also reduce the overhead recursive calls made for 2 - 3 params.
*/
// print() functions
	// spare print()
	void print();
	// Simple Printer
	template <typename T>
	void print(T &&t, char ch = '\0') {
		if (ch == '\0') {
			say t wrap;
		}
		else {
			say t with ch;
		}
	}

	// Printing Two Different Args
	template <typename T, typename U>
	void print(T &&t, U &&u, char ch = '\0') {
		if (ch == '\0') {
			say t with u wrap;
		}
		else {
			say t with u with ch;
		}
	}
	// Printing 3 different Args
	template <typename T, typename U, typename V>
	void print(T&& t, U&& u, V&& v, char ch = '\0') {
		if (ch == '\0') {
			say t with u with v wrap;
		}
		else {
			say t with u with  v with ch;
		}
	}

	// Printing for more than 3 args
	template <typename... Args>
	void print(Args&&... args) {
		print_container::Show(std::cout, std::forward<Args>(args)...);
	}

// println() functions automatically appending a new line
	// Simple Printer
	template <typename T>
	void println(T&& t) {
		say t wrap;
	}

	// Printing Two Different Args
	template <typename T, typename U>
	void println(T&& t, U&& u) {
		say t with u wrap;
	}

	// Printing 3 different Args
	template <typename T, typename U, typename V>
	void println(T&& t, U&& u, V&& v) {
		say t with u with v wrap;
	}

	// does appends a new line
	// Printing for more than 3 args
	template <typename... Args>
	void println(Args&&... args) {
		print_container::Show(std::cout, std::forward<Args>(args)...) done; // #define done <<std::endl;
	}

//#######################################################################################################################
// Special DataType Printers should be called with Print(), note the Capitalization
// Vector Printers
// 1D vector Printers
/*
Seperator can be provided as a second param to defer between two iterations.
By default separator is " " or a single whitespace.
*/
	// These are overloaded with default types just to save the overhead of deducing the type.
	void Print (vector <string> &vec, string end = " ");  // Implemented in PyBasics.cpp
	void Print (vector <int> &vec, string end = " ");     // Implemented in PyBasics.cpp


	// This overloaded Print() function prints a vector of any type.
	template <typename T>
	void Print ( vector <T> &vec, string end = " " ) {
		for (T& i : vec) {
			say i with end;
		} say "" done;
	}

	// This Overloaded Function Handles Printing of a vector returned by a function. range() or Map().
	template <typename T>
	void Print (const vector <T> &vec, string end = " " ) {
		for (const T& i : vec) {
			say i with end;
		} say "" done;
	}

//#######################################################################################################################
// 2D vector Printer
/*
Seperator can be provided as a second param to defer between two iterations.
By default separator is "\t" or a tab.
*/
	template <typename T>
	void Print (vector <vector <T>> &vec, string end = "\t") {
		for (int i = 0; i < vec.size(); i++ ) {
			for (int j = 0; j < vec[i].size(); j++) {
				say vec[i][j] with end;
			} say "" done;
		}
	}

//#######################################################################################################################
// Array Printer
// 1D Array
/*
Seperator can be provided as a second param to defer between two iterations.
By default separator is " " or a single whitespace.

Note: This function doesn't require you to provide the size of the array.
*/
	template <typename T>
	void Print ( T &arr, string end = " ") {
		for (int i = 0; i < Size(arr); i++) {
			say arr[i] with end;
		} say "" done;
	}

//#######################################################################################################################
// 2D Array Printer
/*
Seperator can be provided as a 'third' param to defer between two iterations.
By default separator is " " or a single whitespace.

Note: This function 'does' require you to provide the size of the array.
	  but you can use the Py::Size() function in its calling.

ex: Print(arr,Py::Size(arr),"\t") // assume arr is a 2D Array of any default cpp datatype
*/
	template <typename T>
	void Print ( T &arr, size_t size, string end = "\t" ) {
		for (size_t i = 0; i < Size(arr); i++) {
			Print (arr[i], end);
		}
	}

//#######################################################################################################################
// basic utility function. IDK if it turns out to be useful.
	template<typename T>
	void swap(T& a, T& b) {
		T temp;
		temp = a;
		a = b;
		b = temp;
	}

	// You Already know what are these :)
	template<typename T>
	double Sum(T& arr) {
		double sum = 0;
		for (size_t i = 0; i < Size(arr); i++) {
			sum += arr[i];
		}
		return sum;
	}

	template<typename T>
	T Sum(const vector<T>& vec) {
		T sum = 0;
		for (const T& t : vec) {
			sum += t;
		}
		return sum;
	}

	template<typename T>
	T Sum(vector<T>& vec) {
		T sum = 0;
		for (T& t : vec) {
			sum += t;
		}
		return sum;
	}

//#######################################################################################################################
// String manipulation Functions (Implemented in PyBasics.cpp)
	// l-value optimization
	// can be used with Map()
	string Upper (string &s);
	string Lower (string &s);
	string Capitalize (string &s);
	string Reverse (string &s);
	string Sort (string& s);

	// for r-value optimization
	string Upper(string&& s);
	string Lower(string&& s);
	string Capitalize(string&& s);
	string Reverse(string&& s);
	string Sort (string&& s);

	// python type string manipulators
	vector<char> List(string s);
	vector<string> Split(string str, char separator = ' ');

	// Cannot be used with map()
	string Pad(string s,string ch = " ");  // adds padding to the string on the terminal positions
	string Pad(char const* str, string ch = " ");
	string Pad(char str, string ch = " ");

//#######################################################################################################################
// Mapping Functions (Implemented in PyBasics.cpp)
/*
This Map() function takes a function as first param and a vector as second param.

ex: Map(Upper, names);  // assume names as a 1D vector<string>
	now the Map() function will apply the Upper() function on all the elements of vector by-reference.
	it supports all the functions that are implemented in the string manipulation section. (Just above this Section)
*/
	void Map (string (*f) (string&), vector <string> &vec);

/*
Note: These cannot modify the vector by-reference as implicit/explicit type transformation is not allowed in C++
*/
	// overloaded for Int()
	vector<int> Map(int (*f) (string), vector <string>& vec);         // returns a vector<int>
	vector<int> Map(int (*f) (string),const vector <string>& vec);    // for compatibility with Split function
	vector<int> Map(int (*f) (string), const vector <char>& vec);     // for compatibility with List function
	// overloaded for Double()
	vector<double> Map(double (*f) (string), vector <string>& vec);         // returns a vector<double>
	vector<double> Map(double (*f) (string),const vector <string>& vec);    // for compatibility with split function
	vector<double> Map(double (*f) (string), const vector <char>& vec);     // for compatibility with List function

	// This Map() Function is overloaded specifically for Str() function.
	// This converts the values of one vector into string and returns the copy of the new vector.
	template<typename T>
	vector<string> Map ( string (*f) (T), vector<T> &vec) {
		vector<string> temp;

		for (T i : vec) {
			temp.push_back ( (*f) (i) );
		}

		return temp;
	}

	// This overloaded copy of Map function Lets you Chain it with List()
	template<typename T>
	vector<string> Map(string(*f) (T),const vector<T>& vec) {
		vector<string> temp;

		for (T i : vec) {
			temp.push_back((*f) (i));
		}

		return temp;
	}

//#######################################################################################################################
// Array of String Mapper
/*
This MapArray() function specifically works only for string array.
It Maps the String Manipulation Functions by-reference on the array.

Note: Doesn't return anything.
*/
	template<typename T>
	void MapArray ( string (*f) (string&), T &arr) {
		for (size_t i = 0; i < Size (arr); i++ ) {
			(* (arr + i) ) = (*f) (* (arr + i) );
		}
	}
/*
It is a peculiar process of returning an array from a function. since in C++ an Array decays to a pointer when 
passed to a function. Its a good challenge to Implement those. 

Therefore MapArray function isn't overloaded for Int(), Double() and Str() functions.

edited: Tried it, didn't go well. Plus it can also create an overhead on the user of this library.
*/

//#######################################################################################################################
// Array to Vector Function
/**
@brief  This toVec() function though declared as template,
		it requires you to provide similar type of array and vector in case of strings

		the below representation shows the compatibility of conversion from arr to vec, Lossy conversions might occur if handled carelessely

@param  arr -> {int}                       | {double}                    | {long}                      | {float}                     | {string}
@param  vec -> {int, double ,long , float} | {int, double ,long , float} | {int, double ,long , float} | {int, double ,long , float} | {string}
	
		Also for Better string manipulation there is a Map function.

@return returns the vector after copying all the values in it by reference from the array provided as param.
*/
	template<typename T, typename U>
	void toVec (T& arr, vector<U> &vec) {
		for (size_t i = 0; i < Size(arr); i++ ) {
			vec.push_back (arr[i]);
		}
	}

//#######################################################################################################################
// Kotlin Type toString() functions.
/*
These functions can convert a 1D Array or Vector to string.
*/
	template<typename T>
	string toString(vector<T>& vec) {
		string s = "<";
		for (size_t i = 0; i < vec.size(); i++) {
			s = s + Pad(Str(vec.at(i)));
		}s = s + ">";
		return s;
	}

	template<typename T>
	string toString(const vector<T>& vec) {
		string s = "<";
		for (size_t i = 0; i < vec.size(); i++) {
			s = s + Pad(Str(vec.at(i)));
		}s = s + ">";
		return s;
	}

	template<typename T>
	string toString(T& arr) {
		string s = "[";
		for (size_t i = 0; i < Size(arr); i++) {
			s = s + Pad(Str(arr[i]));
		}s = s + "]";
		return s;
	}
// The End 
}

#endif // PYTESTFILE_HPP