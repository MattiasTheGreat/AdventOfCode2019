#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int day8_1() {

	ifstream in;

	in.open("input8.txt");
	char pixel;
	int minZeroes = 100000;
	int product = 0;
	bool reached = false;
	while (!reached) {
		int zeroes = 0, ones = 0, twos = 0;
		for (int i = 0; i < 25 && !reached; ++i) {
			for (int j = 0; j < 6 && !reached; ++j) {
				in >> pixel;
				if (in.eof()) {
					reached = true;
					break;
				}
				if (pixel == '0')
					++zeroes;
				if (pixel == '1')
					++ones;
				if (pixel == '2')
					++twos;
			}
		}
		if (zeroes < minZeroes && !reached) {
			minZeroes = zeroes;
			product = ones * twos;
		}

	}
	return product;
}

string day8_2() {
	ifstream in;

	in.open("input8.txt");
	char pixel;
	int minZeroes = 100000;
	int product = 0;
	bool reached = false;
	vector<vector<char>> image(6, vector<char>(25,2));
	while (!reached) {
		for (int i = 0; i < 6 && !reached; ++i) {
			for (int j = 0; j < 25 && !reached; ++j) {
				in >> pixel;
				if (in.eof()) {
					reached = true;
					break;
				}

				if (pixel != '2' && image[i][j] == 2)
					image[i][j] = pixel;

			}
		}
	}
	
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 25; ++j)
			cout << image[i][j];
		cout << endl;
	}
	return "above";
}

//1: 1925 too low;