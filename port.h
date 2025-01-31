#ifndef PORT_H
#define PORT_H

#include "generic-field.h"
#include "string.h"
using namespace std;
#include <string> //for using the template "string"

class Port : public GenericField {
public:
    int range_start;
    int range_end;
    String rule_info;

	Port(const Port& other);
    Port(const char* rule);
    ~Port();

    bool match(const GenericString &packet) const ;
};

#endif