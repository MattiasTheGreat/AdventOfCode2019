#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "calculateIntcode.h"

using namespace std;

long long runAmplifiers(vector<long long>& opcode, vector<int>& phases) {
	long long ampInput = 0;
	for (auto phase : phases) {
		IntComp amp(opcode);
		amp.addInput(phase);
		amp.addInput(ampInput);
		amp.calculateIntcode();
		ampInput = amp.output[0];
	}
	return ampInput;
}

long long runFeedback(vector<long long>& opcode, vector<int>& phases) {

	IntComp amp1(opcode), amp2(opcode), amp3(opcode), amp4(opcode), amp5(opcode);
	amp1.addInput(phases[0]);
	amp2.addInput(phases[1]);
	amp3.addInput(phases[2]);
	amp4.addInput(phases[3]);
	amp5.addInput(phases[4]);
	
	amp1.addInput(0);
	int inputCounter = 0;
	while (!amp5.halted) {
		amp1.calculateIntcode();
		amp2.addInput(amp1.output[inputCounter]);

		amp2.calculateIntcode();
		amp3.addInput(amp2.output[inputCounter]);

		amp3.calculateIntcode();
		amp4.addInput(amp3.output[inputCounter]);

		amp4.calculateIntcode();
		amp5.addInput(amp4.output[inputCounter]);

		amp5.calculateIntcode();
		amp1.addInput(amp5.output[inputCounter]);
		++inputCounter;
	}

	return amp5.output[inputCounter - 1];
}

int day7_1() {
	ifstream in;

	in.open("input7.txt");

	int input;
	char comma;
	vector<long long> opcode;

	while (in >> input >> comma) {
		opcode.push_back(input);
	}
	vector<int> phases;
	phases.push_back(0);
	phases.push_back(1);
	phases.push_back(2);
	phases.push_back(3);
	phases.push_back(4);
	long long most = 0;
	for (int i = 0; i < 120; ++i) { // 120 == 5! == permutation of 5 entries;
		most = max(most, runAmplifiers(opcode, phases));
		next_permutation(phases.begin(), phases.end());

	}
	return most;
}

int day7_2() {
	ifstream in;

	in.open("input7.txt");

	long long input;
	char comma;
	vector<long long> opcode;

	while (in >> input >> comma) {
		opcode.push_back(input);
	}
	vector<int> phases;
	phases.push_back(5);
	phases.push_back(6);
	phases.push_back(7);
	phases.push_back(8);
	phases.push_back(9);
	long long most = 0;
	for (int i = 0; i < 120; ++i) { // 120 == 5! == permutation of 5 entries;
		most = max(most, runFeedback(opcode, phases));
		next_permutation(phases.begin(), phases.end());

	}
	return most;
}

// 1: 68 incorrect;
//2: 4716712 too low;
//2: 139629729 too high