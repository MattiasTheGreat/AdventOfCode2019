#include <iostream>
#include <vector>
using namespace std;


int day4_1() {
	int intervalStart = 264360;
	int intervalEnd = 746325;

	int counter = 0;
	for (int i = intervalStart; i <= intervalEnd; ++i) {
		vector<int> digits;
		int divider = i;

		while (divider > 0) {
			digits.push_back(divider % 10);
			divider /= 10;
		}

		bool increasing = true;
		bool pair = false;

		for (int j = 0; j < digits.size(); ++j) {
			if (j != 0) {
				if (digits[j - 1] == digits[j])
					pair = true;
				else if (digits[j - 1] < digits[j]) {
					increasing = false;
					break;
				}
			}
		}

		if (increasing && pair) {
			++counter;
		}
	}
	return counter;
}

int day4_2() {
	int intervalStart = 264360;
	int intervalEnd = 746325;

	int counter = 0;
	for (int i = intervalStart; i <= intervalEnd; ++i) {
		vector<int> digits;
		int divider = i;

		while (divider > 0) {
			digits.push_back(divider % 10);
			divider /= 10;
		}

		bool increasing = true;
		bool pair = false;
		int chain = 1;

		for (int j = 0; j < digits.size(); ++j) {
			if (j != 0) {
				if (digits[j - 1] == digits[j])
					chain++;
				else{
					if (chain == 2)
						pair = true;
					chain = 1;
					if (digits[j - 1] < digits[j]) {
						increasing = false;
						break;
					}
				}
			}
		}
		if (chain == 2)
			pair = true;

		if (increasing && pair) {
			++counter;
			cout << i << endl;
		}
	}
	return counter;
}

// 1014 too high
// 534 too low