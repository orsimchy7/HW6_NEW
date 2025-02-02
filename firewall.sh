#!/bin/bash


#user input
complexRules=$(cat $1) #read rules file from first arg
packetsInput=$(cat - | sed 's/  //g') #read packets file from stdin
validPackets="" #final list

# ========= Part one - parsing 1 complex rule
applyComplexRule() {
	local complexRuleFourFields=$1
	local PacketsInput=$2
	for field in $complexRuleFourFields; do #bash's IFS interepts words as fields - white space(s) separting
		PacketsInput=$(echo "$PacketsInput" | ./firewall.exe "$field")
	done
	echo "$PacketsInput" | sort | uniq
}


# ========= Part two - the wrap - parsing all complex rules
#for a valid rule line template: 1. no comments 2. no commas
complexRules=$(echo "$complexRules" | grep -vE "^ *#"  | cut -d "#" -f 1 |sed 's/,/ /g')
for Rule in $complexRules; do #bash's IFS interepts lines as rules
	validPackets+=$(applyComplexRule "$Rule" "$packetsInput")
	validPackets+="\n"
done
#no empty lines needed
validPackets=$(echo -e "$validPackets" | grep -v '^$')

echo -e "$validPackets" | sort | uniq
