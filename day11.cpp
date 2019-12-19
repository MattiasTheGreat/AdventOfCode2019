#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

#include "calculateIntcode.h"

using namespace std;

int day11_1() {
	ifstream in;

	in.open("input11.txt");

	map<pair<int, int>, int> painted;

	long long input;
	char comma;
	vector<long long> opcode;

	while (in >> input >> comma) {
		opcode.push_back(input);
	}

	int x = 0, y = 0;
	pair<int, int> location(x, y);

	int direction = 0;
	int outputCounter = 0;

	IntComp comp(opcode);
	comp.addInput(0);
	while (!comp.halted) {
		comp.calculateIntcode();
		int paint = comp.output[outputCounter];
		++outputCounter;
		int turn  = comp.output[outputCounter];
		++outputCounter;
		
		painted[location] = paint;

		if (turn == 1) 
			++direction;
		else
			--direction;

		if (direction > 3)
			direction -= 4;
		if (direction < 0)
			direction += 4;

		switch (direction) {
		case 0:
			++x;
			break;
		case 1: 
			--y;
			break;
		case 2:
			--x;
			break;
		case 3:
			++y;
			break;
		}
		

		location.first = x;
		location.second = y;
		if(painted.count(location) == 0)
			comp.addInput(0);
		else
			comp.addInput(painted[location]);
	}

	return painted.size();
}

string day11_2() {
	ifstream in;

	in.open("input11.txt");

	map<pair<int, int>, int> painted;

	long long input;
	char comma;
	vector<long long> opcode;

	while (in >> input >> comma) {
		opcode.push_back(input);
	}

	int x = 0, y = 0;
	pair<int, int> location(x, y);

	int direction = 0;
	int outputCounter = 0;

	IntComp comp(opcode);
	comp.addInput(1);

	int minx = 0, miny = 0, maxx = 0, maxy = 0;
	while (!comp.halted) {
		comp.calculateIntcode();
		int paint = comp.output[outputCounter];
		++outputCounter;
		int turn = comp.output[outputCounter];
		++outputCounter;

		painted[location] = paint;

		if (turn == 1)
			++direction;
		else
			--direction;

		if (direction > 3)
			direction -= 4;
		if (direction < 0)
			direction += 4;

		switch (direction) {
		case 0:
			++x;
			break;
		case 1:
			--y;
			break;
		case 2:
			--x;
			break;
		case 3:
			++y;
			break;
		}
		minx = min(minx, x);
		miny = min(miny, y);
		maxx = max(maxx, x);
		maxy = max(maxy, y);

		location.first = x;
		location.second = y;
		if (painted.count(location) == 0)
			comp.addInput(0);
		else
			comp.addInput(painted[location]);
	}

	for (int i = miny; i <= maxy; ++i) {
		for (int j = minx; j <= maxx; ++j) {
			cout << painted[pair<int, int>(j, i)];
		}
		cout << endl;
	}
	return "above";
}


// 1: 5190 too high;
// 1: 4366 too high;
// 1: 15 incorrect;