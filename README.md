# PyBasicsLibrary
This is a C++ based Library and uses the it to implement some of the basic Python Built-in functions.

Features (Funtions) :

	* Range()      : provides a vector<double> can be used in range based for loops. with python like Syntax.
	* Input()      : provides a single line Input feature returns a string
	* Size()       : determine the size of the array, despite wherever used and in whatever context.
	* Int()        : converts a string to integer
	* Double()     : converts a string to double
	* Str()        : converts any valid datatype to a string
	* print()      : can print any no. of arguements
	* Print()      : can print 1D, 2D Arrays and Vectors
	* toVec()      : can convert an array to a vector.
	* find()       : can find an entity in a collection of same type of entities (raw array or vector)

Features (Functors):

	toVec()      : can convert an Array Class object to a vector.
	toArr()		 : can convert a vector to an Array Class object
	
- good thing about this functor approach is that it can implement a help feature that is solely for the object it is a part of.

Features (Classes):

	* A Special File Handling Class is also provided to handle basic File opening processes in 1-2 lines of code.
	  Documentation in PyBasics.cpp
	* A Special Array Class. Array class implements array's in different form. other than std::array's but similar to std::vector
	  but different from std::vector, Array class has a lot more features built-in [read internal documentation]
	  It doesn't require size as a parameter. but it has a limitation, it's size is defaulted to INT32_MAX elements.
	  It can be changed by the programmer by changing the MAX_ARRAY_CAPACITY.

Features (Namespaces):

	* This Library has two namespaces that are ____internal_print____ and ____to_string____
		> these handle operations/workings for print() and Str() so they need not be used outside this library.


String Manipulation Functions:

	* Upper()						: to Upper Case the whole String
	* Lower()						: to Lower Case the whole String
	* Capitalize()						: to Capitalize a String
	* Reverse()						: to Reverse a String
	* Sort()						: to sort a string
	* List()						: to convert a string to vector of characters
	* Title()						: to make the text 'Title'
	* Replace()						: to remove a replace a part of a string with another
	* Strip()						: trims blank spaces at extreme ends
	* RemoveRedundantSpaces()				: Reduces numerous unnecessary spaces to one
	* ReformatText()					: Reformats the text [read internal documentation]
	* Pad()							: to append a character at start and in the end of a string

Mapping Functions:

	* Map()        : can Apply any of the String Manipulations on a vector of strings, doesn't return anything
	* MapArray()   : can Apply any of the String Manipulations on an Array of Strings, doesn't return anything

Special Python features in C++:

	* An overloaded (*) operator for string multiplication.
	* An "In" operator to find a value in a 1D array or vector can 
	  be used directly in an if statement to test presence of a value in its collection list.

This Library also provides some of the fun Macros (Strictly Optional to Use), to save you 
a bit of typing.
These are defined using Macros:

	* Aliased "std::cout<<"    as "say","ask" and "show"
	* Aliased '<< " " <<'      as "with"
	* Aliased "std::cin>>"     as "listen"
	* Aliased ">>"             as "also"
	* Aliased "<<std::endl;"   as "done" and "wrap" while using them no semiclon is required

This Library Also has a File Class:

	* This class is a wrapper class around the fstream library.
	* It handles the actual procedures of maintaining file basics like opening in a particular mode.
	* Closing when the task is done.

	* overlapping one file on another (if you open another file while a file is already open
	  the new one will not open, but this has been take care of in this class. It will close
	  the old file and open the new one. Note: it opens the new file in the mode of the previous file.)

	* supports momentary opening of files and their closing. if single line tasks needs to be performed
	  like if you want to open a file and show its content in a for-loop. this can be achieved in a single line

	  ex:If Iam having 4 testfiles, only differed by their no. as:
		
		testfile0.txt
		testfile1.txt
		testfile2.txt
		testfile3.txt
		
	A name you can create. or if you can make a vector of filenames.
	you can access them as shown below:

		File file;
		for(int i = 0; i <= 3; i++){
			file.open("testfile"+Str(i)+".txt",'r').showfile();
		}

		for (int i = 0; i <= 3; i++) {
			File("testfile"+Str(i)+".txt",'r').showfile();
		}
	all the basic procedures will be handled behind the scenes and you get to focus on important details.

* You can collect the data of all files in your database in one go by using a vector<string> or Array<string>
  and load the files like the previous ex. and replace showfile() with readfile().

The Array Class is designed to behave like a vector but in a permitted range of 0 - MAX_ARRAY_CAPACITY.
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


A Discriptive overview on PyBasics:

Something Like this is made possible.
Also You can use this code for Testing the Library
	
	auto vec = Map(Int, List(Input("Enter a no.: ")));
	print("The Number that you entered has been vectorized digit by digit: ", vec);
	print("The Result: ", (Double(Input("Enter the Sum: "))) / (Int(Input("Enter the Total: "))));
	print("Range (begin = -1, end = 9, step = 2):", Range(-1, 9, 2));

	string names[]{ "phineas","ferb","candace","isabella","buford" };
	MapArray(Upper, names);
	print("Uppercased Names: ");
	print(names);
	print();

	print("Lowercased Names: ");
	MapArray(Lower, names);
	print(names);
	print();

	print("testing the presence of candace:",' ');
	("candace" In names) ? print("found her") : print("couldn't find her");
	print("Str(\"*\") * 4: ", Str("*") * 4);
