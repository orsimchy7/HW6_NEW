
#include "string-array.h"


StringArray::StringArray() : subStrVec() {} //inialization list

GenericString* StringArray::get_substr (int idx) {
	return this->subStrVec[idx];
}


int StringArray::getArrLen() {
	return this->subStrVec.size();
}


void StringArray::addSubStr(char *subStr) {
	GenericString* addedStr = new String(subStr);
	this->subStrVec.push_back(addedStr);
}

StringArray::~StringArray() {
	for (GenericString* str : subStrVec) {
		cout << "delete str loop" << endl;
        delete str; //deleting each sub str
    }
    subStrVec.clear(); // vector deleting
    cout << "~StringArray" << endl;
    
}

