#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Interval {
public:
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	bool horizontal = false;
	int length = 0, previousLength = 0;

	Interval() {};

	void move(char c, int dist) {
		previousLength = length;
		length += dist;
		switch(c) {
		case 'R':
			x1 = x2;
			x2 = x1 + dist;
			y1 = y2;
			horizontal = true;
			break;

		case 'L':
			x1 = x2;
			x2 = x1 - dist;
			y1 = y2;
			horizontal = true;
			break;
		case 'D':
			x1 = x2;
			y1 = y2;
			y2 = y1 - dist;
			horizontal = false;
			break;
		case 'U':
			x1 = x2;
			y1 = y2;
			y2 = y1 + dist;
			horizontal = false;
			break;
		}
	}

	bool inInterval(int bound1, int bound2, int point) {
		return (point < bound1 && point > bound2) || (point < bound2 && point > bound1);
	}

	 int intersectWireLength(Interval& other) {
		int distance = 100000000; // Too large hopefully.
		if (horizontal) {
			/*if (other.horizontal) {
				if (y1 == other.y1) {
					if (inInterval(x1, x2, other.x1))
						distance = abs(other.x1);

					if (inInterval(x1, x2, other.x2)) {
						distance = min(distance, abs(other.x2));
					}
					if (inInterval(other.x1, other.x2, x1))
						distance = min(distance, abs(x1));

					if (inInterval(other.x1, other.x2, x2))
						distance = min(distance, abs(x2));
					distance += abs(y1); // Any y.
				}

			}
			else {*/
				if (inInterval(other.y1, other.y2, y1) && inInterval(x1, x2, other.x1))
					distance = previousLength + abs(other.x1 - x1) + other.previousLength + abs(other.y1 - y1);
			//}
		}
		else {
			/*if (!other.horizontal) {
				if (x1 == other.x1) {
					if (inInterval(y1, y2, other.y1))
						distance = abs(other.y1);
					if (inInterval(y1, y2, other.y2)) {
						distance = min(distance, abs(other.y2));
					}
					if (inInterval(other.y1, other.y2, y1))
						distance = min(distance, abs(y1));

					if (inInterval(other.y1, other.y2, y2))
						distance = min(distance, abs(y2));
					distance += abs(x1); // Any x.
				}

			}
			else {*/
				if (inInterval(other.x1, other.x2, x1) && inInterval(y1, y2, other.y1))
					distance = previousLength + abs(other.x1 - x1) + other.previousLength + abs(other.y1 - y1);
			//}
		}

		return distance;
	}

	 int intersectManhattan(Interval& other) {
		 int distance = 100000000; // Too large hopefully.
		 if (horizontal) {
			 /*if (other.horizontal) {
				 if (y1 == other.y1) {
					 if (inInterval(x1, x2, other.x1))
						 distance = abs(other.x1);

					 if (inInterval(x1, x2, other.x2)) {
						 distance = min(distance, abs(other.x2));
					 }
					 if (inInterval(other.x1, other.x2, x1))
						 distance = min(distance, abs(x1));

					 if (inInterval(other.x1, other.x2, x2))
						 distance = min(distance, abs(x2));
					 distance += abs(y1); // Any y.
				 }

			 }
			 else {*/
				 if (inInterval(other.y1, other.y2, y1) && inInterval(x1, x2, other.x1))
					 distance = abs(other.x1) + abs(y1);
			 //}
		 }
		 else {
			 /*if (!other.horizontal) {
				 if (x1 == other.x1) {
					 if (inInterval(y1, y2, other.y1))
						 distance = abs(other.y1);
					 if (inInterval(y1, y2, other.y2)) {
						 distance = min(distance, abs(other.y2));
					 }
					 if (inInterval(other.y1, other.y2, y1))
						 distance = min(distance, abs(y1));

					 if (inInterval(other.y1, other.y2, y2))
						 distance = min(distance, abs(y2));
					 distance += abs(x1); // Any x.
				 }

			 }
			 else {*/
				 if (inInterval(other.x1, other.x2, x1) && inInterval(y1, y2, other.y1))
					 distance = abs(other.y1) + abs(x1);
			 //}
		 }

		 return distance;
	 }
};


int day3_1() {
	ifstream in;

	in.open("input3.txt");

	char direction, divider;
	int distance;

	vector<int> distList1, distList2;

	vector<char> dirList1, dirList2;

	bool first = true;
	int index = 0;
	while (in >> direction >> distance >> divider) {

		if (first) {
			distList1.push_back(distance);
			dirList1.push_back(direction);
		}
		else {
			distList2.push_back(distance);
			dirList2.push_back(direction);
		}
		++index;
		if (divider != ',') {
			first = false;
			index = 0;
		}
	}

	Interval firstWire{};
	int bestDist = 100000000;
	for (int i = 0; i < distList1.size(); ++i) {
		firstWire.move(dirList1[i], distList1[i]);
		Interval secondWire{};
		for (int j = 0; j < distList1.size(); ++j) {
			secondWire.move(dirList2[j], distList2[j]);
			bestDist = min(bestDist, secondWire.intersectManhattan(firstWire));
		}
	}
	return bestDist;
}

int day3_2() {
	ifstream in;

	in.open("input3.txt");

	char direction, divider;
	int distance;

	vector<int> distList1, distList2;

	vector<char> dirList1, dirList2;

	bool first = true;
	int index = 0;
	while (in >> direction >> distance >> divider) {

		if (first) {
			distList1.push_back(distance);
			dirList1.push_back(direction);
		}
		else {
			distList2.push_back(distance);
			dirList2.push_back(direction);
		}
		++index;
		if (divider != ',') {
			first = false;
			index = 0;
		}
	}

	Interval firstWire{};
	int bestDist = 100000000;
	for (int i = 0; i < distList1.size(); ++i) {
		firstWire.move(dirList1[i], distList1[i]);
		Interval secondWire{};
		for (int j = 0; j < distList1.size(); ++j) {
			secondWire.move(dirList2[j], distList2[j]);
			bestDist = min(bestDist, secondWire.intersectWireLength(firstWire));
		}
	}
	return bestDist;
}