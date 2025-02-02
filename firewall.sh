#!/bin/bash


#user input
complexRules=$(cat $1) #read rules file from first arg
packetsInput=$(cat - | sed 's/  //g') #read packets file from stdin
validPackets="" #final list

# ========= Part one - parsing 1 complex rule
applyComplexRule() {
	local complexRuleFourFields="$1"
	#for a valid rule line template: no commas
	complexRuleFourFields=$(echo "$complexRuleFourFields" | sed 's/,/ /g')
	local PacketsInput="$2"
	for field in $complexRuleFourFields; do #bash's IFS interepts words as fields - white space(s) separting
		PacketsInput=$(echo "$PacketsInput" | ./firewall.exe "$field")
	done
	echo "$PacketsInput"
}


# ========= Part two - the wrap - parsing all complex rules
#for a valid rule line template: 1. no comments 2. no empty lines
complexRules=$(echo "$complexRules" | sed 's/#.*//' | grep -vE '^\s*#|^\s*$')
while IFS= read -r Rule; do #bash's IFS interepts lines as rules
	optionalPkts=$(applyComplexRule "$Rule" "$packetsInput")
	if [[ -n "$optionalPkts" ]]; then
		validPackets+="$optionalPkts"$'\n'
	fi
done <<< "$complexRules"
#deleting first empty line
validPackets=$(echo -e "$validPackets" | grep -v '^$')
#print legal pkts to stdout
echo -e "$validPackets" | sort | uniq
