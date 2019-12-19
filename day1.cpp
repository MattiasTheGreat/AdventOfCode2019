
#include <iostream>

using namespace std;

void day1_1() {
	int i;
	long long sum = 0;
	while (cin >> i) {
		sum += i / 3 - 2;

		cout << "sum: " << sum << endl;
	}

}



void day1_2() {
	int i;
	long long sum = 0;
	while (cin >> i) {
		int weight = i / 3 - 2;
		while (weight > 0) {
			sum += weight;
			weight = weight / 3 - 2;
		}
		cout << "sum: " << sum << endl;
	}
	
}

