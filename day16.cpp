#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int day16_1() {
	fstream in;

	in.open("input16.txt");
	char input;
	vector<int> signal;
	
	while (in >> input) {
		signal.push_back((int)(input - '0'));
	}

	cout << signal.size() << endl;
	system("pause");
	vector<int> newSignal(signal);
	vector<int> pattern = { 0,1,0,-1 };
	for (int phase = 1; phase <= 100; ++phase) {
		
		for (int i = 0; i < signal.size(); ++i) {
			int patternCounter = 1;
			int patternIndex = 0;
			int sum = 0;
			for (auto dragonFly : signal) {
				if (patternCounter == i + 1) {
					++patternIndex;
					patternCounter = 0;
					if (patternIndex > 3)
						patternIndex -= 4;
				}
				++patternCounter;
				sum += dragonFly * pattern[patternIndex];
			}
			int oneSignal = abs(sum) % 10;
			int patternLength = 4 * i;
			newSignal[i] = abs(sum) % 10;
		}
		signal = newSignal;

	}
	for (int i = 0; i < 8; ++i)
		cout << signal[i];
	cout << endl;
	return 1;
}

int day16_2() {
	return 2;
}

// 1: 80151737 too high;