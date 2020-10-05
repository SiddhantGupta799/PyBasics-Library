# PyBasicsLibrary
This is a C++ based Library and uses the language to implement some of the basic Python Built-in functions.

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

String Manipulation Functions:

	* Upper()      : to Upper Case the whole String
	* Lower()      : to Lower Case the whole String
	* Capitalize() : to Capitalize a String
	* Reverse()    : to Reverse a String
	* Sort()       : to sort a string
	* List()       : to convert a string to vector of characters
	* Pad()        : to append a character at start and in the end of a string
	* toString()   : to convert 1D array or vector to a string.

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

This Library Also has a File Handler Class which:

* This class is a wrapper class around the fstream library.
* It handles the actual procedures of maintain a file basics like opening in a particualr mode.
* Closing when the task is done.

* overlapping one file on another (if you open another file while a file is already open
  the new one will not open, but this has been take care of in this class. It will close
  the old file and open the new one. Note: it opens the new file in the mode of the previous file.)

* supports momentary opening of files and their closing. if single line tasks needs to be performed
  like if you want to open a file and show its content in a for-loop. this can be achieved in a single line

  ex:if iam having 4 testfiles only differed by ther no. as:
		
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
	// all the basic procedures will be handled behind the scenes and you get to focus on important details.

* Even you can collect the data of all files in your database in one go by using a vector<string> 
  and load the files like the previous ex. and replace showfile() with readfile().

A Discriptive overview on PyBasics:

Something Like this is made possible.
	
	auto vec = Map(Int,List(Input("Enter a no.: ")));
	print ("The Result: ", (Double ( Input ("Enter the Sum: ") ) ) / (Int ( Input ("Enter the Total: ") ) ));
	println (names[0] + " " + names[1] + " " + names[2] + " " + Str (3) + " " + cname);
	Print(Range(-1, 9, 2), "\t");
	Map(Reverse,names);  // assume names as an Array or Vector of strings
	a in b (the python "in" operator to return a boolean value after testing presence of a in b)
	print(s * 4); (python string multiplication feature)
	An allrounder print function, though it has variants to Handle Different operations efficiently.



###########################################################
