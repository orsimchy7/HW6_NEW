
#ifndef STRING_H
#define STRING_H

#include "generic-string.h"
#include "string-array.h"


class String : public GenericString {
 public :
	char* strg; //mustnt be const oherwise cant change!! and probably wasnt allowed to use std::string
 public :
 	String() = default;
 	String(const char* str); //constructor
 	String(const String& other); //copy constructor
	StringArray split(const char *delimiters) const;
	GenericString& operator=(const char *str);
	GenericString& trim();
	bool operator==(const GenericString &other) const;
	bool operator==(const char *other) const;
	int to_integer() const;
	String& as_string();
	const String& as_string() const;
	GenericString* make_string(const char *str);
	void printMethod();
	~String();
};
GenericString* make_string(const char *str);

#endif
