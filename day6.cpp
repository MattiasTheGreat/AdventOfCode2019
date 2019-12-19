#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <set>

using namespace std;

int countOrbits(map<string, vector<string>> orbits, string parent, int depth) {
	int sum = 0;
	
	if(orbits[parent].empty()){
		return depth;
	}
	for (auto child : orbits[parent]) {
		sum += countOrbits(orbits, child, depth + 1);
	}
	//cout << parent << " has " << sum + depth << " indirect" << endl;
	return sum + depth;
}

struct pathNode {
	int height = 0;
	int i = 0;

	void operator+(const pathNode& a) {
		height += a.height;
		i += a.i;
	}
};

int counter = 0;
pathNode findSharedParent(map<string, vector<string>> orbits, string parent) {
	pathNode result;
	counter++;
	cout << counter << endl;
	if (parent == "YOU" || parent == "SAN") {
		result.i = 1;
	}

	if (orbits[parent].empty()) {
		return result;
	}
	for (auto child : orbits[parent]) {

		result + findSharedParent(orbits, child);
		if (result.i == 2)
			return result;
	}
	if (result.i == 1)
		result.height += 1;
	return result;
}

int day6_1() {
	string input;
	ifstream in;
	map<string, vector<string>> orbits;

	in.open("input6.txt");

	int counter2 = 0;
	while (in >> input) {
		string parent, child;
		counter2++;
		parent = input.substr(0, 3);
		child = input.substr(4, 3);
		orbits[parent].push_back(child);
	}
	return countOrbits(orbits, "COM", 0);
	

}

int day6_2() {
	string input;
	ifstream in;
	map<string, vector<string>> orbits;

	in.open("input6.txt");


	int counter2 = 0;
	while (in >> input) {
		string parent, child;
		counter2++;
		parent = input.substr(0, 3);
		child = input.substr(4, 3);
		orbits[parent].push_back(child);
	}
	pathNode result = findSharedParent(orbits, "COM");
	return result.height;
}
