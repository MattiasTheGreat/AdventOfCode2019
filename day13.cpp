#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

#include "calculateIntcode.h"

using namespace std;

int day13_1() {
	ifstream in;

	in.open("input13.txt");

	long long input;
	char comma;
	vector<long long> opcode;

	while (in >> input >> comma) {
		opcode.push_back(input);
	}
	IntComp comp(opcode);
	comp.calculateIntcode();
	int blockCount = 0;
	for (int i = 2; i < comp.output.size(); i += 3) {
		if (comp.output[i] == 2)
			++blockCount;
	}
	return blockCount;
}

int day13_2() {
	ifstream in;

	in.open("input13.txt");

	long long input;
	char comma;
	vector<long long> opcode;

	while (in >> input >> comma) {
		opcode.push_back(input);
	}
	opcode[0] = 2;
	
	IntComp comp(opcode);
	comp.calculateIntcode();
	int outputCounter = 0;
	vector<long long>& output = comp.output;
	long long maxX = 0, maxY = 0;
	for (; outputCounter < output.size(); outputCounter += 3) {
		maxX = max(maxX, output[outputCounter]);
		maxY = max(maxY, output[outputCounter + 1]);
	}

	vector<vector<long long>> grid(maxY + 1, vector<long long>(maxX + 1, 0));

	outputCounter = 0;

	for (; outputCounter < output.size(); outputCounter += 3) {
		int x = output[outputCounter];
		int y = output[outputCounter + 1];
		int tile = output[outputCounter + 2];

		if (output[outputCounter] >= 0)
			grid[y][x] = tile;
	}

	string joystick;
	int score = 0;
	int pad_x = 20;
	int ball_x = 16;
	while (!comp.halted) {
		system("cls");
		for (auto row : grid) {
			cout << row.size() << " ";
			for (auto tile : row) {
				switch (tile) {
				case 0:
					cout << " ";
					break;
				case 1:
					cout << "M";
					break;
				case 2:
					cout << "H";
					break;
				case 3:
					cout << "-";
					break;
				case 4:
					cout << ".";
					break;
				}
			}
			cout << endl;
		}
	

		if (ball_x < pad_x) 
			joystick = "1";
		
		else if (ball_x > pad_x) 
			joystick = "3";
		
		else 
			joystick = "2";
		
		if (joystick == "1")
			comp.addInput(-1);
		if (joystick == "2")
			comp.addInput(0);
		if (joystick == "3")
			comp.addInput(1);
		
		
		comp.calculateIntcode();
		for (; outputCounter < output.size(); outputCounter += 3) {
			int x = output[outputCounter];
			int y = output[outputCounter + 1];
			int tile = output[outputCounter + 2];

			if (tile == 4)
				ball_x = x;
			if (tile == 3)
				pad_x = x;
			if (output[outputCounter] >= 0)
				grid[y][x] = tile;
			else
				score = tile;
		}
		cout << "Score: " << score << endl;
	}
	return 2;
}

// 1: 204 too low