#include <vector>
#include <fstream>
#include <iostream>

#include "calculateIntcode.h"

using namespace std;



int day2_1() {
	ifstream in;

	in.open("input2.txt");

	int input;
	char comma;
	vector<int> opcode;

	while (in >> input >> comma) {
		opcode.push_back(input);
	}

	opcode[1] = 12;
	opcode[2] = 2;
	calculateIntcode(opcode);
	return opcode[0];
}

int day2_2() {
	ifstream in;

	in.open("input2.txt");

	int input;
	char comma;
	vector<int> opcode;

	while (in >> input >> comma) {
		opcode.push_back(input);
	}

	int intcodeResult = 0;
	int const DESIRED_OUTPUT = 19690720;

	for (int noun = 0; noun < 100; ++noun) {
		for (int verb = 0; verb < 100; ++verb) {
			vector<int> opCopy(opcode);
			opCopy[1] = noun;
			opCopy[2] = verb; 
			calculateIntcode(opCopy);
			if (opCopy[0] == DESIRED_OUTPUT)
				return 100 * noun + verb;
		}
	}
	return -1;
}