#include <iostream>
#include <fstream>

#include "calculateIntcode.h"

using namespace std;

long long day9_1() {
	ifstream in;

	in.open("input9.txt");

	long long input;
	char comma;
	vector<long long> opcode;
	 
	while (in >> input >> comma) {
		opcode.push_back(input);
	}

	IntComp comp(opcode);
	comp.addInput(1);
	comp.calculateIntcode();

	return comp.output[0];
}

long long day9_2() {
	ifstream in;

	in.open("input9.txt");

	long long input;
	char comma;
	vector<long long> opcode;

	while (in >> input >> comma) {
		opcode.push_back(input);
	}

	IntComp comp(opcode);
	comp.addInput(2);
	comp.calculateIntcode();

	return comp.output[0];
}