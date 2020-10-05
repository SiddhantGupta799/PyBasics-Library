#include "PyBasics.hpp"
/*
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
*/
namespace Py {
// =============================================== File Handler Class: =============================================== 
// Implementation of File Handler Class
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
	if iam having 4 testfiles only differed by there no. as:
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
*/
	File::File(string name, char mode) : name{ name }, mode{ mode }
	{
		modeSwitcher(name, mode);
	}

	void File::modeSwitcher(string name, char mode) {
		switch (mode) {
		case 'r':
			file.open(name, ios::in);
			break;
		case 'w':
			file.open(name, ios::out);
			break;
		case 'o':
			file.open(name, ios::in | ios::out);
			break;
		case 'b':
			file.open(name, ios::out | ios::binary);
			break;
		case 'a':
			file.open(name, ios::app);
			break;
		}

		if (file) {
			//say "file opened" wrap;
			openSuccess = true;
		}
		else {
			//say "error" wrap;
			openSuccess = false;
		}
	}

	void File::reset() {
		file.clear();
		file.seekg(0, ios::beg);
	}

	void File::showfile() {
		reset();
		string line;
		if (openSuccess) {
			while (getline(file, line)) {
				say line wrap;
			}
		}
		else {
			cerr << "No such File or Directory" << endl;
		}
		reset();
	}

	string File::readfile() {
		reset();
		string line;
		string data;
		if (openSuccess) {
			while (getline(file, line)) {
				data += line;
			}
		}
		reset();
		return data;
	}

	File::File(const File& obj) : File(obj.name, obj.mode) {}

	// opens the new file in the previous set mode
	void File::open(string name) {
		if (openSuccess) {
			close();
		}
		modeSwitcher(name, this->mode);
	}

	// Opens a File for momentary operations.
	// Returns the File so that it can be chained with readfile() or showfile()
	File File::open(string name, char mode) {
		return File(name, mode);
	}
	/*
	This open function is made to do the task of reading or showing the whole file 
	in a single line.
	readfile() returns the string containing the file data
	showfile() diplays the contents of the file.
	*/

	// in making
	//void File::writefile(){}

	void File::close() {
		file.close();
		openSuccess = false;
	}


	File :: ~File() {
		if (openSuccess) {
			//say "file closed" wrap;
			file.close();
		}
	}


// =============================================== Functions: =============================================== 


// Their Implementations
//#######################################################################################################################
// Input
/**
Single Line Input function. Can be used hand in hand with the Typecasters,
for Integer or Double Value inputs.

ex: int i = Int(Input("Enter an Integer.: "));
	double d = Double(Input("Enter a Float/Double.: "));
*/

	string Input ( string s ) {
		say s ;
		cin.clear();
		cin.sync();
		getline ( cin, s );
		return s;
	}

//#######################################################################################################################
// Python String multiplier.
/*
This operator works on l-values.
ex:
	string sym = " * ";
	std::cout << (((sym * 4) + "\n") * 4) << std::endl;  // prints a 4x4 square
	now sym can be used in this type of construct.
*/
	string operator* (std::string str, int times) {
		string newstr;
		for (; times > 0; times--) {
			newstr = newstr + str;
		}
		return newstr;
	}

//#######################################################################################################################
// Find Functions for "In" operator to look for a string in string or a char const* in a string
	bool find(string l, string r) {
		if (r.find(l) <= r.size()) {
			return true;
		}return false;
	}

	bool find(char const* l, string r) {
		if (r.find(l) <= r.size()) {
			return true;
		}return false;
	}

	bool find(char const* l, char const* r) {
		return find(l,Str(r));
	}

	bool find(char l, char const* r) {
		return find(Str(l), Str(r));
	}

//#######################################################################################################################
// TypeCasters
/*
This Double() and Int() functions Typecasts a valid string into the respective types.

Note: Uses the Builtin Functions stod() and stoi() respectively
ex: Int("456") = 456
    Double("67") = 67.00
*/
	double Double ( string s ) {
		return stod ( s );
	}

	double Double(char ch) {
		return stod(Str(ch));
	}

	int Int ( string s ) {
		return stoi ( s );
	}

	// This overload returns a integer if the character was an integer ex: '5' it will return 5
	// if passed any other character it will implicitly return the integer or ascii value of charater
	int Int(char ch) {
		int num = ch - 48;
		if((num) >= 0 && (num) <= 9)
			return (num);
		return ch;
	}

	int Int(double d) {
		return (int) d;
	}

	string Str(string& s) {
		return s;
	}

	string Str(char ch) {
		string s = "";
		s += ch;
		return s;
	}

	string Str(char const* str) {
		string s = "";
		s += str;
		return s;
	}

//#######################################################################################################################
// For Generating list of numbers as vector 
/*
This function generates a range of numbers according to the user.
If provided a single parameter then list generates from 0 to that number with a step of 1.
If provided two parameters then list generated begins from first param to the last param with a step of one.
If provided all three then list generated begins from first param two the second param with a step of third param.

Note: it by default provides a vector of doubles, but it can be implicitly typecasted to int.
*/
	
	vector <double> Range ( double end ) {
		return Range ( 0.0, end, 1.0 ) ;
	}

	vector <double> Range ( double begin, double end ) {
		return Range ( begin, end, 1.0 ) ;
	}

	vector <int> Range(int end) {
		return Range(0, end, 1);
	}

	vector <int> Range(int begin, int end) {
		return Range(begin, end, 1);
	}

//#######################################################################################################################
// Printer
	namespace print_container {
		std::ostream& Show(std::ostream& os) {
			return os;
		}
	}

	void print() {
		say "" wrap;
	}
//#######################################################################################################################
// Special DataTypes Printers, Note the Capitalization in calling
// @brief Because of the templates creating a linker issue most of the printers are implemented in the .hpp file itself

// 1D vector Printers
//@brief This Overloaded function for handelling Printing of vector elements of string type
	void Print (vector <string> &vec, string end ) {
		for (const string& i : vec) {
			say i with end;
		} say "" done;
	}
//@brief This Overloaded function for handelling Printing of vector elements of string type
	void Print (vector <int> &vec, string end ) {
		for (const int& i : vec ) {
			say i with end;
		} say "" done;
	}

//#######################################################################################################################
// This the map function just like Python
// also works like that but on vectors
// the Upper, Lower, Capitalize and Reverse function are acceptable by this one
// to extend capabilities the Int, Double and Str are also applicable with this function.
// for extended mappings (Int, Double and Str) the Map functions returns a vector after applying the changes
// MapArray function is specifically for the string Arrays Mapping and doesn't extend capabilities for different types of Arrays
	void Map (string (*f) (string&), vector <string> &vec) {
		for (string & ar : vec ) {
			ar = (*f) (ar);
		}
	}

	vector<int> Map (int (*f) (string), vector <string> &vec) {
		vector <int> temp;

		for (string ar : vec) {
			temp.push_back ( (*f) (ar) );
		}

		return temp;
	}

	vector<int> Map(int (*f) (string),const vector <string>& vec) {
		vector <int> temp;

		for (string ar : vec) {
			temp.push_back((*f) (ar));
		}

		return temp;
	}

	vector<int> Map(int (*f) (string), const vector <char>& vec) {
		vector <int> temp;

		for (char ar : vec) {
			temp.push_back(Int(ar));
		}

		return temp;
	}

	vector<double> Map (double (*f) (string), vector <string> &vec) {
		vector <double> temp;

		for (string ar : vec) {
			temp.push_back ( (*f) (ar) );
		}

		return temp;
	}

	vector<double> Map(double (*f) (string),const vector <string>& vec) {
		vector <double> temp;

		for (string ar : vec) {
			temp.push_back((*f) (ar));
		}

		return temp;
	}

	vector<double> Map(double (*f) (string), const vector <char>& vec) {
		vector <double> temp;

		for (char ar : vec) {
			temp.push_back((*f) (Str(ar)));
		}

		return temp;
	}

//#######################################################################################################################
// String Manipulation functions

	// l-value optimization
	string Upper (string &s) {
		for (size_t i = 0; i < s.size(); i++) {
			s[i] = std::toupper (s[i]);
		}

		return s;
	}

	string Lower (string &s) {
		for (size_t i = 0; i < s.size(); i++) {
			s[i] = std::tolower (s[i]);
		}

		return s;
	}

	string Capitalize (string &s) {
		s[0] = std::toupper (s[0]);
		return s;
	}

	string Reverse (string &s) {
		char temp;
		size_t f = s.size();

		for (size_t i = 0; i < f / 2; i++) {
			temp = s[i];
			s[i] = s[f - i - 1];
			s[f - i - 1] = temp;
		}

		return s;
	}

	string Sort(string& s) {
		for (size_t i = 0; i < s.size(); i++) {
			for (size_t j = 0; j < s.size() - 1; j++) {
				if (s[j] >= s[j + 1]) {
					swap(s[j], s[j + 1]);
				}
			}
		}
		return s;
	}


	// r-value optimization
	string Upper(string&& s) {
		return Upper(s);
	}

	string Lower(string&& s) {
		return Lower(s);
	}

	string Capitalize(string&& s) {
		return Capitalize(s);
	}

	string Reverse(string&& s) {
		return Reverse(s);
	}

	string Sort(string&& s) {
		return Sort(s);
	}

	vector<string> Split(char const* str, char separator) {
		return Split(Str(str),separator);
	}

	vector<string> Split(string str, char separator) {
		str += ' ';
		string temp;
		vector<string> vec;
		for (size_t i = 0; str[i] != '\0'; i++) {
			if (str[i] == separator || str[i] == ' ') {
				if (!temp.empty()) {
					vec.push_back(temp);
				}
				temp.clear();
			}
			else {
				temp += str[i];
			}
		}
		return vec;
	}

	vector<char> List(char const* str) {
		return List(Str(str));
	}

	vector<char> List(string s) {
		vector<char> chars;
		for (char ch : s) {
			chars.push_back(ch);
		}
		return chars;
	}

	string Pad(char const* str, string ch) {
		string s = "";
		s = s + ch + str + ch;
		return s;
	}

	string Pad(char str, string ch) {
		string s = "";
		s = s + ch + str + ch;
		return s;
	}

	string Pad(string s, string ch) {
		s = ch + s + ch;
		return s;
	}
}
//#######################################################################################################################
