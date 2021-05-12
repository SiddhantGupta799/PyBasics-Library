#include "PyBasics.h"
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
	// Implementation of File Handler Class
	File::File(string name, File_Open_Modes mode) : name{ name }, mode{ mode }
	{
		modeSwitcher(name, mode);
	}

	void File::modeSwitcher(string name, File_Open_Modes mode) {
		switch (mode) {

		case READ:
			file.open(name, ios::in);
			break;

		case WRITE:
			file.open(name, ios::out);
			break;

		case APPEND:
			file.open(name, ios::app);
			break;

		case BINARY:
			file.open(name, ios::out | ios::binary);
			break;

		case READ_AND_WRITE:
			file.open(name, ios::in | ios::out);
			break;

		case READ_AND_APPEND:
			file.open(name, ios::in | ios::app);
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

	void File::reset_cursor() {
		file.clear();
		file.seekg(0, ios::beg);
	}

	void File::showfile() {
		reset_cursor();
		string line;
		if (openSuccess) {
			while (getline(file, line)) {
				say line wrap;
			}
		}
		else {
			cerr << "No such File or Directory" << endl;
		}
		reset_cursor();
	}

	string File::readline() {
		string line;
		if (openSuccess and getline(file, line)) {
			return line;
		}
		return eol;
	}
	
	bool File::readline(string& line) {
		if (openSuccess and getline(file, line)) {
			return true;
		}return false;
	}

	string File::readfile() {
		reset_cursor();
		string line;
		string data;
		if (openSuccess) {
			while (getline(file, line)) {
				data += line;
				data += "\n";
			}
		}
		reset_cursor();
		return data;
	}

	File::File(const File& obj) : File(obj.name, obj.mode) {}

	void File::open_new_file(string name, File_Open_Modes mode) {
		if (openSuccess) {
			close();
		}
		modeSwitcher(name,mode);
	}

	File File::open(string name, File_Open_Modes mode) {
		return File(name, mode);
	}

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

	void File::help() {
		cout << "help() is under making" << endl;
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
	string Input(string s) {
		say s;
		cin.clear();
		cin.sync();
		getline(cin, s);
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
		return find(l, Str(r));
	}

	bool find(char ch, char const* r) {
		return find(Str(ch), Str(r));
	}

//#######################################################################################################################
// TypeCasters
/*
	This Double() and Int() functions Typecasts a valid string into the respective types.

	Note: Uses the Builtin Functions stod() and stoi() respectively
	ex: Int("456") = 456
		Double("67") = 67.00
*/
	double Double(string s) {
		return stod(s);
	}

	double Double(char ch) {
		return stod(Str(ch));
	}

	double Double(double d) {
		return d;
	}

	int Int ( string s ) {
		return stoi ( s );
	}

	int Int(int i) {
		return i;
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
	namespace ____internal_print____ {
		std::ostream& ___show___(std::ostream& os) {
			return os;
		}
	}

	void print() {
		say "" wrap;
	}

	void print(const char* s) {
		cout << s << endl;
	}

//#######################################################################################################################
// Special DataTypes Printers, Note the Capitalization in calling
// @brief Because of the templates creating a linker issue most of the printers are implemented in the .hpp file itself

// 1D vector Printers
//@brief This Overloaded function for handelling Printing of vector elements of string type
	void Print (vector <string> &vec, string end ) {
		for (const string& i : vec) {
			say i << end;
		} say "" done;
	}

//@brief This Overloaded function for handelling Printing of vector elements of string type
	void Print (vector<int>& vec, string end ) {
		for (const int& i : vec ) {
			say i << end;
		} say "" done;
	}


//@brief This Overloaded function for handelling Printing of Array elements of string type
	void Print(Array<string>& arr, string end) {
		for (int i = 0; i < arr.size(); i++) {
			say arr[i] << end;
		} say "" done;
	}

//@brief This Overloaded function for handelling Printing of Array elements of string type
	void Print(Array <int>& arr, string end) {
		for (int i = 0; i < arr.size(); i++) {
			say arr[i] << end;
		} say "" done;
	}

//#######################################################################################################################
// This the map function just like Python
// also works like that but on vectors and Array Class objects
// the Upper, Lower, Capitalize and Reverse function are acceptable by this one
// to extend capabilities the Int, Double and Str are also applicable with this function.
// for extended mappings (Int, Double and Str) the Map functions returns a vector after applying the changes
// MapArray function is specifically for the string Arrays Mapping and doesn't extend capabilities for different types of Raw - Arrays
	vector<string> Map (string (*f) (string&), vector<string>&vec) {
		for (string & ar : vec ) {
			ar = (*f) (ar);
		}
		return vec;
	}

	vector<string> Map(string(*f) (string&), const vector <string>& vec) {
		vector<string> v = vec;
		return Map(*f,v);
	}

	vector<int> Map (int (*f) (string), vector <string> &vec) {
		vector <int> temp;

		for (string ar : vec) {
			temp.push_back ( (*f) (ar) );
		}

		return temp;
	}

	vector<int> Map(int (*f) (string),const vector <string>& vec) {
		vector <string> v = vec ;
		return Map(*f,v);
	}

	vector<int> Map(int (*f) (string), const vector <char>& vec) {
		vector <int> temp;

		for (char ar : vec) {
			temp.push_back(Int(ar));
		}

		return temp;
	}

	vector<double> Map (double (*f) (string), vector <string>& vec) {
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

	Array<string> Map(string (function)(string&), Array<string>& arr) {
		for (size_t i = 0; i < Len(arr); i++) {
			function(arr[i]);
		}
		return arr;
	}
	
	Array<string> Map(string (function)(string&),const Array<string>& arr) {
		Array<string> ar = arr;
		return Map(function,ar);
	}

	Array<int> Map(int (function)(string), Array<string>& arr) {
		Array<int> intArr;
		for (size_t i = 0; i < Len(arr); i++) {
			intArr.append((function)(arr[i]));
		}
		return intArr;
	}

	Array<int> Map(int(function) (string),const Array<string>& arr) {
		Array<string> ar = arr;
		return Map(function, ar);
	}

	Array<double> Map(double(function) (string), Array<string>& arr) {
		Array<double> intArr;
		for (size_t i = 0; i < Len(arr); i++) {
			intArr.append((function)(arr[i]));
		}
		return intArr;
	}

	Array<double> Map(double(function) (string),const Array<string>& arr) {
		Array<string> ar = arr;
		return Map(function, ar);
	}

	Array<double> Map(double(function)(double), Array<double>& arr) {
		for (double& d : arr) {
			d = function(d);
		}
		return arr;
	}

	Array<double> Map(double(function)(double), const Array<double>& arr) {
		Array<double> ar = arr;
		return Map(function, ar);
	}

	Array<long double> Map(long double(function)(long double), Array<long double>& arr) {
		for (long double& d : arr) {
			d = function(d);
		}
		return arr;
	}

	Array<long double> Map(long double(function)(long double), const Array<long double>& arr) {
		Array<long double> ar = arr;
		return Map(function,ar);
	}

//#######################################################################################################################
// String Manipulation functions

//#######################################################################################################################
	// helper functions for ReformatText
	void __swap(char& a, char& b) {
		char temp = a;
		a = b;
		b = temp;
	}

	// Helper Functions for ReformatText
	void __the_ones_that_are_followed_by_a_space(
		deque<char>& s,     // the deque that gets edited
		size_t i,           // index of editing
		char prvious_char,  // character preceding the position
		char next_char)     // character succeeding the position
	{
		/*
		This one rectifies the improper placing of
		'.' = period
		',' = comma
		':' = colon
		')' = closing parenthesis
		']' = closing square brackets
		'}' = closing curly braces
		';' = semi colon
		'?' = question mark
		*/
		// correct for of the above entities -> '<word><entity> <word>'
		// example: ... important, how ...
		//          -------------^ here it is

		if (prvious_char == ' ' and next_char == ' ') {
			// case: 'important , to'
			s.erase(s.begin() + i - 1, s.begin() + i);  // deletes the unnecessary space
		}
		else if (prvious_char == ' ' and next_char != ' ') {
			// case: 'important ,to' 
			__swap(s[i - 1], s[i]);   // swaps the places
		}
		else {
			// case: 'important,to' 
			s.insert(s.begin() + i, ' ');   // will be good to insert a space after comma
		}
	}

	// helper for ReformatText
	void __the_ones_that_are_preceded_by_a_space(
		deque<char>& s,     // the deque that gets edited
		size_t i,           // index of editing
		char prvious_char,  // character preceding the position
		char next_char)     // character succeeding the position
	{
		/*
		This one rectifies the improper placing of
		'(' = opening paranethesis
		'[' = opening square brackets
		'{' = opening curly braces
		*/
		// correct for of the above entities -> '<word> <entity><word>'
		// example: ... important (how ...
		//          --------------^ here it is
		if (prvious_char != ' ' and next_char == ' ') {
			// case: 'see( '
			__swap(s[i], s[i + 1]);
		}
		else if (prvious_char != ' ' and next_char != ' ') {
			// case: 'see('
			s.insert(s.begin() + i, ' ');   //  will be good to insert a space before opening parenthesis
		}
		else if (prvious_char == ' ' and next_char == ' ') {
			// case: 'see ( '
			s.erase(s.begin() + i + 1, s.begin() + i + 2);
		}
	}

	// helper for ReformatText
	void __the_ones_that_need_padding(
		deque<char>& s,     // the deque that gets edited
		size_t i,           // index of editing
		char pch,  // character preceding the position
		char fch)     // character succeeding the position 
	{
		/*
		This one rectifies the improper placing of
		'+' = Addition
		'-' = Subtraction
		'*' = Multiplication
		'/' = Divison
		'=' = Equals
		*/
		// correct for of the above entities -> '<word> <entity> <word>'
		// example: ... 3 + 4 ...
		//          ------^ here it is
		// but if its quoted like this -> '+' any improper spacings will be removed
		char ppch = s[i - 2], ffch = s[i + 2];

		if (ppch != ' ' and pch == ' ' and fch == ' ' and ffch != ' ') {
			// case: 3 + 4 -> 3 + 4 
			// no change
		}
		else if (pch != ' ' and fch == ' ' and ffch != ' ') {
			// case: 3+ 4 -> 3 + 4 
			s.insert(s.begin() + i, ' ');
		}
		else if (pch == ' ' and fch != ' ') {
			// case: 3 +4 -> 3 + 4 
			s.insert(s.begin() + i + 1, ' ');
		}
		else if (pch != ' ' and fch != ' ') {
			// case: 3+4 -> 3 + 4
			s.insert(s.begin() + i, ' ');
			s.insert(s.begin() + i + 2, ' ');
		}
	}

	int single_quote_count = 0;		// for the __i_handle_quotes()
	int double_quote_count = 0;		// for the __i_handle_quotes()

	// helper for ReformatText
	void __i_handle_quotes(
		deque<char>& s,     // the deque that gets edited
		size_t& i,				// index of editing
		char pch,			// character preceding the position
		char fch)			// character succeeding the position
	{
		// recognizing which quote we are working with
		char ch = s[i];
		int quote_count = 8;
		if (ch == '\'') {
			// single quote
			// cout << "single quote encountered with status: " << single_quote_count << endl;
			if (single_quote_count == 0) {
				single_quote_count = 1;
				quote_count = 0;	// opening quote
			}
			else {
				single_quote_count = 0;
				quote_count = 1;	// closing quote
			}
		}
		else if (ch == '"') {
			// double quote
			// cout << "double quote encountered with status: " << double_quote_count << endl;
			if (double_quote_count == 0) {
				double_quote_count = 1;
				quote_count = 0;
			}
			else {
				double_quote_count = 0;
				quote_count = 1;
			}
		}

		if (quote_count == 0) {
			/* encountered opening quote */
			if (pch == ' ' and fch != ' ') {
				// case: framed "response -> framed "response
				// needs no change
				i++;
			}
			else if ((pch == '(' or pch == '[' or pch == '{') and fch != ' ') {
				// case: framed ("response -> framed ("response
				// because by now the bracket has been handled
				// needs no change
				i++;
			}
			else if ((pch == '(' or pch == '[' or pch == '{') and fch == ' ') {
				// case: framed ( "response -> framed ("response
				s.erase(s.begin() + i + 1, s.begin() + i + 2);
				i++;
			}
			else if (pch != ' ' and fch == ' ') {
				// case: framed" response -> framed "response
				__swap(s[i], s[i + 1]);
				i += 2;
				// since the next char will be a double inverted quote, and to prevent 
				// the code from assumming that, as if it had found the closing quote we 
				// make it flip 2 elements
			}
			else if (pch != ' ' and fch != ' ') {
				// case: framed"response -> framed "response
				s.insert(s.begin() + i, ' ');
				i += 2;
				// same reason as above
			}
			else {
				// case: framed " response -> framed "response
				s.erase(s.begin() + i + 1, s.begin() + i + 2);
				i++;
			}
		}
		else if (quote_count == 1) {
			/* encountered closing quote */
			if (pch == ' ' and fch != ' ') {
				// case: crane "trend -> crane" trend
				__swap(s[i - 1], s[i]);
			}
			else if (pch != ' ' and (fch == ')' or fch == ']' or fch == '}')) {
				// case: crane")trend -> crane")trend
				// the bracket will be handled afterwards
				// needs no change
			}
			else if (pch != ' ' and fch == ' ') {
				// case: crane" trend -> crane" trend
				// needs no change
			}
			else if (pch != ' ' and fch != ' ') {
				// case: crane"trend -> crane" trend
				s.insert(s.begin() + i + 1, ' ');
			}
			else {
				// case: crane " trend -> crane" trend
				s.erase(s.begin() + i - 1, s.begin() + i);
			}
			i++;
		}
	}

	// helper for FindAll
	void __get_char_positions(string& str, char& ch, Array<int>& char_index_register) {
		int i = 0;
		for (char& c : str) {
			if (ch == c) {
				char_index_register += i;
			}
			i++;
		}
	}

	// helper for FindAll
	// time complexity: O(n)
	// n: size of s
	bool __verify_presence_according_to_register(string& str, string& s, int& begin_position) {
		int len = s.size();
		int last_position = begin_position + len;
		int j = 0;
		for (int i = begin_position; i < last_position; i++) {
			if (str[i] != s[j]) {
				return false;
			}
			j++;
		}
		return true;
	}
	// End of Helper Functions
//#######################################################################################################################
// Actual String Manipulation Tools
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

	string Capitalize (string& s) {
		Lower(s);
		s[0] = std::toupper(s[0]);
		return s;
	}

	string HapHazard(string& s) {
		int size = s.size();
		Lower(s);
		srand((size_t)time(0));
		int id = 0;
		int len = rand() % 200;
		for (int i = 0; i < len; i++) {
			id = (rand() % size);

			id % 2 == 0 ? s[id] = toupper(s[id]) : s[id] = tolower(s[id]);
		}
		return s;
	}

	string Reverse (string &s) {
		size_t f = s.size();

		for (size_t i = 0; i < f / 2; i++) {
			Swap(s[i], s[f - i - 1]);
		}

		return s;
	}

	string Sort(string& s) {
		return quickSort(s);
	}

	string Title(string& s) {
		Capitalize(s);
		for (size_t i = 0; i < s.size() - 1; ++i) {
			if (s[i] == ' ') {
				s[i + 1] = std::toupper(s[i + 1]);
			}
			if (s[i] == '\'' or s[i] == '\"') {
				// this is here so the function does work on single or double quotes
				if (s[i - 1] == ' ') {
					s[i + 1] = std::toupper(s[i + 1]);
				}
			}
		}
		return s;
	}

	/*
	Trims unnecessary spaces from the extreme ends.
	Time Complexity: O(n)
	*/
	string Strip(string& s) {
		int begining_spaces = 0, end_spaces = 0;
		int size = s.size();

		// counting spaces in the begining
		for (int i = 0; i < size; i++) {
			if (s[i] == ' ')
				begining_spaces++;
			else
				break;
		}
		// counting spaces from the end
		for (int i = 0; i < size; i++) {
			if (s[size - i - 1] == ' ')
				end_spaces++;
			else
				break;
		}

		// creating a buffer
		string str;
		for (int i = begining_spaces; i < size - end_spaces; i += 1) {
			str += s[i];
		}

		// clearing the old string
		s.erase();

		// moving the buffer to original string
		s = std::move(str);
		return s;
	}

	/*
	Removes redundant spaces between the words of a string.
	Time Complexity: O(n)
	*/
	string RemoveRedundantSpaces(string& s) {
		string str_buffer;
		int space_count = 0;
		for (char ch : s) {
			if (ch == ' ' and space_count == 0) {
				str_buffer.push_back(ch);
				space_count = 1;
			}
			else if (ch != ' ') {
				str_buffer.push_back(ch);
				space_count = 0;
			}
		}
		s.erase();
		s = std::move(str_buffer);
		return s;
	}

	string ReformatText(string& s) {
		// the editting format is inspired from Microsoft Word
		/**
		* Reformatting Rules that are being followed:
		*	- a space after commas, periods, colons, semicolons, question marks,
			  exclamation marks opening brackets and none before them
		*	- a space before closing brackets
		*	- unnecesaary spaces removed.
		*/
		/*
		* What it cannot do:
				This function doesn't balance quotation marks or any types of brackets.
				It just knows where a particular punctuation is put.
				Also it doesn't correct grammar.
		*/

		// removing unnecessary spaces between words and extreme ends
		RemoveRedundantSpaces(s);
		Strip(s);

		/* pre-editting touchs
		*	- this includes if the very begining of the text is a quotation.
		*/
		if (s[0] == '"') {
			// capitalizes the first letter since its the very begining of the text.
			s[1] = toupper(s[1]);
		}
		s[0] = toupper(s[0]);

		// putting insertion and deletion operations in the hand of deque as these operations are constant time
		deque<char> buffer;

		// extra padding in beginning sides
		buffer.push_back(' ');
		buffer.push_back(' ');

		// filling the buffer with actual string
		for (char ch : s) {
			buffer.push_back(ch);
		}

		// extra padding in end sides
		buffer.push_back(' ');
		buffer.push_back(' ');

		// clearing memory of string for effective handling of the process
		s.clear();

		// actual editing
		char
			pch,	// previous character
			ch,		// current character
			fch;	// next character

		size_t i = 2;
		for (; i < buffer.size() - 2;) {
			// not going to be out of bound
			pch = buffer[i - 1],
				ch = buffer[i],
				fch = buffer[i + 1];

			// for debug info
			// cout << "i:" << i << " " << pch << ch << fch << endl;

			if (ch == ',' or
				ch == '.' or
				ch == ':' or
				ch == ';' or
				ch == '?' or
				ch == '!' or
				ch == ')' or
				ch == ']' or
				ch == '}')
			{
				__the_ones_that_are_followed_by_a_space(buffer, i, pch, fch);
				if (ch == '.') {
					// to capitalize the first word
					buffer[i + 1] = std::toupper(buffer[i + 1]);
				}
				i++;
			}

			else if (ch == '(' or ch == '[' or ch == '{')
			{
				__the_ones_that_are_preceded_by_a_space(buffer, i, pch, fch);
				i++;
			}

			else if (ch == '+' or ch == '-' or ch == '*' or ch == '/' or ch == '=')
			{
				if (
					(pch == '\'' or pch == '"') or
					(fch == '\'' or fch == '"')
					)
				{
					// any quoted symbol is to be prevented from being handled here
				}
				else {
					__the_ones_that_need_padding(buffer, i, pch, fch);
				}
				i++;
			}

			else if (ch == '\"' or ch == '\'')
			{
				if (ch == '\'' and fch == 's' and pch != ' ') {
					// an apostrophe
					if (buffer[i + 2] != ' ') {
						buffer.insert(buffer.begin() + i + 2, ' ');
						i += 2;
					}
					else {
						i++;
					}
				}
				else if (ch == '\'' and fch == 't' and pch == 'n') {
					// the case -> isn't, where "not" is shortened to "n't"
					if (buffer[i + 2] != ' ') {
						buffer.insert(buffer.begin() + i + 2, ' ');
						i += 2;
					}
					else {
						i++;
					}
				}
				else {
					__i_handle_quotes(buffer, i, pch, fch);
				}
			}

			else {
				i++;
			}
		}

		// removing extra padding from the begining
		buffer.pop_front();
		buffer.pop_front();

		// removing extra padding from the end
		buffer.pop_back();
		buffer.pop_back();

		// filling the string from the buffer
		// this operation is of O(n) time complexity as it is only appending a character at a time
		for (char ch : buffer) {
			s += ch;
		}

		// clearing all the buffer
		buffer.clear();

		return s;

		/*
		After notes
			Briefly explaining:
				We are playing with a deque<char> and making changes to it while still looping through it.
				this can result in pointer invalidation if you use the 'for each' loop.
				The conditions for the looping begins from 2 to size() - 2, since, we are making changes
				to the string we do need to query its size everytime we enter in loop. since the size
				varies we need to do check it through size();

				we are also looking at the one preceding character and one succeeding character, so we cannot do
				this by reference as it will only invite more debugging problems.

				most of the workings in this function are too weird to be understood by us. even i was amazed
				after looking at how it actually did what it did. but after giving lot of time debugging it
				all the outputs look appreciable.

		*/
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

	string Title(string&& s) {
		return Title(s);
	}

	string Strip(string&& s) {
		return Strip(s);
	}

	string RemoveRedundantSpaces(string&& s) {
		return RemoveRedundantSpaces(s);
	}

	string ReformatText(string&& s) {
		return ReformatText(s);
	}

	// Finds all the occurrences of s in str works linearly
	// time complexity: O(n)
	Array<int> FindAll(string& str, string s) {
		Array<int> char_index_register;

		if ((str.size() <= s.size()) and (str.size() <= 1)) {
			return char_index_register;
		}

		// time complexity: O(n)
		// n: str.size()
		__get_char_positions(str, s[0], char_index_register);

		// time complexity: O(n x m)	// can be ignored as it doesn't traverse the whole input
		// n: size of char_index_register
		// m: s.size()
		int temp = 0;
		for (int i : char_index_register) {
			if (__verify_presence_according_to_register(str, s, i)) {
				char_index_register[temp++] = i;
			}
		}

		// removal is linear
		char_index_register.erase(temp);
		return char_index_register;
	}

	// Replaces all the occurrences of _old in str with _new
	// time complexity: O(n)
	string Replace(string& str, string _old, string _new) {
		Array<int> positions_register = FindAll(str, _old);
		int difference = _new.size() - _old.size();

		if (difference == 0) {
			// if size is same then just reinitialize with new string
			// pass
		}

		else if (difference > 0) {
			// inserting blank spaces in string equal to difference
			// insertions only occur at positions found so not a lot of insertions will be made
			// time complexity: O(n x m)
			// n: insertion
			// m: size of positions_register (very less, only the no. of matches found)
			int no_of_insertions = 0;
			for (int& i : positions_register) {
				i = (i + (no_of_insertions * difference));  // updating the positions_register according to the blanks inserted
				str.insert(i, " ", difference);
				no_of_insertions++;
			}
		}

		else if (difference < 0) {
			// deletion of abs(difference)
			// deletions only occur at positions found so not a lot of deletions will be made
			// time complexity: O(n x m)
			// n: erasing
			// m: size of positions_register (very less, only the no. of matches found)
			int no_of_deletion = 0;
			for (int& i : positions_register) {
				i = (i + (no_of_deletion * difference));  // updating the positions_register according to the blanks deleted
				str.erase(i, abs(difference));
				no_of_deletion++;
			}
		}

		// time complexity: O(n x m)
		// n: size of positions_register
		// m: size of _new
		for (size_t i : positions_register) {
			for (size_t j = 0; j < _new.size(); j++) {
				str[j + i] = _new[j];
			}
		}

		return str;
	}

	vector<string> Split(string str, char separator, bool considerSpacesToo) {
		str = Strip(str);
		str = RemoveRedundantSpaces(str);
		string temp;
		vector<string> vec;
		if (considerSpacesToo) {
			str = Replace(str, " ", Str(separator));
		}
		str += separator;
		for (char ch : str) {
			if (ch == separator and (temp.size() != 0)) {
				vec.push_back(temp);
				temp.clear();
			}
			else {
				if (ch != separator)
					temp += ch;
			}
		}
		return vec;
	}

	vector<string> Split(string s, string separator) {
		char ch;
		if (separator.size() == 1) {
			ch = separator[0];
		}
		else {
			s = Replace(s, separator, "#");
			ch = '#';
		}
		return Split(s, ch, false);
	}

	Array<string> SplitInArray(string str, char separator, bool considerSpacesToo) {
		string temp;
		Array<string> arr;
		if (considerSpacesToo) {
			str = Replace(str, " ", Str(separator));
		}
		str += separator;
		for (char ch : str) {
			if (ch == separator) {
				arr.append(temp);
				temp.clear();
			}
			else {
				if (ch != separator)
					temp += ch;
			}
		}
		return arr;
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

	string quickSort(string s) {
		if (s.size() <= 1) {
			return s;
		}
		else {
			char pivot = s[s.size() / 2];
			string left = "";
			string middle = "";
			string right = "";
			for (char ch : s) {
				if (ch < pivot) {
					left += ch;
				}
				else if (ch == pivot) {
					middle += ch;
				}
				else {
					right += ch;
				}
			}
			return quickSort(left) + middle + quickSort(right);
		}
	}

// Basic Utility Functions
	string Sum(vector<string>& vec) {
		string s = "";
		for (string& ch : vec) {
			s += ch;
		}
		return s;
	}

	string Sum(const vector<string>& vec) {
		vector <string> v = vec;
		return Sum(v);
	}

	string Sum(Array<string>& arr) {
		string sum = "";
		for (size_t i = 0; i < Len(arr); i++)
			sum += arr[i];
		return sum;
	}

	string Sum(const Array<string>& arr) {
		Array<string> ar = arr;
		return Sum(ar);
	}

	namespace ____to_string____ {
		string ___notation_braces___(string s, char symbol_left, char symbol_right) {
			return symbol_left + s + symbol_right;
		}

		string ___padder___(string s) {
			return ' ' + s + ' ';
		}
	}

	vector<int> make_int(vector<vector<int>>& vec) {
		vector<int> nums;
		for (vector<int>& v : vec) {
			int temp = 0;
			for (int n : v) {
				temp = temp * 10 + n;
			}
			nums.push_back(temp);
		}
		return nums;
	}

	string toVec:: help(){ return "toVec: Converts Raw Array or Array Class Objects to std::vector";}
	string toArr:: help() { return "toArr: Converts Raw Array or std::vector to Array Class Objects"; }
}
//#######################################################################################################################