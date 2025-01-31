
#include "generic-field.h"
#include "generic-string.h"
#include "string.h"
#include "port.h"
#include <cstdbool>
#include <cstring>
#include <iostream>
using namespace std;
//<iostream> provides us access to cout cin cerr

Port::Port(const Port& other): range_start(other.range_start),
                               range_end(other.range_end),
                               rule_info(other.rule_info){

}


Port::Port(const char* rule = "") : range_start(0), range_end(0),rule_info(rule){
    //parsing the rule string.
    rule_info.trim();

    //separate the field name and value.
    StringArray as1 = rule_info.split("=");
    
    StringArray range_values = as1.get_substr(1)->split("-");

    //convert strings to ints
    range_start = range_values.get_substr(0)->trim().to_integer();
    range_end = range_values.get_substr(1)->trim().to_integer();
    
    // rule_info = "src-port" or "dst-port"
    rule_info = as1.get_substr(0)->trim().as_string();

    //delete s_p;
}

Port::~Port() {
}


bool Port::match(const GenericString &packet) const {
    // Parse the packet
    String trimmed_packet = packet.as_string();
    trimmed_packet.trim();
    StringArray fields = trimmed_packet.split(",");
    //fields = ["src-ip=6.6.6.6  ", 
    //" src-port=67,dst-port=4 ",...]

    //find the relevant port field.
    for (int i = 0; i < fields.getArrLen(); i++) {
        StringArray key_value = fields.get_substr(i)->split("=");
        key_value.get_substr(0)->trim();

        // Check if the current field matches the rule information.
        if (*(key_value.get_substr(0)) == rule_info) {
            int port = key_value.get_substr(1)->trim().to_integer();
            return (port >= range_start && port <= range_end);
        }
    }

    // Return false if error
    return false; 
}