
#ifndef STRINGARRAY_H
#define STRINGARRAY_H

#include <iostream>
using namespace std;
#include <vector> //for using the template "vector"
#include "generic-string.h"
#include "string.h"


class StringArray {
	 public :
	std::vector<GenericString*> subStrVec; //dynamic arr contain pointers for genericstrings
	 public :
	 	StringArray();
	 	~StringArray();
	 	GenericString* get_substr (int idx);
	 	int getArrLen();
	 	void addSubStr(char *subStr);
};

#endif
