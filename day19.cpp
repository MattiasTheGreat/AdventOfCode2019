#include <iostream>
#include <fstream>

#include "calculateIntcode.h"

using namespace std;

bool isPulling(vector<long long>& opcode, int x, int y) {
	IntComp comp{ opcode };
	comp.addInput(x);
	comp.addInput(y);
	comp.calculateIntcode();

	return comp.output.back() == 1;
}

int const TOO_HIGH = -2;
int const TOO_LOW = -1;
pair<int, int> meassureFitByX(vector<long long>& opcode, int x, int y) {
	if (!isPulling(opcode, x, y)) {
		cout << "initial assumption false\n";
		return pair<int, int>{-1, -1};
	}
	do
		++x;
	while (isPulling(opcode,x, y));

	x -= 100;

	if (isPulling(opcode, x, y)) {
		y += 100;
		if (isPulling(opcode, x, y)) {
			int tooHigh = 0;
			do {
				++y;
				++tooHigh;
			} while (isPulling(opcode, x, y));
			if (tooHigh > 1) {
				cout << "too high at: " << x << " " << y << endl;
				return pair<int, int>{0, TOO_HIGH};
			}
			else {
				cout << "perfect at: " << x << " " << y << endl;
				return pair<int, int>{x, y - 99};
			}
		}
		else {
			cout << "too low at: " << x << " " << y << endl;
			return pair<int, int>{0, TOO_LOW};
		}
	}
	else {
		cout << "too low at: " << x << " " << y << endl;
		return pair<int, int>{TOO_LOW, 0};
	}
}

pair<int, int> findSpace(vector<long long>& opcode, int x, int y) {
	int down = 1;
	int right = 1;

	while (isPulling(opcode, x, y)) {
		++x;
		++right;
	}
	x -= right;
	while (isPulling(opcode, x, y)) {
		++y;
		++down;
	}
	return pair<int, int>{right, down};
}

int day19_1() {
	
	
	ifstream in;

	in.open("input19.txt");

	long long input;
	char comma;
	vector<long long> opcode;

	while (in >> input >> comma) {
		opcode.push_back(input);
	}

	int pullCounter = 0;
	for (int x = 0; x < 50; ++x) {
		cout << x + 1 << "/50\n";
		int pullY = 0;
		for (int y = 0; y < 50; ++y) {
			IntComp comp{ opcode };
			comp.addInput(x);
			comp.addInput(y);
			comp.calculateIntcode();
			if (comp.output.back() == 1) {
				cout << x << " " << y << endl;
				++pullCounter;
				++pullY;
			}
			
			
		}
		//cout << "pully: " << pullY << endl;
	}
	return pullCounter;
}

int day19_2() {
	ifstream in;

	in.open("input19.txt");

	long long input;
	char comma;
	vector<long long> opcode;

	while (in >> input >> comma) {
		opcode.push_back(input);
	}

	long long minX = 0, maxX = 1000;

	while (true) {
		int x, y;
		cin >> x >> y;
		auto result = findSpace(opcode, x, y);
		cout << result.first << " " << result.second << endl;
	}
	/*for(int x = 670; x < 687; ++x)
		for (int y = 930; y < 941; ++y) {
			auto result = findSpace(opcode, x, y);
			cout << "with " << x << " " << y << ": " << result.first << " " << result.second << endl;
		}
		*/

		while (true) {
			int x, y;
			cin >> x >> y;
			auto result = isPulling(opcode, x, y);
			cout << result << endl;
		}
	system("pause");
	bool found = false;
	int testX;
	int testY;
	int initialY;
	while (minX - maxX < -1){
		cout << "minx: " << minX << " maxX: " << maxX << endl;
		testX = (minX + maxX) / 2;
		testY = testX * 1.3;
		int initialX = testX;
		initialY = testY;

		auto fit = meassureFitByX(opcode, testX, testY);
		
		if (fit == pair<int, int>{TOO_LOW, TOO_LOW}) {
			cout << "initial assumption false\n";
			break;
		}
		else if (fit.first == TOO_LOW) {
			minX = testX;
		}
		else if (fit.second == TOO_LOW) {
			minX = testX;
		}
		else if (fit.second == TOO_HIGH) {
			maxX = testX;
		}
		else {
			cout << "found one at: " << fit.first << " " << fit.second << endl;
			maxX = testX;

		}
		
		


		/*if (isPulling(opcode, testX, testY)) {
			testY += 100;
			if (isPulling(opcode, testX, testY)) {
				int tooHigh = 0;
				do {
					++testY;
					++tooHigh;
				}
				while (isPulling(opcode, testX, testY));
				if (tooHigh > 1) {
					maxX = initialX;
					cout << "at x = " << initialX << ", y = " << initialY << " we got too many Y by " << tooHigh << "\n";
				}
				else {
					found = true;
					cout << "found with x = " << testX << ", y = " << initialY << " and testY - 100 = " << testY - 100 << endl;
				}
			}
			else {
				cout << "at x = " << initialX << ", y = " << initialY << " we got too few Y\n";
				minX = initialX;
			}
		}
		else {
			cout << "at x = " << initialX << ", y = " << initialY << " we got too few X\n";
			minX += initialX;
			
		}*/
		
	}
	return testX*10000 + testY;
}

// 2: 6890943 too high;
// 2: 6870941 too high;

// 2: 6810932 too low;