//  Author  - Siddhant Gupta.
//  Place   - Uttar Pradesh, India.
//  Completed On 22/09/2020.

// This PyBasics Library is a simulation of some basic Python functions.
// while implementing them the names were changed a little bit, as some keywords are reserved by C++.
// This Library Uses basic C++ functionality to reduce redundant typing by providing basic #includes
// and Input Output Functionailty

/*
Features (Classes):
	- A Special File Handling Class is also provided to handle basic File opening processes in 1-2 lines of code.
	  Documentation in PyBasics.cpp

	- A Special Array Class. Array class implements array's in different form. other than std::array's but similar to std::vector
	  but different from std::vector, Array class has a lot more features built-in [read internal documentation]
	  It doesn't require size as a parameter. but it has a limitation, it's size is defaulted to INT32_MAX elements.
	  It can be changed by the programmer by changing the MAX_ARRAY_CAPACITY.
*/
/*
Features (Namespaces):

	- This Library has two namespaces that are ____internal_print____ and ____to_string____
		> these handle operations/workings for print() and Str() so they need not be used outside this library.

*/
/*
Features (Funtions):
// Range()      : provides a vector<double> can be used in range based for loops. with python like Syntax.
// Input()      : provides a single line Input feature returns a string
// Size()       : determine the size of the array, despite wherever used and in whatever context.
// Int()        : converts a string to integer
// Double()     : converts a string to double
// Str()        : converts any valid datatype to a string
// print()      : can print any no. of arguements
// Print()      : can print 1D, 2D Arrays and Vectors
// find()       : can find an entity in a collection of same type of entities (raw array or vector)

Features (Functors):
	toVec()      : can convert an Array Class object to a vector.
	toArr()		 : can convert a vector to an Array Class object
- good thing about this functor approach is that it can implement a help feature that is solely for the object it is a part of
*/
/**  -- String Manipulation Functions --  **//*
	* Upper()						: to Upper Case the whole String
	* Lower()						: to Lower Case the whole String
	* Capitalize()					: to Capitalize a String
	* Reverse()						: to Reverse a String
	* Sort()						: to sort a string
	* List()						: to convert a string to vector of characters
	* Title()						: to make the text 'Title'
	* Replace()						: to remove a replace a part of a string with another
	* Trim()						: trims blank spaces at extreme ends
	* RemoveRedundantSpaces()		: Reduces numerous unnecessary spaces to one
	* ReformatText()				: Reformats the text [read internal documentation]
	* Pad()							: to append a character at start and in the end of a string
*/
/**  -- Mapping Functions --  **/
// Map()        : can Apply any of the String Manipulations on a vector and Array Class objects of strings.
// MapArray()   : can Apply any of the String Manipulations on an raw-array of Strings, doesn't return anything

/* 
Special Features for more READABILITY
These are defined using Macros
	* Aliased "std::cout<<"    as "say" and "ask"
	* Aliased '<< " " <<'      as "with"
	* Aliased "std::cin>>"     as "listen"
	* Aliased ">>"             as "also"
	* Aliased "<<std::endl;"   as "done" and "wrap" while using them no semiclon is required
*/
/*
Special Python features in C++
	- An overloaded (*) operator for string multiplication.
	- An "In" operator to find a value in a 1D array or vector can
	  be used directly in an if statement to test presence of a value in its collection list.

Here in this Library there are two types of printers or outputstreams.
1. Print()     // note the Capitalization, This prints Special List DataTypes along with 1D and 2D Arrays
2. print()     // this can handle normal printings for different arguements.
*/
/*
	In Order to use everything this library has to offer use 
	#include "PyBasics.h"
	using namespace Py;
*/
#ifndef PYBASICS_H
#define PYBASICS_H

#include <cassert>
#include <cctype>
#include <cmath>
#include <ctime>
#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Arrays.h"

using namespace std;

namespace Py {
// Important Macro
#define Size(x) (sizeof(x) / sizeof((x)[0]))
// Some for fun Macros
// remember these are strictly optional to use.
// for output 
#define say std::cout<<
#define ask std::cout<<
#define with << " " <<
#define done <<std::endl;    // while using "done" or "wrap" it's not required to use a semicolon
#define wrap <<std::endl;

// for input
#define listen std::cin>>
#define also >>

// some shortcuts for 'for' loops
// normal for loop with iterator i = int
#define fr(begin, end, step) for (int i = begin; i < end; i += step)
// normal for loop iterator i = double
#define frd(begin, end, step) for (double i = begin; i < end; i += step)
// reverse for loop with iterator i
#define frr(end, begin, step) for (int i = end - 1; i >= begin; i--)
// for nesting 
#define fri(begin, end, step) for (int i = begin; i < end; i += step)
#define frj(begin, end, step) for (int j = begin; j < end; j += step)

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

you typed:      say "Hi!" with name done;
equivalent to:  std::cout << "Hi! " << name << std::endl;
*/

//#######################################################################################################################
	// some functions for 'int' datatype with there definition stored in PyBasics.cpp

	Array<int>& make_increasing_range(Array<int>& arr, int begin, int end, int increment);
	Array<int>& make_decreasing_range(Array<int>& arr, int begin, int end, int decrement);
	Array<int>& make_random_range(Array<int>& arr, int len);

//#######################################################################################################################

// =============================================== File Handler Class: ================================================== 
/*
	These are file opening modesthat File class requires you to pass as a parameter.
	The names suggest waht they do.
*/
	enum File_Open_Modes {
		READ, WRITE, READ_AND_WRITE, APPEND, READ_AND_TRUNCATE, READ_AND_APPEND, BINARY
	};

/**
	This class is a wrapper class around the fstream library.
	it handles the actual procedures of maintain a file basics like opening in a particualr mode.
	closing when the task is done.

	* overlapping one file on another (if you open another file while a file is already open
	  the new one will not open, but this has been take care of in this class. It will close
	  the old file and open the new one. Note: it opens the new file in the mode of the previous file.)

	* supports momentary opening of files and their closing. if single line tasks needs to be performed
	  like if you want to open a file and show its content in a for-loop. this can be achieved in a sinle line

	  ex:
		if iam having 4 testfiles only differed by ther no. as:
		testfile0.txt
		testfile1.txt
		testfile2.txt
		testfile3.txt
		a name you can create. or if you can make a vector of filenames.
		you can access them as shown below:

		File file;
		for(int i = 0; i <= 3; i++){
			file.open("testfile"+Str(i)+".txt",'r').showfile();
		}

		for (int i = 0; i <= 3; i++) {
			File("testfile"+Str(i)+".txt",'r').showfile();
		}
		// all the basic procedures will be handled behind the scenes and you get to focus on important details.

	* even_indice_val you can collect the data of all files in your data base in one go by using a vector<string>
	  and load the files like the previous ex. and replace showfile() with readfile().

	* This class is Compatible with the Map() function.

*/
	class File {
		fstream file;
		string name;
		File_Open_Modes mode;
		bool openSuccess;
		void modeSwitcher(string, File_Open_Modes);
		string eol = "__END_OF_LINE__";
	public:
		File() = default;
		File(string name, File_Open_Modes mode = READ);

		File(const File&);
		
		// resets cursor
		void reset_cursor();
		// opens a new file in the same object
		void open_new_file(string name, File_Open_Modes mode);
		
		// Opens a File for momentary operations.
		// Returns the File so that it can be chained with readfile(), readline() or showfile()
		File open(string name, File_Open_Modes mode);

		// closes the file
		void close();
		// shows the file
		void showfile();
		
		/*
			How to use this overload of readline() to access the file line by line.
			ex:

			File file = File{ "<filename>.<filetype>",'r' };
			string line = "";
			while (line = file.readline(), line != file.EOL()) {
				// Do something with the "line"
			}
		*/
		string readline();

		/*
			How to use this overload of readline() to access the file line by line.
			ex:

			File file = File{ "<filename>.<filetype>",'r' };
			string line = "";
			while (file.readline(line)) {
				// Do something with the "line"
			}
		*/
		bool readline(string& line);

		/* Designated to read the entire file. */
		string readfile();

		void help();

		// To check if the file is open using if condition
		operator bool() {
			return openSuccess;
		}

		// writing to file
		template<typename T>
		void writeline(T t) {
			if (mode != READ)
				file << t << "\n";
			else
				cerr << "Error: wrong mode selected to write file";
		}

		// returns 
		string EOL() { return eol; }
		~File();
	};

//#######################################################################################################################
// ================================================== Functions: ======================================================== 

// @brief Since Template Functions create linker issues therfore template type are implemented in .h file itself
//#######################################################################################################################
// Number List Generators (Implementation in PyBasics.cpp)

	template<typename T>
	vector <T> Range(T begin, T end, T step) {
		vector <T> _range_data;

		// this is being done to detect invalid params that produce infinitesimal range
		bool _flag = false;
		clock_t _time_begin = clock();
		clock_t _time_end = clock() + 4000;
		// this will take a second to detect if the params are invalid
		/*
		this function can provide a maximum range of 15.34 Million elements
		if you want bigger ranges please consider your own loops.
		*/
		if (end > begin) {
			for (T i = begin; i < end; i += step) {
				_time_begin = clock();
				if (_time_begin <= _time_end) {
					_range_data.push_back(i);
				}
				else {
					_flag = true;
					break;
				}
			}
		}
		else {
			for (T i = begin; i > end; i += step) {
				_time_begin = clock();
				if (_time_begin <= _time_end) {
					_range_data.push_back(i);
				}
				else {
					_flag = true;
					break;
				}
			}
		}
		if (_flag) {
			_range_data.clear();
		}

		return _range_data;
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


	bool find(string l, string r);		// Implementation in PyBasics.cpp
	bool find(char const* l, string r);	// Implementation in PyBasics.cpp
	bool find(char const* l, char const* r);
	bool find(char l, char const* r);
	
	// Linear Search 
	// for 1D vectors
	template <typename T, typename U>
	bool find(T t, vector<U>& vec) noexcept {
		for (U& i : vec) {
			if (t == i) {
				return true;
			}
		}return false;
	}

	// for built-in functions that return a vector
	template <typename T, typename U>
	bool find(T t, const vector<U>& vec) noexcept {
		for (const U& i : vec) {
			if (t == i) {
				return true;
			}
		}return false;
	}

	// for 1D Arrays
	template <typename U,class _Ty, size_t _Size>
	bool find(U u, _Ty(&_Array)[_Size]) noexcept {
		for (int i = 0; i < _Size; i++) {
			if (u == _Array[i]) {
				return true;
			}
		}return false;
	}

	// exclusive to Array Class objects this find() uses internal binary_search
	template <typename T, typename U>
	bool find(U u, Array<T>& arr) noexcept {
		return arr.binary_search(u);
	}

	template <typename T, typename U>
	bool find(U u, const Array<T>& ar) noexcept {
		Array<T> arr = ar;
		return arr.binary_search(u);
	}

// ======================= Driver Code for the operator "In" (self constructed operator) ======================= 

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

	template<typename Lhs, typename Rhs>
	bool operator>(const Obj_Container<Lhs, decltype(IN)>& obj, const Rhs& rhs) {
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
/*
	These functions can convert a 1D Raw - Array, Array Class objects and Vector to string. Provides extra parameters and mods.
*/
	namespace  ____to_string____ {
		string ___notation_braces___(string s, char symbol_left, char symbol_right);
		string ___padder___(string s);

		template<typename T>
		string ____str____(vector<T> vec, bool padding = true, bool notation_braces = true) {
			string s;

			for (T v : vec) {
				if (padding) {
					s += ___padder___(to_string(v));
				}
				else {
					s += to_string(v);
				}
			}

			if (notation_braces) {
				s = ___notation_braces___(s, '<', '>');
			}

			return s;
		}

		template<typename T>
		string ____str____(Array<T> arr, bool padding = true, bool notation_braces = true) {
			string s;

			for (size_t i = 0; i < arr.size(); i++) {
				if (padding) {
					s += ___padder___(to_string(arr[i]));
				}
				else {
					s += to_string(arr[i]);
				}
			}

			if (notation_braces) {
				s = ___notation_braces___(s, '[', ']');
			}

			return s;
		}
	}

	template<typename T>
	string Str(Array<T>& arr, bool padding = true, bool notation_braces = true) {
		return ____to_string____::____str____(arr, padding, notation_braces);
	}

	template<typename T>
	string Str(vector<T>& vec, bool padding = true, bool notation_braces = true) {
		return ____to_string____::____str____(vec, padding, notation_braces);
	}

	template<typename T>
	string Str(Array<T>&& arr, bool padding = true, bool notation_braces = true) {
		return ____to_string____::____str____(arr, padding, notation_braces);
	}

	template<typename T>
	string Str(vector<T>&& vec, bool padding = true, bool notation_braces = true) {
		return ____to_string____::____str____(vec, padding, notation_braces);
	}

//#######################################################################################################################
// TypeCasters	Implemented in PyBasics.cpp
	int Int(string s);
	int Int(char ch);
	int Int(double d);
	
	double Double(string s);

	string Str(char ch);
	string Str(char const* str);	// for Exception Safety
	string Str(string& s);			// does nothing but prevents Str(T t) from throwing a string to string conversion error

/*
This Str() function converts any type of default datatype into string.
Note: uses the builtin to_string() function.
*/
	template <typename T> string Str(T t) {return to_string(t);}

/* This Str() function converts any type of default datatype raw - array into string. */
	template <class _Ty, size_t _Size>
	string Str(_Ty(&_Array)[_Size]) noexcept {
		string s = "[";
		int i = 0;
		for (; i < _Size - 1; i++) {
			s += ' ' + to_string(_Array[i]) + ',';
		}
		s += " " + to_string(_Array[i]) + " ]";
		return s;
	}

//#######################################################################################################################
/**
	Single Line Input function. Can be used hand in hand with the Typecasters,
	for Integer or Double Value inputs.

	ex: int i = Int(Input("Enter an Integer.: "));
		double d = Double(Input("Enter a Float/Double.: "));
*/
	string Input(string s = "");

//#######################################################################################################################
// Overloaded for including vector printing along with other arguements in print();
	template<typename T>
	ostream& operator<< (ostream& os, vector<T>& vec) {
		size_t i = 0;
		os << '<';
		if (vec.size() >= 1) {
			for (; i < vec.size() - 1; i++) { os << vec[i] << ", "; }
			os << vec[i];
		}
		return os << '>';
	}

	template<typename T>
	ostream& operator<< (ostream& os, const vector<T>& vec) {
		size_t i = 0;
		os << '<';
		if (vec.size() >= 1) {
			for (; i < vec.size() - 1; i++) { os << vec[i] << ", "; }
			os << vec[i];
		}
		return os << '>';
	}

	// for concatention of two vectors
	template<typename T>
	vector<T> operator+(vector<T> lhs, vector<T> rhs) {
		for (T& t : rhs) {lhs.push_back(t);}
		return lhs;
	}

// Since the Deque is already included i thought might as well implement global operator<< to be used in print function
	
	template<typename T>
	ostream& operator<< (ostream& os, deque<T>& deq) {
		size_t i = 0;
		os << '<';
		if (deq.size() >= 1) {
			for (; i < deq.size() - 1; i++) { os << deq[i] << ", "; }
			os << deq[i];
		}
		return os << '>';
	}

	template<typename T>
	ostream& operator<< (ostream& os,const deque<T>& deq) {
		size_t i = 0;
		os << '<';
		if (deq.size() >= 1) {
			for (; i < deq.size() - 1; i++) { os << deq[i] << ", "; }
			os << deq[i];
		}
		return os << '>';
	}

//#######################################################################################################################
// Printer
/*
	Py namespace provides a print function
	print()

	Note: can be supplied any valid literal value for printing. can also print user defined class objects if the
	class has a an overloaded '<<' operator
*/
	// this namespace is created to handle 4 or more arguements printings
	namespace ____internal_print____ {

		std::ostream& ___show___(std::ostream& os); // Implemented in PyBasics.cpp

		template <typename T>
		std::ostream& ___show___(std::ostream& os, T&& t) {
			return os << std::forward<T>(t);
		}

		template <typename T, typename U, typename... Args>
		std::ostream& ___show___(std::ostream& os, T&& t, U&& u, Args&&... args) {
			return ___show___(___show___(os, std::forward<T>(t)) << ' ', std::forward<U>(u), std::forward<Args>(args)...);
		}
	}

// These print statements also automatically append a newline but they can be made to not do this, by passing any character at the end of parameters.
/*
	- These functions are overloaded just to save the usage of namespace print_container.
	  and to also reduce the overhead recursive calls made for 2 - 3 params.
	- this print function is similar to python print(*args,end="") the end arguement is a character
	- if the character is passed then the print function doesn't put an endl at the end

*/
// print() functions
	// spare print()
	void print();

	// Simple Printer
	template <typename T>
	void print(T&& t, char ch = '\000') {
		if (ch == '\000') {say t wrap;}
		else {say t with ch;}
	}

	// Printing Two Different Args
	template <typename T, typename U>
	void print(T&& t, U&& u, char ch = '\000') {
		if (ch == '\000') {say t with u wrap;}
		else {say t with u with ch;}
	}

	// Printing 3 different Args
	template <typename T, typename U, typename V>
	void print(T&& t, U&& u, V&& v, char ch = '\000') {
		if (ch == '\000') {say t with u with v wrap;}
		else {say t with u with  v with ch;}
	}

	void print(const char* s);

	// prints 1D Array
	template <class _Ty, size_t _Size>
	void print(_Ty(&_Array)[_Size]) noexcept {
		cout << '[';
		int i = 0;
		for (; i < _Size - 1; i++) {cout << _Array[i] << ", ";}
		cout << _Array[i] << ']';
	}

	// prints 2D Array
	template <class _Ty, size_t _Size>
	void print(_Ty(&_Array)[_Size][_Size]) noexcept {
		int i = 0;
		for (; i < _Size; i++) {
			print(_Array[i]);
			cout << endl;
		}
	}

	// Printing for more than 3 args
	template <typename... Args>
	void print(Args&&... args) {
		____internal_print____::___show___(std::cout, std::forward<Args>(args)...);
	}

//#######################################################################################################################
// Special DataType Printers should be called with Print(), note the Capitalization
// Vector and Array Class objects Printers
// 1D vector Printers
/*
	Seperator can be provided as a second param to defer between two iterations.
	By default separator is " " or a single whitespace.
*/

	// This overloaded Print() function prints a vector of any type.
	template <typename T>
	void Print(vector<T>& vec, string end = " ") {
		for (const T& i : vec) {
			say i << end;
		} say "" done;
	}

	// This Overloaded Function Handles Printing of a vector returned by a function. range() or Map().
	template <typename T>
	void Print(const vector<T>& vec, string end = " ") {
		for (const T& i : vec) {
			say i << end;
		} say "" done;
	}

/* For 1D Array Class Objects */

	template <typename T>
	void Print(Array<T>& arr, string end = " ") {
		for (const T& i : arr) {
			say i << end;
		} say "" done;
	}

	// This Overloaded Function Handles Printing of a vector returned by a function like Map() or SplitInArray().
	template <typename T>
	void Print(const Array<T>& arr, string end = " ") {
		for (const T& t : arr) {
			cout << t << end;
		}
		cout << endl;
	}

//#######################################################################################################################
// 2D Printer Vector and Array Class objects
/*
	Seperator can be provided as a second param to defer between two iterations.
	By default separator is "\t" or a tab.
*/
	template <typename T>
	void Print(vector<vector<T>>& vec, string end = "\t") {
		for (size_t i = 0; i < vec.size(); i++) {
			for (size_t j = 0; j < vec[i].size(); j++) {
				say vec[i][j] << end;
			} say "" done;
		}
	}

	// for r-value of 2D vector
	template <typename T>
	void Print(const vector<vector<T>>& vec, string end = "\t") {
		for (size_t i = 0; i < vec.size(); i++) {
			for (size_t j = 0; j < vec[i].size(); j++) {
				say vec[i][j] << end;
			} say "" done;
		}
	}

	template <typename T>
	void Print(Array<Array<T>>& arr, string end = "\t") {
		for (const Array<T>& ar: arr) {
			for (const T& t : ar) {
				say t << end;
			}say "" done;
		}
	}

	// for r-value of 2D Array Class Object
	template <typename T>
	void Print(const Array<Array<T>>& arr, string end = "\t") {
		for (const Array<T>& ar : arr) {
			for (const T& t : ar) {
				say t << end;
			}say "" done;
		}
	}

//#######################################################################################################################
// 1D Raw - Array Printer
	template <class _Ty, size_t _Size>
	void Print(_Ty(&_Array)[_Size], string end = " ") {
		for (int i = 0; i < _Size; i++) {
			say _Array[i] << end;
		} say "" done;
	}

//#######################################################################################################################
// 2D Raw - Array Printer
	template <class _Ty, size_t _Size>
	void Print(_Ty(&_Array)[_Size][_Size], string end = "\t") {
		for (size_t i = 0; i < _Size; i++) {
			Print(_Array[i], end);
		}
	}

//#######################################################################################################################
// basic utility function. IDK if it turns out to be useful.
// You Already know what are these :)

	template<typename T>
	void Swap(T& a, T& b) {
		T temp = a;
		a = b;
		b = temp;
	}

	// Sums a 1D Raw-Array
	template<typename T, size_t s>
	double Sum(T (&arr)[s]) {
		double sum = 0;
		for (size_t i = 0; i < s; i++) {
			sum += arr[i];
		}
		return sum;
	}

	template<typename T>
	T Sum(vector<T> vec) {
		T sum = 0;
		for (T& t : vec) {
			sum += t;
		}
		return sum;
	}

	template<typename T>
	double Sum(Array<T> arr) {
		double sum = 0;
		for (size_t i = 0; i < arr.size(); i++)
			sum += arr[i];
		return sum;
	}

	string Sum(vector<string> vec);
	string Sum(Array<string> arr);

	template<typename T>
	T Max(T a, T b) {
		if (a > b) {
			return a;
		}return b;
	}

	template<typename T>
	T Min(T a, T b) {
		if (a < b) {
			return a;
		}return b;
	}

	template<typename T>
	T Max(vector<T> vec) {
		T temp = vec[0];
		int size = vec.size();
		for (int i = 0; i < size; ++i) {
			if (vec[i] > temp) {
				temp = vec[i];
			}
		}
		return temp;
	}

	template<typename T>
	T Min(vector<T> vec) {
		T temp = vec[0];
		int size = vec.size();
		for (int i = 0; i < size; ++i) {
			if (vec[i] < temp) {
				temp = vec[i];
			}
		}
		return temp;
	}

//#######################################################################################################################
// Quick Sort Algorithm Implementation
	// Sorts in: O(nlog(n)) Time
	template<typename T>
	Array<T> quickSort(Array<T> arr) {
		int size = arr.size();
		if (size < 32) {
			// bubble sort optimization
			arr.sort();
			return arr;
		}
		else {
			T pivot = arr[size / 2];
			Array<T> left;
			Array<T> middle;
			Array<T> right;
			for (size_t i = 0; i < size; i++) {
				if (arr[i] < pivot) {
					left += arr[i];
				}
				else if (arr[i] == pivot) {
					middle += arr[i];
				}
				else {
					right += arr[i];
				}
			}
			return quickSort(left) + middle + quickSort(right);
		}
	}

	// Sorts in: O(nlog(n)) Time
	string quickSort(string s);

	// Sorts in: O(nlog(n)) Time
	template<typename T>
	vector<T> quickSort(vector<T> vec) {
		int size = vec.size();
		if (size < 32) {
			// bubble sort optimization
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size - 1; j++) {
					if (vec[j] >= vec[j + 1]) {
						Swap(vec[j], vec[j + 1]);
					}
				}
			}
			return vec;
		}
		else {
			T pivot = vec[size / 2];
			vector<T> left;
			vector<T> mid;
			vector<T> right;
			for (int i = 0; i < size; i++) {
				if (vec[i] < pivot) {
					left.push_back(vec[i]);
				}
				else if (vec[i] == pivot) {
					mid.push_back(vec[i]);
				}
				else {
					right.push_back(vec[i]);
				}
			}
			// uses operator+ for vectors declared above in this file
			return quickSort(left) + mid + quickSort(right);
		}
	}

//#######################################################################################################################
// Sorting Functions (Basic Bubble Sorting) only for vectors
	// For 1D vectors
	// Sorts in: O(n^2) Time
	template <typename T>
	vector<T> Sort(vector<T>& vec) {
		for (size_t i = 0; i < vec.size(); i++) {
			for (size_t j = 0; j < vec.size() - 1; j++) {
				if (vec[j] >= vec[j + 1]) {
					Swap(vec[j], vec[j + 1]);
				}
			}
		}
		return vec;
	}

	template <typename T>
	vector<T> Sort(vector<T>&& v) {return Sort(v);}

	// for 1D Array Class Objects
	// Sorts in: O(n^2) Time for arr.size() <= 200
	template <typename T>
	Array<T> Sort(Array<T>& arr) {return arr.sort();}

	template <typename T>
	Array<T> Sort(Array<T>&& arr) {return arr.sort();}

//#######################################################################################################################
// String manipulation Functions (Implemented in PyBasics.cpp)
	// can be used with Map()
	// l-value optimization
	string Upper(string& s);
	string Lower(string& s);
	string Capitalize(string& s);
	string HapHazard(string& s);
	string Reverse(string& s);
	string Sort(string& s);
	string Title(string& s);
	string Trim(string& s);
	string RemoveRedundantSpaces(string& s);
	string ReformatText(string& s);

	// for r-value optimization
	string Upper(string&& s);
	string Lower(string&& s);
	string Capitalize(string&& s);
	string Reverse(string&& s);
	string Sort(string&& s);	// String overload for Sort functions
	string Title(string&& s);
	string Trim(string&& s);
	string RemoveRedundantSpaces(string&& s);
	string ReformatText(string&& s);

	// python type string manipulators
	vector<char> MakeList(string s);							 // converts a string into a vector of characters
	string Replace(string& Str, string Old, string New);
	vector<string> Split(string str, char separator = ' ', bool considerSpacesToo = true);	 // converts a string into vector of strings based on the separator provided 
	vector<string> Split(string s, string separator);

	Array<string> SplitInArray(string str, char separator = ' ', bool considerSpacesToo = true);
	Array<int> FindAll(string& str, string s);

	// Cannot be used with map()
	int Count(string s, char ch);
	string Pad(string s, string ch = " ");					// adds padding to the string on the terminal positions
	string Pad(char const* str, string ch = " ");
	string Pad(char str, string ch = " ");

//######################################################################################################################
// vector and Array manipulation functions
/*
Merge Function Assumes that the passed container is sorted
*/
	// merging of two sorted vectors
	template<typename T>
	vector<T> Merge(vector<T> v1, vector<T> v2) {
		int size_1 = v1.size(), size_2 = v2.size();
		int i = 0, j = 0, k = 0;
		vector<T> c(size_1 + size_2);
		while (i < size_1 and j < size_2) {
			if (v1[i] < v2[j]) {
				c[k++] = v1[i++];
			}
			else {
				c[k++] = v2[j++];
			}
		}

		for (; i < size_1; i++) {
			c[k++] = v1[i];
		}

		for (; j < size_2; j++) {
			c[k++] = v2[j];
		}

		return c;
	}

	// merging of two sorted Array Class Objects
	template<typename T>
	Array<T> Merge(Array<T> a1, Array<T> a2) {
		int size_1 = a1.size(), size_2 = a2.size();
		int i = 0, j = 0, k = 0;
		Array<T> c(size_1 + size_2);
		while (i < size_1 and j < size_2) {
			if (a1[i] < a2[j]) {
				c[k++] = a1[i++];
			}
			else {
				c[k++] = a2[j++];
			}
		}

		for (; i < size_1; i++) {
			c[k++] = a1[i];
		}

		for (; j < size_2; j++) {
			c[k++] = a2[j];
		}

		return c;
	}

	// Guesses the Pattern of the AP and returns all the missing element
	template<typename T>
	vector<T> missing_elements_of_an_AP(vector<T> vec) {

		T a = vec[0], l = vec[vec.size() - 1];
		int n = vec.size();
		vector<T> missing_elem;

		T d = INT32_MAX;
		for (int i = 1; i < n; i++) {
			if ((vec[i] - vec[i - 1]) < d) {
				d = vec[i] - vec[i - 1];
			}
		}

		T _a = a;
		for (int i = 0; i < n;) {
			if (_a == vec[i]) { i++; }
			else { missing_elem.push_back(_a); }
			_a += d;
		}

		return missing_elem;
	}

	// returns a vector of duplicate elements in the parameter vector
	/*
	* Anyways I have figured it out either the duplicate 
	  removal can be done in O(nlog(n)) time at its best. 
	* but the order is lost and the thing gets sorted.
	template<typename T>
	vector<T> RemoveDuplicates(vector<T> vec) {
		vector<T> dup_cont;
		sort(vec.begin(), vec.end());

		size_t temp_size = 0;
		T prev_elem = vec[0];
		dup_cont.push_back(prev_elem);
		for (size_t i = 0; i < vec.size(); i++) {
			if (vec[i] != prev_elem) {
				dup_cont.push_back(vec[i]);
				temp_size++;
				prev_elem = vec[i];
			}
		}

		return dup_cont;
	}
	*/

	/*
	This Implementation keeps the order intact and uses a register to hold the 
	information of the elements. 
	vector:   <1, 4, 2, 5, 4, 2, 5, 3, 6, 4, 5, 3, 2, 4, 6>
	register: <0, 0, 0, 0, 1, 1, 1, 0, 0, 2, 2, 1, 2, 3, 1>
	whichever element will have the register as 0 will be preserved
	output:   <1, 4, 2, 5, 3, 6>
	Removal process is linear.
	*/
	template<typename T>
	vector<T> RemoveDuplicates(vector<T>& vec) {
		int size = vec.size();
		int* _register = new int[size]{0};

		for (int i = 0; i < size; i++) {
			T temp = vec[i];
			for (int j = i + 1; j < size; j++) {
				if (temp == vec[j]) {
					_register[j]++;
				}
			}
		}

		/*
		cout << '<';
		for (int i = 0; i < size - 1;i++) {
			cout << _register[i] << ", ";
		}
		cout << _register[size - 1] << '>' << endl;
		*/
		
		// Removal
		size_t temp_size = 0;
		for (int i = 0; i < size; i++) {
			if(_register[i] == 0)
				vec[temp_size++] = vec[i];
		}

		// Also a part of removal
		vec.erase(vec.begin() + temp_size, vec.end());

		// Nulling out register
		delete[]_register;
		_register = nullptr;

		return vec;
	}

//#######################################################################################################################
// Mapping Functions (Implemented in PyBasics.cpp)
/*
	This Map() function takes a function as first param and a vector as second param.

	ex: Map(Upper, names);  // assume names as a 1D vector<string>
		now the Map() function will apply the Upper() function on all the elements of vector by-reference.
		it supports all the functions that are implemented in the string manipulation section. (Just above this Section)

Note: These cannot modify the vector by-reference as implicit/explicit type transformation is not allowed in C++
*/
	// Supports functors and lamdas but refrain from the void return type
	/*
	template<typename T, typename U, class Func>
	vector<U> IntelligentMap(Func function, vector<T> vecT) {
		vector<U> vecU;

		for (T t : vecT) {
			vecU.push_back(function(t));
		}

		return vecU;
	}
	*/

	// overloaded for Int()
	vector<int> Map(int (function) (string), vector<string> vec);			// returns a vector<int>
	vector<int> Map(int (function) (char), vector<char> vec);				// for compatibility with List function
	
	// overloaded for Str()
	template<typename T>
	vector<string> Map(string(function)(T), vector<T> vec) {
		vector<string> temp;
		for (T i : vec) {
			temp.push_back(function(i));
		}
		return temp;
	}

// universal Map() functions

	/*
	Runs the function on the input vector stores the output of the function in output vector
	then returns the output vector.
	Ex:

	double Double(string s){
		return stod(s);
	}

	Map(Double, vector<string>{"4", "5", "6"})
	Return: vec, which has been changed to vector<double>{4, 5, 6};
	*/
	template<typename T, typename U>
	vector<U> Map(U(function)(T), vector<T> vecT) {
		vector<U> vecU;
		for (T& i : vecT) {
			vecU.push_back(function(i));
		}
		return vecU;
	}

	/*
	Runs the function on the input vector stores the output of the function in same vector
	then returns the that vector.
	Ex:

	void square(int& n){
		n *= n;
	}

	Map(square, vector<int>{4, 5, 6})
	Return: vec, which has been changed to vector<int>{16, 25, 36};
	*/
	template<typename T>
	vector<T> Map(void(function)(T&), vector<T> vec) {
		for (T& i:vec) {function(i);}
		return vec;
	}

	/*
	Runs the function on the input vector stores the output of the function in same vector
	then returns that vector.
	Ex: 
	
	int square(int& n){
		n *= n;
		return n;
	}

	Map(square, vector<int>{4, 5, 6})
	Return: vec, which has been changed to vector<int>{16, 25, 36};
	*/
	template<typename T>
	vector<T> Map(T(function)(T&), vector<T> vec) {
		for (T& i : vec) { function(i); }
		return vec;
	}

	/*
	Runs the function on the input vector stores the output of the function in output vector
	then returns the output vector.
	Ex: Map(sin, vector<long double>{4.32,4.613,6.734})
	Return: vector<long double>{-0.923998, -0.995065, 0.435699};
	*/
	template<typename T>
	vector<T> Map(T(function)(T), vector<T> vec) {
		vector<T> newVec;
		for (T i : vec) { 
			newVec.push_back(function(i)); 
		}
		return newVec;
	}

//#######################################################################################################################
// Raw - Array of String Mapper
/*
	This MapArray() function specifically works only for string array.
	It Maps the String Manipulation Functions by-reference on the array.

	Note: Doesn't return anything.
*/
	template<typename T>
	void MapArray(string(*f) (string&), T& arr) {
		for (size_t i = 0; i < Size(arr); i++) {
			(*(arr + i)) = (*f) (*(arr + i));
		}
	}
/*
	It is a peculiar process of returning an array from a function. since in C++ a Raw-Array decays to a pointer when
	passed to a function. Its a good challenge to Implement those.

	Therefore MapArray function isn't overloaded for Int(), Double() and Str() functions.
*/
//#######################################################################################################################
/*
	This Function makes combinations from an array of integers.
	Ex. 
	Input-> {1,5,2,6,4,7}
	Output-> A vector of vector<int> filled with all the possible combinations of numbers from the input array.
	in this case : 152 156 154 157 126 124 127 164 167 147 526 524 527 564 567 547 264 267 247 647
	
	to get the numbers in right form use _make_int()
*/

	vector<int> make_int(vector<vector<int>>& vec);

	template<size_t s>
	vector<vector<int>> combinations(int(&num)[s], int k, int begin_idx = 0) {
		static vector<int> temp;
		static vector<vector<int>> NumDict;
		int size = s;
		if (k > 2) {
			fri(begin_idx, size - k + 1, 1) {
				temp.push_back(num[i]);
				combinations(num, k - 1, i + 1);
				temp.pop_back();
			}
		}
		else if (k == 2) {
			fri(begin_idx, size - 1, 1) {
				temp.push_back(num[i]);
				frj(i + 1, size, 1) {
					temp.push_back(num[j]);
					NumDict.push_back(temp);
					temp.pop_back();
				}
				temp.pop_back();
			}
		}

		return NumDict;
	}

//#######################################################################################################################
// Array <-> Vector Function
	/* 
	Not Sure if the functor approach is successful, but it is good to implement a help feature for every one of these
	*/

	class toVec {
	public:
		toVec() = default;
		string help();

		template<typename T, size_t size>
		vector<T> operator()(T(&arr)[size]) {
			return vector<T>(std::begin(arr), std::end(arr));
		}

		template<typename T>
		vector<T> operator()(Array<T>& arr) {
			return vector<T>(arr.begin(), arr.end());
		}

		template<typename T>
		vector<T> operator()(const Array<T>& ar) {
			Array<T> arr = ar;
			return vector<T>(arr.begin(), arr.end());
		}
	};
	
	class toArr {
	public:
		toArr() = default;
		string help();

		template<typename T, size_t size>
		Array<T> operator()(T(&arr)[size]) {
			return Array<T>(arr);
		}

		template<typename T>
		Array<T> operator()(vector<T>& vec) {
			return Array<T>(vec.begin(), vec.end());
		}

		template<typename T>
		Array<T> operator()(const vector<T>& vec) {
			return Array<T>(vec.begin(), vec.end());
		}
	};

//###########################################################################################################
// overloaded for Array<char>

	void toupper(char& c);
	void tolower(char& c);
	bool isalpha(char c);
	bool isdigit(char c);
	bool islower(char c);
	bool isupper(char c);
	bool isalnum(char c);
}
#endif // PYBASICS_H
