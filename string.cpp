
#include <cstring>
#include <iostream>
using namespace std;
#include "string.h"
#include <cstddef>

//constuctors
String::String(const char* str) : strg(str) { //inialization list
	//cout << "String created" << endl;
}

String::String(const String& other): strg(other.strg) {
	//cout << "String created using copy" << endl;
}
//operators
GenericString& String::operator=(const char *str) {
	this->strg = str;
	return *this; //this is the way of returning refernce to this
}

bool String::operator==(const GenericString &other) const {
	const String* otherString = dynamic_cast<const String*>(&other);
	if (otherString->strg.compare(this->strg)) {
		return false;
	}
	return true;
}

bool String::operator==(const char *other) const {
	if (this->strg.compare(other)) {
		return false;
	}
	return true;
}

//other functions

StringArray String::split(const char *delimiters) const {
	StringArray substrs; //dont use this if arrlen is not member anymore: = new StringArray(); cause dont need constructor
	char *strgTemp = new char[strlen(this->strg.data()) + 1];
	strcpy(strgTemp, this->strg.data());
	//need to convert const char* strg to (ordinary) char* strg?
	char* token = strtok(strgTemp, delimiters);
	while (token != nullptr) {
		//keep setting String array
		substrs.addSubStr(token);
		//substrs.subStrVec.push_back(token);
		token = strtok(nullptr, delimiters);
	}
	delete[] strgTemp;
	return substrs;
}

GenericString& String::trim() {
	//1. 'locating' first white spaces
	std::size_t first = this->strg.find_first_not_of(" ");
	this->strg.erase(0, first);
	//2. 'locating' last white spaces
	std::size_t last = this->strg.find_last_not_of(" ");
	this->strg.erase(last+1);

	return *this;
}
//1. non const ver.
String& String::as_string() {
	String* str = dynamic_cast<String*>(this); //converts safely
	return *str;
}
//2. const ver.
const String& String::as_string() const {
	const String* str = dynamic_cast<const String*>(this); //converts safely
	return *str;
}


int String::to_integer() const {
	const char* str = this->strg.data();
	return atoi(str);
}

String::~String() {
	//cout << "String destructed" << endl;
}

void String::printMethod() {
	//cout << "strg member is: "<< strg << endl;
}



//check in shat kabala
GenericString* make_string(const char *str) {
	GenericString *a = new String(str); //as requested, allocate memory
	//cout << "String was made" << endl;
	return a;
}


//helpers:
//int atoi(const char* str) //converts numeric str to an actual num (int type)
//char *strtok(char *str, const char *delim) //break to substrings
