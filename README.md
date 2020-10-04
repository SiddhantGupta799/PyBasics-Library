# PyBasicsLibrary
This is a C++ based Library and uses the language to implement some of the basic Python Built-in functions.

Features (Funtions) :
Range()      : provides a vector<double> can be used in range based for loops. with python like Syntax.
Input()      : provides a single line Input feature returns a string
Size()       : determine the size of the array, despite wherever used and in whatever context.
Int()        : converts a string to integer
Double()     : converts a string to double
Str()        : converts any valid datatype to a string
print()      : can print any no. of arguements
Print()      : can print 1D, 2D Arrays and Vectors
toVec()      : can convert an array to a vector.
find()       : can find an entity in a collection of same type of entities (raw array or vector)

 -- String Manipulation Functions --
Upper()      : to Upper Case the whole String
Lower()      : to Lower Case the whole String
Capitalize() : to Capitalize a String
Reverse()    : to Reverse a String
Sort()       : to sort a string
List()       : to convert a string to vector of characters
Pad()        : to append a character at start and in the end of a string
toString()   : to convert 1D array or vector to a string.

  -- Mapping Functions -- 
Map()        : can Apply any of the String Manipulations on a vector of strings, doesn't return anything
MapArray()   : can Apply any of the String Manipulations on an Array of Strings, doesn't return anything

Special Python features in C++
	- An overloaded (*) operator for string multiplication.
	- An "In" operator to find a value in a 1D array or vector can 
	  be used directly in an if statement to test presence of a value in its collection list.


###########################################################
A Discriptive overview on PyBasics:

Something Like this is made possible.
	
	* auto vec = Map(Int,List(Input("Enter a no.: ")));
	* print ("The Result: ", (Double ( Input ("Enter the Sum: ") ) ) / (Int ( Input ("Enter the Total: ") ) ));
	* println (names[0] + " " + names[1] + " " + names[2] + " " + Str (3) + " " + cname);
	* Print(Range(-1, 9, 2), "\t");
	* Map(Reverse,names);  // assume names as an Array or Vector of strings
	* a in b (the python "in" operator to return a boolean value after testing presence of a in b)
	* print(s * 4); (python string multiplication feature)
	* An allrounder print function, though it has variants to Handle Different operations efficiently.

This Library also provides some of the fun Macros (Strictly Optional to Use), to save you 
a bit of typing.
These are defined using Macros
Aliased "std::cout<<"    as "say","ask" and "show"
Aliased '<< " " <<'      as "with"
Aliased "std::cin>>"     as "listen"
Aliased ">>"             as "also"
Aliased "<<std::endl;"   as "done" and "wrap" while using them no semiclon is required
###########################################################
