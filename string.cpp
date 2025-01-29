
#include <cstring>
#include <iostream>
using namespace std;
#include "string.h"

//constuctors
String::String(const char* str) : strg(new char[strlen(str) + 1]) { //inialization list
	strcpy(strg, str);

	cout << "String created" << endl;
}

String::String(const String& other): strg(new char[strlen(other.strg) + 1]) {
	strcpy(this->strg, other.strg);
}
//operators
GenericString& String::operator=(const char *str) {
	if(!str) return *this;
	if (this->strg) {
		delete[] this->strg; //free memory allocated before
	}
	if (str) {
		this->strg = new char[strlen(str) + 1]; //+1 for '/0'
		strcpy(this->strg, str);
	}
	else {
		this->strg=nullptr;
	}
	return *this; //this is the way of returning refernce to this
}

bool String::operator==(const GenericString &other) const {
	const String* otherString = dynamic_cast<const String*>(&other);
	if (!otherString) return false; //other is not a String - cant compare
	if (!strcmp(otherString->strg, this->strg)) {
		return true;
	}
	return false;
}

bool String::operator==(const char *other) const {
	if (!strcmp(other, this->strg)) {
		return true;
	}
	return false;
}

//other functions

StringArray String::split(const char *delimiters) const {
	StringArray substrs; //dont use this if arrlen is not member anymore: = new StringArray(); cause dont need constructor
	char *strgTemp = new char[strlen(this->strg) + 1];
	strcpy(strgTemp, this->strg);
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
	//1. 'removing' first white spaces
	char* ptr = this->strg; //to avoid mem leaking. operator = has original meaning and ptr doesnt need delete
	while(*(ptr) == ' ' && ptr ) {
		ptr++;
	}
	if (ptr != this->strg) {
		memmove(this->strg, ptr, strlen(ptr) + 1); //coping non-white-spaces srtg to start
	}
	//2. 'removing' last white spaces
	int lastidx = strlen(this->strg) - 1;
	while (lastidx >= 0 && this->strg[lastidx] == ' ') {
		lastidx--;
	}
	this->strg[lastidx + 1] = '\0'; //rewrites first white space to be str end - '/0'
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
	const char* str = this->strg;
	return atoi(str);
}

String::~String() {
	cout << "String destructed" << endl;
	delete[] strg;
	cout << "String destructed" << endl;
}

void String::printMethod() {
	cout << "strg member is: "<< strg << endl;
}



//check in shat kabala
GenericString* make_string(const char *str) {
	GenericString *a = new String(str); //as requested, allocate memory
	cout << "String was made" << endl;
	return a;
}


//helpers:
//int atoi(const char* str) //converts numeric str to an actual num (int type)
//char *strtok(char *str, const char *delim) //break to substrings
