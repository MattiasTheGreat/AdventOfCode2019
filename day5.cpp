#include <iostream>
#include <vector>
#include <fstream>

#include "calculateIntcode.h"

using namespace std;

string day5_1() {
	ifstream in;

	in.open("input5_1.txt");

	int input;
	char comma;
	vector<int> opcode;

	while (in >> input >> comma) {
		opcode.push_back(input);
	}

	vector<int> inputVec(1,1); // Input is a single 1;

	calculateIntcode(opcode, &inputVec);
	cout << endl;
	return "Above";
}

string day5_2() {
	ifstream in;

	in.open("input5_1.txt");

	int input;
	char comma;
	vector<int> opcode;

	while (in >> input >> comma) {
		opcode.push_back(input);
	}

	vector<int> inputVec(1, 5); // Input is a single 5;
	calculateIntcode(opcode, &inputVec);
	cout << endl;
	return "Above";
}

//1079114 too low