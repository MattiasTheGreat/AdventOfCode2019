#include "calculateIntcode.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

vector<int> calculateIntcode(vector<int>& opcode, vector<int>* input) {


	int PC = 0; // Program Counter
	int IC = 0; // Input Counter
	vector<int> output;
	while (opcode[PC] != 99) {
		int operand = opcode[PC];
		int instruction = operand % 100;

		vector<int> parameterMode(3);
		parameterMode[0] = (operand / 100) % 10;
		parameterMode[1] = (operand / 1000) % 10;
		parameterMode[2] = (operand / 10000) % 10;
		//parameterMode[3] = instruction / 100000 % 10;


		int parameter1{ 0 }, parameter2{ 0 }, parameter3{ 0 };
		if (PC + 1 < opcode.size()) {
			if (parameterMode[0] == 0)
				parameter1 = opcode[PC + 1];
			else if (parameterMode[0] == 1)
				parameter1 = PC + 1;
		}

		if (PC + 2 < opcode.size()) {
			if (parameterMode[1] == 0)
				parameter2 = opcode[PC + 2];
			else if (parameterMode[1] == 1)
				parameter2 = PC + 2;
		}

		if (PC + 3 < opcode.size()) {
			if (parameterMode[2] == 0)
				parameter3 = opcode[PC + 3];
			else if (parameterMode[2] == 1)
				parameter3 = PC + 3;
		}



		switch (instruction) {
		case 1: // Addition;
			opcode[parameter3] = opcode[parameter1] + opcode[parameter2];
			PC += 4;
			break;
		case 2: // Multiplication;
			opcode[parameter3] = opcode[parameter1] * opcode[parameter2];
			PC += 4;
			break;

		case 3: // Input;
			if (input) {
				if (IC < input->size())
					opcode[parameter1] = input->at(IC);
				else {
					cout << "To little input error\n";
					return output;
				}
				++IC;
			}
			else {
				cout << "No input error\n";
				return output;
			}
			PC += 2;
			break;
		case 4: // Output;
			output.push_back(opcode[parameter1]);
			cout << opcode[parameter1];
			PC += 2;
			break;
		case 5: // Not equal branch;
			if (opcode[parameter1] != 0)
				PC = opcode[parameter2];
			else
				PC += 3;
			break;
		case 6: // Equal branch;
			if (opcode[parameter1] == 0)
				PC = opcode[parameter2];
			else
				PC += 3;
			break;
		case 7: // Less than comparator;
			if (opcode[parameter1] < opcode[parameter2])
				opcode[parameter3] = 1;
			else
				opcode[parameter3] = 0;
			PC += 4;
			break;
		case 8: // Equals comparator;
			if (opcode[parameter1] == opcode[parameter2])
				opcode[parameter3] = 1;
			else
				opcode[parameter3] = 0;
			PC += 4;
			break;
		}
		
	}

	return output;
}

IntComp::IntComp(std::vector<long long> opcode) : opcode{ opcode } {
	for (int i = 0; i < 10000; ++i)
		this->opcode.push_back(0);
}

void IntComp::calculateIntcode() {
	halted = false;
	
	while (opcode[PC] != 99) {
		long long operand = opcode[PC];
		long long instruction = operand % 100;

		vector<long long> parameterMode(3);
		parameterMode[0] = (operand / 100) % 10;
		parameterMode[1] = (operand / 1000) % 10;
		parameterMode[2] = (operand / 10000) % 10;
		//parameterMode[3] = instruction / 100000 % 10;

		vector<long long> parameters(MAX_PARAMETERS, 0);

		for (int i = 0; i < MAX_PARAMETERS; ++i) {
			if (PC + i + 1 < opcode.size()) {
				if (parameterMode[i] == 0) {
					parameters[i] = opcode[PC + i + 1];
				}
				else if (parameterMode[i] == 1) {
					parameters[i] = PC + i + 1;
				}
				else if (parameterMode[i] == 2) {
					parameters[i] = opcode[PC + i + 1] + RB;
				}
			}
		}

		switch (instruction) {
		case 1: // Addition;
			opcode[parameters[2]] = opcode[parameters[0]] + opcode[parameters[1]];
			PC += 4;
			break;
		case 2: // Multiplication;
			opcode[parameters[2]] = opcode[parameters[0]] * opcode[parameters[1]];
			PC += 4;
			break;

		case 3: // Input;
			if (IC < input.size())
				opcode[parameters[0]] = input.at(IC);
			else {
				cout << "Waiting for input \n";
				return;
			}
			++IC;
			PC += 2;
			break;
		case 4: // Output;
			output.push_back(opcode[parameters[0]]);
			PC += 2;
			break;
		case 5: // Not equal branch;
			if (opcode[parameters[0]] != 0)
				PC = opcode[parameters[1]];
			else
				PC += 3;
			break;
		case 6: // Equal branch;
			if (opcode[parameters[0]] == 0)
				PC = opcode[parameters[1]];
			else
				PC += 3;
			break;
		case 7: // Less than comparator;
			if (opcode[parameters[0]] < opcode[parameters[1]])
				opcode[parameters[2]] = 1;
			else
				opcode[parameters[2]] = 0;
			PC += 4;
			break;
		case 8: // Equals comparator;
			if (opcode[parameters[0]] == opcode[parameters[1]])
				opcode[parameters[2]] = 1;
			else
				opcode[parameters[2]] = 0;
			PC += 4;
			break;

		case 9: // Change Relative Base;
			RB += opcode[parameters[0]];
			PC += 2;
			break;
		}

	}
	halted = true;
}

bool IntComp::changeOpcode(int position, int value) {
	if (position >= 0 && position < opcode.size()) {
		opcode[position] = value;
		return true;
	}

	return false;
}

void IntComp::addInput(long long in) {
	input.push_back(in);
}

IntComp generateIntComp(string fileName) {
	ifstream in;

	in.open(fileName);

	long long input;
	char comma;
	vector<long long> opcode;

	while (in >> input >> comma) {
		opcode.push_back(input);
	}

	return IntComp(opcode);
}
