//  Author  - Siddhant Gupta.
//  Place   - Uttar Pradesh, India.
//  Completed On 9/05/2021.

// This PyBasics Library is a simulation of some basic Python functions.
// while implementing them the names were changed a little bit, as some keywords are reserved by C++.
// This Library Uses basic C++ functionality to reduce redundant typing by providing basic #includes
// and Input Output Functionailty

/*
// Features (Classes):
	- A Special File Handling Class is also provided to handle basic File opening processes in 1-2 lines of code.
	  Documentation in PyBasics.cpp

	- A Special Array Class. Array class implements array's in different form. other than std::array's but similar to std::vector
	  but different from std::vector, Array class has a lot more features built-in [read internal documentation]
	  It doesn't require size as a parameter. but it has a limitation, it's size is defaulted to INT32_MAX elements.
	  It can be changed by the programmer by changing the MAX_ARRAY_CAPACITY.
*/
/*
// Features (Namespaces):

	- This Library has two namespaces that are ____internal_print____ and ____to_string____
		> these handle operations/workings for print() and Str() so they need not be used outside this library.

*/
// Features (Funtions):
// Range()      : provides a vector<double> can be used in range based for loops. with python like Syntax.
// Input()      : provides a single line Input feature returns a string
// Size()       : determine the size of the array, despite wherever used and in whatever context.
// Int()        : converts a string to integer
// Double()     : converts a string to double
// Str()        : converts any valid datatype to a string
// print()      : can print any no. of arguements
// Print()      : can print 1D, 2D Arrays and Vectors
// toVec()      : can convert an array to a vector.
// find()       : can find an entity in a collection of same type of entities (raw array or vector)

/**  -- String Manipulation Functions --  **/
// Upper()						: to Upper Case the whole String
// Lower()						: to Lower Case the whole String
// Capitalize()					: to Capitalize a String
// Reverse()					: to Reverse a String
// Sort()						: to sort a string
// List()						: to convert a string to vector of characters
// Title()						: to make the text 'Title'
// Replace()					: to remove a replace a part of a string with another
// Strip()						: trims blank spaces at extreme ends 
// RemoveRedundantSpaces()		: Reduces numerous unnecessary spaces to one
// ReformatText()				: Reformats the text [read internal documentation]
// Pad()						: to append a character at start and in the end of a string

/**  -- Mapping Functions --  **/
// Map()        : can Apply any of the String Manipulations on a vector and Array Class objects of strings.
// MapArray()   : can Apply any of the String Manipulations on an raw-array of Strings, doesn't return anything

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

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <ctime>
#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// just a piece of code that determines if the passed paramenter is an iterator
template <class _iter>
using _iter_cat_t = typename iterator_traits<_iter>::iterator_category;

template <class... _Types>
using void_tt = void;

template <class _Ty, class = void>
constexpr bool _is_iterator_v = false;

template <class _Ty>
constexpr bool _is_iterator_v<_Ty, void_tt<_iter_cat_t<_Ty>>> = true;


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

	* even you can collect the data of all files in your data base in one go by using a vector<string>
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

// ================================================= Array Class: ======================================================= 
	constexpr int MAX_ARRAY_CAPACITY = INT32_MAX;
	constexpr int EXTRA_RESERVE = 10;
	/*
	This Array Class is designed to behave like a vector but in a permitted range of 0 - MAX_ARRAY_CAPACITY.
	Compatibility: 
		- With the algorithm library 
		- for each loops
		- any other Cpp library that accesses a contigious memory block using begin() and end() method.

	Supports:
		- Negative Index Accessibility
		- Negative Index Insertability
		- Sorted Insertability
		- Input via operator>>
		- Appending
		- Concatenation
		- Replacment
		- Poping
		- Sorting
		- Reversal
		- Erasing
		- Max and Min
		- Duplicates Removal
		- Count and Conditional Count
		- Conditional Removal and Complete removal (all occurrences) of an Element
		- Linear and Binary Search
		- Lower and Upper Bound Search
		- Rotation in Clockwise and Anti Clockwise Direction
		- Negative Positive Rearrangement

	Operators Supported:
		- operator<<
		- operator>> // requires that the size is set during initialization
		- operator=
		- operator+
		- operator+=
		- operator[]
		- all of the comparison operators like < , > , <= , >= , == , != 
		- operator() // this is an interesting one, it takes a function as a parameter and maps the function to all the array elements

	Other memory Manipulation functions Supported:
		- resize()
		- clear()
		- shrink_to_fit()

	Note:
		operators '+', '+=' can concatenate single values as
		well as values passed in the form of initializer_list.
		ex:
			// operator +=
			Array<int> arr{4,5,3};
			print(arr);
			arr += 5;
			print(arr);
			arr += {4,8,1};
			print(arr);

			// operator +
			print(arr + Array<int>{67, 89, 54});

		output:
			4 5 3
			4 5 3 5
			4 5 3 5 4 8 1
			4 5 3 5 4 8 1 67 89 54

		operator '+'  doesn't support direct initializer_list
	
	Since Raw arrays and std::array have a problem of not being dynamically declarable.
	for ex.: we cannot pass a variable array size in the templated std::array<{typename},{size_t}>
		i.e. we cannot increase a counter variable and then declare the Array with counter as the value of size.
		ex:
			int counter_val = function(param);
			std::array<int,counter_val> arr;   // this results in a compiler error.
			to avoid this. Array class is designed to not have the size parameter passed to it as template declaration.
			But Size can be passed as a param to constructor

	-	The Array Class provides transferabilty among functions without size becoming a hurdle in between.

	*/

	template <class T>
	class Array {
		size_t visible_size = 0;							// Visible Size
		T* values = nullptr;			// Actual array that holds the info
		int capacity = 0;					// Holding capacity of the array
		int multiplier = 0;			// factor by which the capacity increases
		
		// this helps in determining whether a Array<char> was intended to behave like a string
		bool is_string = false;

		// Used to get length as a returned value from a global function
		friend size_t Len(const Array<T>& arr) {
			return arr.visible_size;
		}

		// To Print the Array. it can be used with all the print functions.
		friend std::ostream& operator<< (std::ostream& os, const Array<T>& arr) {
			if (arr.is_string) {
				for (size_t i = 0; i < arr.visible_size; i++) {
					os << arr.values[i];
				}
			}
			else {
				os << '[';
				size_t i = 0;
				for (; i < arr.visible_size - 1; i++) {
					os << arr.values[i] << ", ";
				}
				os << arr.values[i] << ']';
			}
			return os;
		}

		// for support of input
		friend istream& operator>>(std::istream& is, Array<T>& arr) {
			arr.input();
			return is;
		}

		// for momentary or assignable join of two Arrays
		friend Array<T> operator+ (Array<T> lhs, Array<T> rhs) {
			lhs.concat(rhs);
			return lhs;
		}

		// yet another copy of swap :(
		template<typename Ty>
		void _swap(Ty& a, Ty& b) {
			Ty temp = a;
			a = b;
			b = temp;
		}

		void _allocate(int bytes = 0) {
			if (this->capacity == 0) {
				// shows new allocation
				this->capacity = bytes + EXTRA_RESERVE;
				this->values = new T[this->capacity];
			}
			else {
				this->capacity = ((++this->multiplier) * 10) + this->capacity + bytes;

				T* sample = new T[this->capacity];

				for (size_t i = 0; i < this->visible_size; i++) {
					sample[i] = this->values[i];
				}

				delete[]this->values;
				this->values = sample;
				sample = nullptr;
			}
		}

		void _de_allocate() {
			if (this->capacity == 0) {
				// nothing can be done
			}
			else {
				// clearing previous memory
				delete[]this->values;
				// allocating basic memory
				this->visible_size = 0;
				this->capacity = EXTRA_RESERVE;
				this->values = new T[this->capacity];
				this->multiplier = 0;
				// Allocates 10 units of space;
			}
		}

		/*
		To fill the default values. passed by the constructor
		This has to be done because for raw-arrays initialiser_list does it automatically.
		*/
		template<typename Custom>
		void _filler(initializer_list<Custom> init_l) {
			int i = 0;
			int size = init_l.size();

			if (this->capacity == 0) {
				this->_allocate(size);
			}

			for (auto& il : init_l) {
				this->values[i] = il;
				i++;
			}

			visible_size = i;
		}

	public:
		/////////////////////////////////////
///////////////    Constructors    ///////////////
		////////////////////////////////////

		// By default allocates atleast 10 units of memory
		Array() {
			this->_allocate();
		}

		// allocates s units of memory
		Array(size_t s) {
			this->visible_size = s;
			this->_allocate(s);
		}

		// allocates s units of memory and initializes all of them to t
		Array(size_t s, T t) {
			this->visible_size = s;
			this->_allocate(s);
			this->fill(t);
		}

		/*			Constructors (for operator= convinience)		*/
		Array(initializer_list<char> init_l) {
			this->_filler(init_l);
		}

		Array(initializer_list<int> init_l) {
			this->_filler(init_l);
		}

		Array(initializer_list<float> init_l) {
			this->_filler(init_l);
		}

		Array(initializer_list<double> init_l) {
			this->_filler(init_l);
		}

		Array(initializer_list<long> init_l) {
			this->_filler(init_l);
		}

		Array(initializer_list<char const*> init_l) {
			this->_filler(init_l);
		}

		// for management of Strings
		Array(string s) {
			int len = (s.size() + 1);
			this->is_string = true;
			this->visible_size = (len - 1);
			this->_allocate(len);
			for (size_t i = 0; i < this->visible_size; i++) {
				this->values[i] = s[i];
			}
		}

		Array(char const* s) : Array(string(s)) {}
		
		// for initialization from sections of a raw array
		Array(T* begin, T* end, size_t additional_bytes = 0) {
			int len = end - begin;
			this->_allocate(len + additional_bytes);
			this->visible_size = len;
			for (int i = 0; i < len; i++) {
				this->values[i] = *(begin + i);
			}
		}

		// for conversion of a raw array completely to Array Class object
		template<size_t s>
		Array(T (&_arr)[s]) {
			int len = s;
			this->_allocate(len);
			this->visible_size = len;
			for (int i = 0; i < len; i++) {
				this->values[i] = *(_arr + i);
			}
		}
		
		// Iterator Based Inititalization
		template<class _Iter, enable_if_t<_is_iterator_v<_Iter>, int> = 0>
		Array(_Iter begin, _Iter end) {
			int len = end - begin;
			this->_allocate(len);
			this->visible_size = len;
			for (int i = 0; i < len; i++) {
				this->values[i] = *(begin + i);
			}
		}

		/*
		For User defined types or class objects.
		Even though the Parameter type is 'CustomType' but it should be equal to 'T'
		ex:
			Array<Player> players
			{	// not permissable by the compiler
				Player{<param1>,<param2>},		// Custom Player Class
				NewPlayer{<param1>,<param2>}	// Custom NewPlayer Class
			};
			even if the two classes posses the exact defintion they shouldn't be assigned in variable object types.

			Array<Player> players
			{	// not permissable by the compiler
				NewPlayer{<param1>,<param2>},		// Custom NewPlayer Class
				NewPlayer{<param1>,<param2>}		// Custom NewPlayer Class
			};

			Only Valid Initialization
			Array<Player> players
			{	// permissable by the compiler
				Player{<param1>,<param2>},		// Custom Player Class
				Player{<param1>,<param2>}		// Custom Player Class
			};

		Also the Custom Class Should Define a Default Constructor.
		PS: this is no different from vectors.
		*/
		template<typename CustomType>
		Array(initializer_list<CustomType> init_l) {
			this->_filler(init_l);
		}

		// Handles 2D Initializations
		template<typename _Ty>
		Array(initializer_list<initializer_list<_Ty>> init_l2D) {
			this->_filler(init_l2D);
		}

		// Handles 3D Initializations
		template<typename _Ty>
		Array(initializer_list<initializer_list<initializer_list<_Ty>>> init_l3D) {
			this->_filler(init_l3D);
		}

		///////////////////////////////////////
///////////////   Copy Constructor    ///////////////
		//////////////////////////////////////

		Array(const Array<T>& obj) :
			multiplier{ obj.multiplier },
			visible_size {obj.visible_size},
			capacity {obj.capacity}
		{
			this->values = new T[obj.capacity];

			for (size_t i = 0; i < obj.visible_size; i++) {
				this->values[i] = obj.values[i];
			}

			/*cout << "copy constructor" << endl;
			this->log_properties();*/
		}

		///////////////////////////////////////
///////////////   Move Constructor    ///////////////
		//////////////////////////////////////

		Array(Array&& obj) noexcept {
			// cout << "Move Constructor" << endl;
			// changing ownership
			this->values = obj.values;
			// nulling out sample
			obj.values = nullptr;
			// assigning all the values accordingly
			this->capacity = obj.capacity;
			this->visible_size = obj.visible_size;
			this->multiplier = obj.multiplier;
		}


		/////////////////////////////////////////////
///////////////    Basic Utility Functions    ///////////////
		////////////////////////////////////////////

		// Fills the Array upto its visible size.
		void fill(T value) {
			for (size_t i = 0; i < this->visible_size; i++) {
				values[i] = value;
			}
		}

		/* creates a positive range of elements from [begin,end) using increment 
		Ex: If you want to create an increasing range.
		Note: increment should be positive.
		Where it should be used: all numerical and character datatypes
		*/
		Array& make_increasing_range(T begin, T end, T increment = 1) {
			assert(begin < end);
			assert(increment > 0);
			// checking if the range extends beyond the capacity and allocating any shortcomings
			int num_of_vals = (int)ceil(((double)(end - begin)) / ((double)increment));
			
			if (num_of_vals > this->capacity) {
				this->_de_allocate();
				this->_allocate(num_of_vals);
			}

			int idx = 0;
			for (T i = begin; i < end; i += increment) {
				this->values[idx] = i;
				idx++;
			}

			this->visible_size = idx;

			return *this;
		}

		/* creates a negative range of elements from [end,begin) using decrement
		Ex: if you want to create a range that goes from 10 to 1 using a decrement of 1
		Note: Decrement should be negative.
		Where it should be used: all numerical and character datatypes
		*/
		Array& make_decreasing_range(T begin, T end, T decrement = -1) {
			assert(end < begin);
			assert(decrement < 0);
			// checking if the range extends beyond the capacity and allocating any shortcomings
			int num_of_vals = (int)ceil(((double)(end - begin)) / ((double)decrement));

			if (num_of_vals > this->capacity) {
				this->_de_allocate();
				this->_allocate(num_of_vals);
			}

			int idx = 0;
			
			for (T i = begin; i > end; i += decrement) {
				this->values[idx] = i;
				idx++;
			}

			this->visible_size = idx;

			return *this;
		}

		//template<std::enable_if_t<!std::is_same<string, T>::value, int>* = nullptr>
		void make_random_range(int len) {
			// make sure this function doesn't run on anything else than numeric or character data types
			if (len > this->capacity) {
				this->_de_allocate();
				this->_allocate(len);
			}

			srand((unsigned int)time(0));
			fr(0, len, 1) {
				this->values[i] = (T)rand();
			}

			this->visible_size = len;
		}

		// Returns visible size 
		int size() { return (int)this->visible_size; }

		// returns capacity
		int get_capacity() { return capacity; }

		//////////////////////////////
///////////////    Operators    ///////////////
		//////////////////////////////

		// Supports positive and negative indices within the range of 0 - visible_size
		T& operator[] (int index) {
			// supports negative indices
			if (index >= 0) {
				assert(index >= 0 and index < (int)this->visible_size);
			}
			if (index < 0) {
				index = this->visible_size - ((-1) * index);
				assert(index >= 0 and index < (int)this->visible_size);
			}
			return this->values[index];
		}

		/*
		Maps a function passed as parameter to all the array elements.
		Note: Type conversions other than the implicit ones are restricted by C++ itself.
		Ex: The passed function should look like one of these  
			> int square (int n) {return n*n;}
			> void square (int& n) {n = n*n;}
			> int square (int& n) {n = n*n; return n;}
		*/
		// Ex -> int square (int n) {return n*n;}
		void operator()(T(function)(T)) {
			for (size_t i = 0; i < this->visible_size; i++) {
				this->values[i] = function(this->values[i]);
			}
		}

		// Ex -> void square (int& n) {n = n*n;}
		void operator()(void(function)(T&)) {
			for (size_t i = 0; i < this->visible_size; i++) {
				function(this->values[i]);
			}
		}

		// Ex -> int square (int& n) {n = n*n; return n;}
		void operator()(T(function)(T&)) {
			for (size_t i = 0; i < this->visible_size; i++) {
				function(this->values[i]);
			}
		}

		// Copy Assignment, Making two exact copies
		Array& operator= (const Array<T>& obj) {
			// acquiring memory equivalent to assignee
			T* sample = new T[obj.capacity];

			// filling the memory with data
			for (size_t i = 0; i < obj.visible_size; i++) {
				sample[i] = obj.values[i];
			}

			// removing old data
			delete[]this->values;

			// changing ownership
			values = sample;

			// nulling out sample
			sample = nullptr;

			// assigning all the values accordingly
			this->capacity = obj.capacity;
			this->visible_size = obj.visible_size;
			this->multiplier = obj.multiplier;

			// returning the reference for current array
			return *this;
		}

		// Move Assignment, Changing the owner ship
		Array& operator= (Array<T>&& obj) noexcept {
			// removing old data
			delete[]this->values;

			// changing ownership
			this->values = obj.values;

			// nulling out sample
			obj.values = nullptr;

			// assigning all the values accordingly
			this->capacity = obj.capacity;
			this->visible_size = obj.visible_size;
			this->multiplier = obj.multiplier;

			// returning the reference of the current array
			return *this;
		}

		// Compares Visible Size and All the values
		bool operator== (Array<T>& arr) {

			if (this->visible_size != arr.visible_size) {
				return false;
			}

			for (size_t i = 0; i < this->visible_size; i++) {
				if (this->values[i] != arr.values[i]) {
					return false;
				}
			}

			return true;
		}

		bool operator<(Array<T>& rhs) {
			return std::lexicographical_compare(this->begin(), this->end(), rhs.begin(), rhs.end());
		}

		bool operator>(Array<T>& rhs) {
			return !this->operator<(rhs);
		}

		bool operator<=(Array<T>& rhs) {
			return !(this->operator>(rhs));
		}

		bool operator>=(Array<T>& rhs) {
			return !(this->operator<(rhs));
		}

		bool operator!=(Array<T>& rhs) {
			return !(this->operator==(rhs));
		}

		operator bool() {
			return this->values != nullptr;
		}

		// operator format for appending
		Array& operator+=(T t) {
			this->append(t);
			return *this;
		}

		// Appends all the elements passed to it and increases the visible size by the no. of passed elements
		Array& operator+=(Array<T> arr) {
			this->concat(arr);
			return *this;
		}


		  ////////////////////////////////////////
///////////////   Memory/Size Manipulators    ///////////////
		  ///////////////////////////////////////

		Array& resize(int bytes = 0) noexcept {
			// allocates more bytes than actually passed as parameter, just in case
			this->_allocate(bytes);
			return *this;
		}

		// clears the data;
		Array& clear() noexcept {
			this->_de_allocate();
			return *this;
		}

		// shrinks the size of the array to visible_size
		Array& shrink_to_fit() noexcept {
			// allocating required memory
			T* sample = new T[this->visible_size];

			// initializing the memory
			for (size_t i = 0; i < this->visible_size; i++) {
				sample[i] = this->values[i];
			}

			// clearing old data
			delete[] this->values;

			// changing ownership
			this->values = sample;

			// nullfying sample
			sample = nullptr;

			// setting all the parameters right
			this->capacity = this->visible_size;
			this->multiplier = 0;

			// returning the reference to current object
			return *this;
		}

		// return the address of first element
		T* begin() {
			return &(this->values[0]);
		}
		
		// return the address of last element
		T* end() {
			return &this->values[visible_size];
		}

		///////////////////////////////////////
///////////////   Member Functions   ///////////////
		//////////////////////////////////////

		Array& input() {
			if (this->is_string) {
				// declaring a temp string
				string s;
				// taking input
				cout << "Enter a string (ending with \\n): ";
				std::getline(cin, s);

				// deleting previous data
				delete[] this->values;

				// getting the size of the input
				int size = s.size();

				// initializing things right
				this->capacity = size + EXTRA_RESERVE;
				this->values = new T[this->capacity];
				this->visible_size = size;
				this->multiplier = 0;

				// finally initializing the values
				for (size_t i = 0; i < size; i++) {
					this->values[i] = s[i];
				}
			}
			else {
				// cout << "Enter " << this->visible_size << " values: ";
				for (size_t i = 0; i < this->visible_size; i++) {
					cin >> this->values[i];
				}
			}
			return *this;
		}

		// Appends and Element to the last and increases visible size by 1
		Array& append(T t) noexcept {
			this->concat({ t });
			return *this;
		}

		// inserts elem at the given index
		Array& insert(int index, T elem) noexcept {
			assert((this->visible_size + 1) < MAX_ARRAY_CAPACITY);

			index >= 0 ? (index) : (index = (this->visible_size - ((-1) * index)));

			assert(index >= 0 and index < (int)this->visible_size);

			if (this->visible_size == this->capacity) {
				this->_allocate();
			}

			for (size_t i = this->visible_size; (int)i > index; i--) {
				this->values[i] = this->values[i - 1];
			}

			this->values[index] = elem;
			this->visible_size++;
			return *this;
		}

		// Sorts the Array, finds the position of elem and inserts it there
		Array& sorted_insert(T elem) {
			// sorting
			this->sort();

			if ((int)this->visible_size == this->capacity) {
				this->_allocate();
			}

			int i = (this->visible_size - 1);

			// finding the place
			while (i >= 0 and this->values[i] > elem) {
				this->values[i + 1] = this->values[i];
				i--;
			}

			this->visible_size++;
			this->values[i + 1] = elem;

			return *this;
		}

		Array& concat(char const* s) noexcept {
			if (this->is_string) {
				this->concat(Array<char>(s));
			}
			return *this;
		}

		// concatenates Array at the back, also reallocates any extra memory if required
		// important: if T = string and concatenation of only one element is required, consider using append()
		Array& concat(Array<T> arr) noexcept {
			int totalSize = this->visible_size + arr.visible_size;

			// concatenation shouldn't make the array more than MAX_ARRAY_CAPACITY
			assert(totalSize < MAX_ARRAY_CAPACITY);

			if (totalSize >= this->capacity) {
				// uses arr.visible_size to increase the size accordingly to fit the array 
				// and still have enough space to concatenate more before another reallocation
				this->_allocate(arr.visible_size);
			}

			int  i = this->visible_size;
			int arrIndex = 0;
			for (; i < totalSize; i++) {
				this->values[i] = arr[arrIndex];
				arrIndex++;
			}
			this->visible_size += arrIndex;
			return *this;
		}

		// finds and replaces the value, if unable to find the value no changes take place
		// faster replacements if array is sorted
		// Note:
		//	> replaces the first occurrence in an unsorted array.
		//	> replaces the last occurrence in a sorted array.
		Array& replace(T elem1, T elem2) {
			int index = -1;
			if (this->is_sorted_ascend()) {
				index = this->upper_bound(elem1);
			}
			else {
				index = this->linear_search(elem1);
			}
			index >= 0 ? (this->values[index] = elem2) : (elem2);
			return *this;
		}

		// replaces all occurrences of elem1 with elem2
		Array& replace_all(T elem1, T elem2) {
			for (size_t i = 0; i < this->visible_size; i++) {
				if (this->values[i] == elem1) this->values[i] = elem2;
			}
			return *this;
		}

		// outputs all the occurrences of elem
		void find_all(T elem) {
			for (size_t i = 0; i < this->visible_size; i++) {
				if (this->values[i] == elem) cout << "Exists at index: " << i << endl;
			}
		}

		// replaces all occurrences like this:
		//		elem1 -> elem2
		//		elem2 -> elem1
		Array& interchange(T elem1, T elem2) {
			for (size_t i = 0; i < this->visible_size; i++) {
				if (this->values[i] == elem1) { this->values[i] = elem2; }
				else if (this->values[i] == elem2) { this->values[i] = elem1; }
			}
			return *this;
		}

		// initializes the last element with the default value and reduces the visible size by 1
		Array& pop() {
			this->values[--this->visible_size] = T{};
			return *this;
		}

		private:
			void _shift_left(int begin) {
				for (size_t i = begin; i < this->visible_size; i++) {
					this->values[i] = this->values[i + 1];
				}
				this->pop();
			}

		public:
		// removes the element at a given index and returns removed element
		T remove(int index) {
			T val = this->values[index];
			this->_shift_left(index);
			return val;
		}

		// to remove all the occurrences of elem
		// time complexity: O(n)
		void remove_all(T elem) {
			size_t temp_size = 0;
			for (size_t i = 0; i < this->visible_size;i++) {
				if (this->values[i] != elem) {
					this->values[temp_size++] = this->values[i];
				}
			}

			// defaulting deleted section
			for (size_t i = temp_size; i < this->visible_size; i++) {
				this->values[i] = T{};
			}

			this->visible_size = temp_size;
		}

		// conditional remove
		//	> removes elements if a certain condition is met
		void remove_if(bool(function)(T)) {
			size_t temp_size = 0;
			for (size_t i = 0; i < this->visible_size; i++) {
				if (!function(this->values[i])) {
					this->values[temp_size++] = this->values[i];
				}
			}

			// defaulting deleted section
			for (size_t i = temp_size; i < this->visible_size; i++) {
				this->values[i] = T{};
			}

			this->visible_size = temp_size;
		}

		// Removes all the duplicates 
		// Note: it will also sort the data.
		// Time Complexity: O(n) [if we keep sorting out of equation] with a positive point that it doesn't use hash table
		Array& remove_duplicates() {
			this->sort();
			size_t temp_size = 1;
			T prev_elem = this->values[0];
			for (size_t i = 0; i < this->visible_size; i++) {
				if (this->values[i] != prev_elem) {
					this->values[temp_size++] = this->values[i];
					prev_elem = this->values[i];
				}
			}

			// defaulting deleted section
			for (size_t i = temp_size; i < this->visible_size; i++) {
				this->values[i] = T{};
			}

			this->visible_size = temp_size;
			return *this;
		}

		// counts all th occurrences of elem
		int count(T elem) {
			int count = 0;
			for (size_t i = 0; i < this->visible_size; i++) {
				if (this->values[i] == elem) count++;
			}
			return count;
		}

		// conditional count
		//	Counts only if a certain condition is met.
		//	Condition should be passed as a function.
		int count_if(bool(function)(T)) {
			int count = 0;
			for (size_t i = 0; i < this->visible_size; i++) {
				if (function(this->values[i])) count++;
			}
			return count;
		}

		// erases a part of the array marked by [begin,end)
		Array& erase(int begin, int end) {
			int base = begin;
			// shifting everything towards left
			for (size_t i = end; i < this->visible_size; i++) {
				this->values[base++] = this->values[i];
			}
			// clearing and defaulting out deleted section
			for (size_t i = base; i < this->visible_size; i++) {
				// initiailizing with default value
				this->values[i] = T{};
			}
			this->visible_size -= (end - begin);
			return *this;
		}

		// erases everything starting from begin
		Array& erase(int begin) {
			this->erase(begin,this->visible_size);
			return *this;
		}

		private:

			void _place_sorted(T elem, int end) {
				end--;
				
				// finding the place
				while (end >= 0 and this->values[end] > elem) {
					*(this->values + end + 1) = this->values[end];
					end--;
				}

				// putting the elem in its sorted position
				this->values[end + 1] = elem;
			}

		public:

		// Sorts the array (using insertion sort), only if it is not sorted
		// since it is adaptive and stable
		Array& sort() {
			if (this->is_sorted_ascend()) {
			}
			else if (this->is_sorted_descend()) {
				this->reverse();
			}
			else if (this->visible_size >= 200) {
				//cout << "going big" << endl;
				std::sort(this->begin(), this->end());
			}
			else {
				// insertion sort
				for (size_t i = 1; i != this->visible_size; i++) {
					this->_place_sorted(this->values[i],i);
				}

				// bubbble sort (just in case)
				/*for (size_t i = 0; i < this->visible_size; i++) {
					for (size_t j = 1; j < this->visible_size - i; j++) {
						if (this->values[j - 1] > this->values[j])
							_swap(this->values[j - 1], this->values[j]);
					}
				}*/
			}
			return *this;
		}

		Array& shuffle() {
			// library offers a highly reliable shuffle without any loss of data in brutally random shuffling
			std::random_shuffle(this->begin(), this->end());
			return *this;
		}

		Array& swap(Array<T>& obj) {
			this->_swap(this->visible_size, obj.visible_size);
			this->_swap(this->multiplier, obj.multiplier);
			this->_swap(this->capacity, obj.capacity);
			this->_swap(this->values, obj.values);
			return *this;
		}

		// returns index of the element
		int linear_search(T elem) {
			for (size_t i = 0; i < visible_size; i++) {
				if (values[i] == elem) {
					return i;
				}
			}
			return -1;
		}

		// Return: true if the array is sorted in ascending order
		bool is_sorted_ascend() {
			for (size_t i = 0; i < visible_size - 1; i++) {
				if (this->values[i] > this->values[i + 1]) {
					return false;
				}
			}
			return true;
		}

		// Return: true if the array is sorted in descending order
		bool is_sorted_descend() {
			for (size_t i = 0; i < visible_size - 1; i++) {
				if (this->values[i] < this->values[i + 1]) {
					return false;
				}
			}return true;
		}

	private:

		// recursive version
		int __binary_search(T* arr, int low, int high, T elem) {
			int mid = (low + high) / 2;
			if (low <= high) {
				if (arr[mid] == elem) {
					return mid;
				}
				else if (elem < arr[mid]) {
					return __binary_search(arr, low, mid - 1, elem);
				}
				else if (elem > arr[mid]) {
					return __binary_search(arr, mid + 1, high, elem);
				}
			}
			return -1;
		}

		// for debugging
		void _show() {
			for (size_t i = 0; i < this->visible_size; i++) {
				cout << this->values[i] << " ";
			}cout << endl;
		}

	public:
		/* Note: Always search for a value one degree lesser 
		Ex: search 2 in Array<int>{5,4,3,2,1} 
			search {1,2,3} in Array<Array<int>> {{1,2,3}, {3,4,5}}
		No guarantee for presence of a 2D matrix in 3D matrix or above
		*/
		// returns true if the element is present, false if not.
		bool binary_search(T elem) {
			// temporary sample for binary searching
			T* sample = new T[visible_size];

			// copying the values
			for (size_t i = 0; i < visible_size; i++) {
				sample[i] = this->values[i];
			}

			// swapping the ownership
			this->_swap(this->values,sample);

			// because sorting works on this->values so to let sorting be handled by sort()
			this->sort();

			// again swapping the ownership
			this->_swap(this->values, sample);

			// finding
			int idx = this->__binary_search(sample, 0, this->visible_size, elem);

			// clearing the sample
			delete[] sample;
			sample = nullptr;

			// returning the presence of element
			return idx >= 0 ? true : false;
		}

		int lower_bound(T elem) {
			// assumes the array is already sorted
			// this code implemented similar to lower_bound function in xutility library
			int _count = this->visible_size;
			T* _first = &this->values[0];

			while (_count > 0) {
				int _count2 = _count / 2;
				T* _mid = (_first + _count2);
				if (*_mid < elem) {
					_first = (_mid + 1);
					_count -= _count2 + 1;
				}
				else {
					_count = _count2;
				}
			}

			return (_first - &this->values[0]);
		}

		// returns the upper bound of the passed element, greater than elem
		int upper_bound(T elem) {
			// assumes the array is already sorted
			int _count = this->visible_size;
			T* _last = &this->values[this->visible_size - 1];

			while (_count > 0) {
				int _count2 = _count / 2;
				T* _mid = (_last - _count2);
				if (*_mid > elem) {
					_last = _mid - 1;
					_count -= _count2 + 1;
				}
				else {
					_count = _count2;
				}
			}

			return (_last - &this->values[0]);
		}


		// Max Element
		T max() {
			T temp = this->values[0];
			for (size_t i = 0; i < this->visible_size; i++) {
				if (this->values[i] > temp) {
					temp = this->values[i];
				}
			}
			return temp;
		}

		// Min Element
		T min() {
			T temp = this->values[0];
			for (size_t i = 0; i < this->visible_size; i++) {
				if (this->values[i] < temp) {
					temp = this->values[i];
				}
			}
			return temp;
		}

		// logs all the properties of the array on console
		void log_properties(char const* entry = "",bool log_obj_details = false, bool show_log_count = true) {
			// irrespective of the object
			static int _i = 0;
			
			if (show_log_count)
				cout << "Log Record Count: " << _i << endl;

			if (log_obj_details) {
				cout << "Object Address: " << this << endl;
				cout << "Object Type: " << typeid(*this).name() << endl;
			}

			if(entry != "")
				cout << "Debug Entry: " << entry << endl;

			cout << "Content: "; this->_show();
			cout << "Size: " << this->visible_size << endl;
			cout << "Current Capacity Multiplier: " << this->multiplier << endl;
			cout << "Current Capacity: " << this->capacity << endl;
			cout << endl;
			_i++;
		}

		// Arranges negatives on left side, positives on right side
		Array& neg_pos_rearrange() {
			int i = 0, j = visible_size - 1;
			while (i < j) {

				while (this->values[i] < 0) { i++; }
				while (this->values[j] >= 0) { j--; }

				if (i < j)
					_swap(this->values[j], this->values[i]);
			}
			return *this;
		}

	public:
		// rotates the array by the given number of times anticlockwise
		// time complexity: O(n), auxilliary space required: 5 * sizeof(int)
		Array& rotate_anti_clockwise(int no_of_times = 1) {
			// using times as pivot
			int first_mid = no_of_times / 2, second_mid = ((this->visible_size + no_of_times) / 2);
			int first_last = no_of_times - 1, second_last = (this->visible_size + no_of_times - 1);
			int i = 0;
			
			// reversing [0,times) // no. of iterations = no_of_times/2
			for (i = 0; i < first_mid; i++) {
				_swap(this->values[i], this->values[first_last - i]);
			}

			// reversing [times,visible_size) // no. of iterations = (no_of_times + visible_size)/2
			for (i = no_of_times; i < second_mid; i++) {
				_swap(this->values[i], this->values[second_last - i]);
			}

			// reversing whole array
			this->reverse();
			return *this;
		}

		// rotates the array by the given number of times clockwise
		// time complexity: O(n)
		Array& rotate_clockwise(int times = 1) {
			this->rotate_anti_clockwise(this->visible_size - times);
			return *this;
		}

		// Reverses the Array
		Array& reverse() {
			int mid = this->visible_size / 2;
			for (int i = 0; i < mid; i++) {
				_swap(this->values[i], this->values[this->visible_size - i - 1]);
			}
			return *this;
		}

		// Gets Rid of allocated memory and sets everything right
		~Array() {
			this->visible_size = 0;
			this->capacity = 0;
			this->multiplier = 0;
			delete[]this->values;
			this->values = nullptr;
		}
	};

	/*
	For 2D Arrays Initialization can be done this way.

		Array<Array<int>> arr2D {			 
			{1,4,2},
			{5,3,7},
			{6,4,3}
		};

		for (int i = 0; i < arr2D.size(); i++) {
			print(arr2D[i]);
		}

		Array<Array<string>> arr2DStr {				  
			{"atr","gec","gwq"},
			{"gtr","hyt","jyt","gir","ort"},
			{"ryt","thu","fre","tre"}
		};

		// if using print function
		for (int i = 0; i < arr2DStr.size(); i++) {
			print(arr2DStr[i]);
		}

		for (int i = 0; i < arr2DStr.size(); i++) {
			for (int j = 0; j < arr2DStr[i].size(); j++) {
				cout << arr2DStr[i][j] << " ";
			}
			cout << endl;
		}
	*/

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
	bool find(U u, const Array<T>& arr) noexcept {
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
// TypeCasters
	// Implementation in PyBasics.cpp
	int Int(string s);
	int Int(int i);
	int Int(char ch);
	int Int(double d);
	double Double(string s);
	double Double(char ch);
	double Double(double d);
	string Str(char ch);
	string Str(char const* str);
	string Str(string& s);
// does nothing but prevents Str(T t) from throwing a string to string conversion error
/*
This Str() function converts any type of default datatype into string.
Note: uses the builtin to_string() function.
*/
	template <typename T>
	string Str(T t) {
		return to_string(t);
	}

/*
	This Str() function converts any type of default datatype raw - array into string.
*/
	template <class _Ty, size_t _Size>
	string Str(_Ty(&_Array)[_Size]) noexcept {
		string s = "[";
		int i = 0;
		for (; i < _Size - 1; i++) {
			s += ' ' + to_string(_Array[i]) + ',';
		}
		s += " " + to_string(_Array[i]);
		return s + " ]";
	}

//#######################################################################################################################
// Input
// Implementation in PyBasics.cpp
	string Input(string s = "");

//#######################################################################################################################
// Overloaded for including vector printing along with other arguements in print();
	template<typename T>
	ostream& operator<< (ostream& os, vector<T>& vec) {
		os << '<';
		size_t i = 0;
		for (; i < vec.size() - 1; i++) {
			os << vec[i] << ", ";
		}
		os << vec[i] << '>';
		return os;
	}

	template<typename T>
	ostream& operator<< (ostream& os, const vector<T>& vec) {
		os << '<';
		size_t i = 0;
		for (; i < vec.size() - 1; i++) {
			os << vec[i] << ", ";
		}
		os << vec[i] << '>';
		return os;
	}

	// for concatention of two vectors
	template<typename T>
	vector<T> operator+(vector<T> lhs, vector<T> rhs) {
		for (T& t : rhs) {
			lhs.push_back(t);
		}
		return lhs;
	}

	template<typename T>
	ostream& operator<< (ostream& os, deque<T>& deq) {
		os << '<';
		size_t i = 0;
		for (; i < deq.size() - 1; i++) {
			os << deq[i] << ", ";
		}
		os << deq[i] << '>';
		return os;
	}

	template<typename T>
	ostream& operator<< (ostream& os,const deque<T>& deq) {
		os << '<';
		size_t i = 0;
		for (; i < deq.size() - 1; i++) {
			os << deq[i] << ", ";
		}
		os << deq[i] << '>';
		return os;
	}

//#######################################################################################################################
// Printer
/*
	Py namespace provides a print functions
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
	These functions are overloaded just to save the usage of namespace print_container.
	and to also reduce the overhead recursive calls made for 2 - 3 params.
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
		for (; i < _Size - 1; i++) {
			cout << _Array[i] << ", ";
		}
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

// These are overloaded with default types just to save the overhead of deducing the type.
	void Print(vector<string>& vec, string end = " ");   // Implemented in PyBasics.cpp
	void Print(vector<int>& vec, string end = " ");      // Implemented in PyBasics.cpp

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
	// These are overloaded with default types just to save the overhead of deducing the type.
	void Print(Array<string>& arr, string end = " ");   // Implemented in PyBasics.cpp
	void Print(Array<int>& arr, string end = " ");      // Implemented in PyBasics.cpp

	template <typename T>
	void Print(Array<T>& arr, string end = " ") {
		for (size_t i = 0; i < arr.size(); i++) {
			say arr[i] << end;
		} say "" done;
	}

	// This Overloaded Function Handles Printing of a vector returned by a function like Map() or SplitInArray().
	template <typename T>
	void Print(const Array<T>& arr, string end = " ") {
		for (size_t i = 0; i < arr.size(); i++) {
			say arr[i] << end;
		} say "" done;
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
		for (size_t i = 0; i < arr.size(); i++) {
			for (size_t j = 0; j < arr[i].size(); j++) {
				say arr[i][j] << end;
			} say "" done;
		}
	}

	// for r-value of 2D Array Class Object
	template <typename T>
	void Print(const Array<Array<T>>& arr, string end = "\t") {
		for (size_t i = 0; i < arr.size(); i++) {
			for (size_t j = 0; j < arr[i].size(); j++) {
				say arr[i][j] << end;
			} say "" done;
		}
	}

//#######################################################################################################################
// 1D Raw - Array Printer
	template <class _Ty, size_t _Size>
	void Print(_Ty(&_Array)[_Size], string end = " ") noexcept {
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

	template<typename T>
	double Sum(T& arr) {
		double sum = 0;
		for (size_t i = 0; i < Size(arr); i++) {
			sum += arr[i];
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

	template<typename T>
	T Sum(const vector<T>& vec) {
		vector <T> v = vec;
		return Sum(v);
	}

	template<typename T>
	double Sum(Array<T>& arr) {
		double sum = 0;
		for (size_t i = 0; i < Len(arr); i++)
			sum += arr[i];
		return sum;
	}

	template<typename T>
	double Sum(const Array<T>& arr) {
		Array<T> ar = arr;
		return Sum(ar);
	}

	string Sum(vector<string>& vec);
	string Sum(const vector<string>& vec);
	string Sum(Array<string>& arr);
	string Sum(const Array<string>& arr);

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
	T Max(vector<T>& vec) {
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
	T Min(vector<T>& vec) {
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
	vector<T> Sort(vector<T>&& v) {
		return Sort(v);
	}

	// for 1D Array Class Objects
	// Sorts in: O(n^2) Time
	template <typename T>
	Array<T> Sort(Array<T>& arr) {
		return arr.sort();
	}

	template <typename T>
	Array<T> Sort(Array<T>&& arr) {
		return arr.sort();
	}

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
	string Strip(string& s);
	string RemoveRedundantSpaces(string& s);
	string ReformatText(string& s);

	// for r-value optimization
	string Upper(string&& s);
	string Lower(string&& s);
	string Capitalize(string&& s);
	string Reverse(string&& s);
	string Sort(string&& s);	// String overload for Sort functions
	string Title(string&& s);
	string Strip(string&& s);
	string RemoveRedundantSpaces(string&& s);
	string ReformatText(string&& s);

	// python type string manipulators
	vector<char> List(string s);							 // converts a string into a vector of characters
	string Replace(string Str, string Old, string New);
	vector<string> Split(string str, char separator = ' ', bool considerSpacesToo = true);	 // converts a string into vector of strings based on the separator provided 
	vector<string> Split(string s, string separator);

	// for Array Class Object. Don't prefer if no. of splits is not confirmed.
	// throws an exception -> "Concat Error: total array size exceeds default limit [50]"
	Array<string> SplitInArray(string str, char separator = ' ', bool considerSpacesToo = true);

	// Cannot be used with map()
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

//	Dissappointment functions

	template<typename T>
	void missing_elements_of_an_AP(vector<T> vec) {
		// Assumption is that the vector has consecutive elements from first_elem to last_elem
		// and only one elem is missing from it
		/*
		T first_elem = (*vec.begin()) - 1, last_elem = *(vec.end() - 1);
		// using (n * (n+1)) / 2
		T sum_first = (first_elem * (first_elem + 1)) / 2, sum_last = (last_elem * (last_elem + 1)) / 2;
		T difference = sum_last - sum_first;
		T actual_sum = Sum(vec);
		return difference - actual_sum;
		*/

		T a = vec[0], l = vec[vec.size() - 1];
		int n = vec.size();
		
		T d = INT32_MAX;
		for (int i = 1; i < n; i++) {
			if ((vec[i] - vec[i - 1]) < d) {
				d = vec[i] - vec[i - 1];
			}
		}



		T _a = a;
		cout << "missing elements: ";
		for (int i = 0; i < n;) {
			if (_a == vec[i]) { i++; }
			else { cout << _a << " "; }
			_a += d;
		}
		cout << endl;
	}

	template<typename T>
	vector<T> FindMoreThanOneMissingElement(vector<T> vec) {
		// Assumption is that the vector has consecutive elements from first_elem to last_elem
		// and only one elem is missing from it
		T low = (*vec.begin()), high = *(vec.end() - 1), len = vec.size();
		T diff = low - 0;
		vector<T> miss_cont;
		for (int i = 0; i < len; i++) {
			if (vec[i] - i != diff) {
				while (diff < vec[i] - i) {
					miss_cont.push_back(diff + i);
					diff++;
				}
			}
		}
		return miss_cont;
	}
	
	/* // disabled becuase it is constrained to int data type
	Array<int> FindMoreThanOneMissingElement(Array<int> arr) {
		// this procedure takes O(n) time but uses Hash Table
		Array<int> Hash(arr.max() + 1,0); // creates an array of max element from the arr and inits all to 0
		int arr_size = arr.size(),hash_size = Hash.size();
		Array<int> miss_cont;
		for (int i = 0; i < arr_size; i++) {
			Hash[arr[i]]++;
		}

		for (int i = arr.min(); i < hash_size; i++) {
			if(Hash[i] == 0) miss_cont += (i);
		}
		return miss_cont;
	}
	*/

	// returns a vector of duplicate elements in the parameter vector
	template<typename T>
	vector<T> GetDuplicates(vector<T> vec) {
		vector<T> Hash(Max(vec) + 1,0);
		vector<T> dup_cont;
		for (size_t i = 0; i < vec.size(); i++) {
			Hash[vec[i]]++;
		}

		for (size_t i = 0; i < Hash.size(); i++) {
			if (Hash[i] > 1)  dup_cont.push_back(i);
		}
		return dup_cont;
	}

//#######################################################################################################################
// Mapping Functions (Implemented in PyBasics.cpp)
/*
	This Map() function takes a function as first param and a vector as second param.

	ex: Map(Upper, names);  // assume names as a 1D vector<string>
		now the Map() function will apply the Upper() function on all the elements of vector by-reference.
		it supports all the functions that are implemented in the string manipulation section. (Just above this Section)
*/
	vector<string> Map(string(*f) (string&), vector <string>& vec);
	vector<string> Map(string(*f) (string&), const vector <string>& vec);

	/*
	Note: These cannot modify the vector by-reference as implicit/explicit type transformation is not allowed in C++
	*/
	// overloaded for Int()
	vector<int> Map(int (*f) (string), vector <string>& vec);				// returns a vector<int>
	vector<int> Map(int (*f) (string), const vector <string>& vec);			// for compatibility with Split function
	vector<int> Map(int (*f) (string), const vector <char>& vec);			// for compatibility with List function
	// overloaded for Double()
	vector<double> Map(double (*f) (string), vector <string>& vec);          // returns a vector<double>
	vector<double> Map(double (*f) (string), const vector <string>& vec);    // for compatibility with Split function
	vector<double> Map(double (*f) (string), const vector <char>& vec);      // for compatibility with List function

	// This Map() Function is overloaded specifically for Str() function.
	// This converts the values of one vector into string and returns the copy of the new vector.
	template<typename T>
	vector<string> Map(string(*f) (T), vector<T>& vec) {
		vector<string> temp;

		for (T i : vec) {
			temp.push_back((*f) (i));
		}

		return temp;
	}

	// This overloaded copy of Map function Lets you Map Str() with returns from List(), Split() and Range()
	template<typename T>
	vector<string> Map(string(*f) (T), const vector<T>& vec) {
		vector<string> temp;

		for (T i : vec) {
			temp.push_back((*f) (i));
		}

		return temp;
	}

	// universal Map() function
	template<typename T, typename U>
	vector<U> Map(U(*f)(T), vector<T> vecT) {
		vector<U> vecU;
		for (size_t i = 0; i < vecT.size(); i++) {
			vecU.push_back((*f)(vecT[i]));
		}
		return vecU;
	}

/*
	This Map() function takes a function as first param and a Array Class objects as second param.

	ex: Map(Upper, names);  // assume names as a 1D Array<string>
		now the Map() function will apply the Upper() function on all the elements of Array<string> by-reference.
		it supports all the functions that are implemented in the string manipulation section. (Just above this Section)
*/
	// overloaded for Upper(), Lower(), and all other similar String Manip. functions 
	//Array<string> Map(string(function) (string&), Array<string>& arr);
	//Array<string> Map(string(function) (string&), const Array<string>& arr);

	// overloaded for Double()
	Array<double> Map(double(function) (string), Array<string>& arr);
	Array<double> Map(double(function) (string), const Array<string>& arr);

	// overloaded for Int()
	Array<int> Map(int(function) (string), Array<string>& arr);
	Array<int> Map(int(function) (string), const Array<string>& arr);

	// overloaded for Str()
	template<typename T>
	Array<string> Map(string (function)(T), Array<T>& arr) {
		Array<string> temp;
		for (size_t i = 0; i < arr.size(); i++) {
			temp += ((function) (arr[i]));
		}
		return temp;
	}

	// This overloaded copy of Map function Lets you Map Str() with returns from SplitInArray()
	template<typename T>
	Array<string> Map(string(function)(T), const Array<T>& arr) {
		Array<T> temp = arr;
		return Map(function, temp);
	}

// various universal Map() functions
	template<typename T, typename U>
	Array<U> Map(U(function)(T), Array<T> arrT) {
		Array<U> arrU;
		for (size_t i = 0; i < arrT.size(); i++) {
			arrU += ((function)(arrT[i]));
		}
		return arrU;
	}

	template<typename T, typename U>
	Array<U> Map(U(function)(T&), Array<T> arrT) {
		Array<U> arrU;
		for (size_t i = 0; i < arrT.size(); i++) {
			arrU += ((function)(arrT[i]));
		}
		return arrU;
	}

	template<typename T>
	Array<T> Map(T(function)(T&), Array<T>& arr) {
		for (T& t: arr) {
			((function)(t));
		}
		return arr;
	}

	template<typename T>
	Array<T> Map(T(function)(T&), const Array<T>& arr) {
		for (size_t i = 0; i < arr.size(); i++) {
			((function)(arr[i]));
		}
		return arr;
	}

	/* Maps a function of return type (void) and reads takes elements by reference 
	*	Because the common convention says any function that only manipulates a single
		parameter with return type void, should take parameter by reference
	*/
	template<typename T>
	Array<T> Map(void(function)(T&), Array<T> arr) {
		for (size_t i = 0; i < arr.size(); i++) {
			(function)(arr[i]);
		}
		return arr;
	}

	Array<double> Map(double(function)(double), Array<double>& arr);
	Array<double> Map(double(function)(double), const Array<double>& arr);
	Array<long double> Map(long double(function)(long double), Array<long double>& arr);
	Array<long double> Map(long double(function)(long double), const Array<long double>& arr);

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
	These functions uses respective constructors of the types required to convert 
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

	template<typename T>
	class toArray {
		typename std::vector<T>::iterator _begin;
		typename std::vector<T>::iterator _end;
		T* _arr_begin = nullptr;
		T* _arr_end = nullptr;
	public:
		toArray(vector<T>& vec) : _begin{ vec.begin() }, _end{ vec.end() } {}
		
		template<size_t s>
		toArray(T(&_arr)[s]): _arr_begin{ std::begin(_arr) }, _arr_end{ std::end(_arr) } {}

		Array<T> operator()() {
			if (_arr_begin == nullptr) {
				return Array<T>(this->_begin, this->_end);
			}
			else {
				return Array<T>(this->_arr_begin, this->_arr_end);
			}
		}
	};
}
#endif // PYBASICS_H
