
#include "generic-field.h"
#include "ip.h"
#include "port.h"

#include "generic-string.h"
#include "string.h"
#include "string-array.h"
#include "input.h"

#include <iostream>
using namespace std;

int main(int argc,char **argv){
	
	String rule = argv[1];

	//first we need to figure out if the rule is
	//about Ip or Port

	StringArray rule_divided=rule.split("="); 

	rule_divided.get_substr(0)->trim();
	StringArray rule_info = rule_divided.get_substr(0)->split("-");
	//we will get in rule_info for example:
	//["src", "ip"]

	const char* port_str = "port";
    const char* ip_str = "ip";

    String rule_type = rule_info.get_substr(1)->as_string();

    if(rule_type==ip_str){

    	Ip ip_obj(rule.strg.c_str());

		//cout << "~rule_info" << endl;
    	//using the function parse_input(Generic_field& field)
    	parse_input(ip_obj);

    }else{
    	Port port_obj(rule.strg.c_str());
    	parse_input(port_obj);

    }


	return 0;
}