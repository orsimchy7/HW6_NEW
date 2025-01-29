#!/bin/bash


#user input
complexRules=$(cat $1) #read rules file from first arg
packetsInput=$(cat -) #read packets file from stdin
validPackets= #final list

# ========= Part one - parsing 1 complex rule
applyComplexRule() {
	local complexRuleFourFields=$1
	local PacketsInput=$(cat -)
	#for a valid rule line template: 1. no comments 2. no commas
	local validRuleFourFields=$(cat "$complexRuleFourFields" | grep -vE "^ *#"  | cut -d "#" -f 1 |sed 's/,/ /g')
	for field in $validRuleFourFields; do #bash's IFS interepts words as fields - white space(s) separting
		PacketsInput=$(echo "$PacketsInput" | ./firewall.exe "$field")
	done
	echo "$PacketsInput" | sort | uniq
}


# ========= Part two - the wrap - parsing all complex rules
#for a valid rules file - no empty lines
validRules=$(cat "$complexRules" | grep -v '^$')
for Rule in $validRules; do #bash's IFS interepts lines as rules
	validPackets+=$(echo "$packetsInput" | applyComplexRule "$Rule")
	validPackets+="\n"
done

echo -e "$validPackets" | sort | uniq
