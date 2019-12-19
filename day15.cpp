#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <set>

#include "calculateIntcode.h"

using namespace std;

struct Ink {
	int x, y, depth;
};

int day15_1() {
	IntComp comp = generateIntComp("input15.txt");
	vector<vector<int>> grid(1000, vector<int>(1000,-1));
	int botX = 500, botY = 500;
	int currentTile = 1;
	int inputCounter = 0;
	string input;
	int currentDirection = 1;
	int stepCounter = 0;
	while (!(stepCounter > 4 && botX == 500 && botY == 500)) {
		++stepCounter;
		/*system("cls");
		for (int y = botY - 15; y < botY + 15; ++y) {
			auto row = grid[y];
			for (int x = botX - 15; x < botX + 15; ++x) {
				if (x == botX && y == botY)
					cout << "D";
				else {
					switch (row[x]) {
					case -1:
						cout << "-";
						break;
					case 0:
						cout << "#";
						break;
					default:
						cout << ".";
						break;
					}
				}

			}
			cout << endl;
		}
		cout << currentTile << endl;*/
		/*cin >> input;
		while (input != "w" && input != "a" && input != "s" && input != "d") {
			cout << "Invalid input";
			cin >> input;
		}
		int intput = 1;
		if (input == "w")
			intput = 1;
		else if (input == "a")
			intput = 3;
		else if (input == "s")
			intput = 2;
		else if (input == "d")
			intput = 4;*/
		
		if (currentTile == 0) {
			if (currentDirection == 1)
				currentDirection = 3;
			else if (currentDirection == 2)
				currentDirection = 4;
			else if (currentDirection == 3)
				currentDirection = 2;
			else if (currentDirection == 4)
				currentDirection = 1;
		}
		else {
			if (currentDirection == 1)
				currentDirection = 4;
			else if (currentDirection == 2)
				currentDirection = 3;
			else if (currentDirection == 3)
				currentDirection = 1;
			else if (currentDirection == 4)
				currentDirection = 2;
		}
		comp.addInput(currentDirection);
		comp.calculateIntcode();

		currentTile = comp.output[inputCounter];
		++inputCounter;
		
		switch (currentDirection) {
		case 1: // North;
				if (currentTile == 0)
					grid[botY - 1][botX] = 0;
				else{
					--botY;
					grid[botY][botX] = currentTile;
				}
				break;
			case 2: // South;
				if (currentTile == 0)
					grid[botY + 1][botX] = 0;
				else {
					++botY;
					grid[botY][botX] = currentTile;
				}
				break;
			case 3: // West;
				if (currentTile == 0)
					grid[botY][botX - 1] = 0;
				else {
					--botX;
					grid[botY][botX] = currentTile;
				}
				break;
			case 4: // East;
				if (currentTile == 0)
					grid[botY][botX + 1] = 0;
				else {
					++botX;
					grid[botY][botX] = currentTile;
				}
				break;
			}
	}


	queue<Ink> breadth_first;
	set<pair<int, int>> visited;
	Ink current = Ink{ 500, 500, 0 };
	while (grid[current.y][current.x] != 2) {
		if (visited.count(pair<int, int>{current.x, current.y + 1}) == 0 && grid[current.y + 1][current.x] != 0) {
			breadth_first.push(Ink{ current.x, current.y + 1, current.depth + 1 });
			visited.insert(pair<int, int>{current.x, current.y + 1});
		}

		if (visited.count(pair<int, int>{current.x, current.y - 1}) == 0 && grid[current.y - 1][current.x] != 0) {
			breadth_first.push(Ink{ current.x, current.y - 1, current.depth + 1 });
			visited.insert(pair<int, int>{current.x, current.y - 1});
		}

		if (visited.count(pair<int, int>{current.x + 1, current.y}) == 0 && grid[current.y][current.x + 1] != 0) {
			breadth_first.push(Ink{ current.x + 1, current.y, current.depth + 1 });
			visited.insert(pair<int, int>{current.x + 1, current.y});
		}

		if (visited.count(pair<int, int>{current.x - 1, current.y}) == 0 && grid[current.y][current.x - 1] != 0) {
			breadth_first.push(Ink{ current.x - 1, current.y, current.depth + 1 });
			visited.insert(pair<int, int>{current.x - 1, current.y});
		}

		current = breadth_first.front();
		breadth_first.pop();
	}
	
	return current.depth;
}

int day15_2() {
	IntComp comp = generateIntComp("input15.txt");
	vector<vector<int>> grid(1000, vector<int>(1000, -1));
	int botX = 500, botY = 500;
	int currentTile = 1;
	int inputCounter = 0;
	string input;
	int currentDirection = 1;
	int stepCounter = 0;
	int oxygenX, oxygenY;
	while (!(stepCounter > 4 && botX == 500 && botY == 500)) {
		++stepCounter;

		if (currentTile == 0) {
			if (currentDirection == 1)
				currentDirection = 3;
			else if (currentDirection == 2)
				currentDirection = 4;
			else if (currentDirection == 3)
				currentDirection = 2;
			else if (currentDirection == 4)
				currentDirection = 1;
		}
		else {
			if (currentDirection == 1)
				currentDirection = 4;
			else if (currentDirection == 2)
				currentDirection = 3;
			else if (currentDirection == 3)
				currentDirection = 1;
			else if (currentDirection == 4)
				currentDirection = 2;
		}
		comp.addInput(currentDirection);
		comp.calculateIntcode();

		currentTile = comp.output[inputCounter];
		++inputCounter;

		switch (currentDirection) {
		case 1: // North;
			if (currentTile == 0)
				grid[botY - 1][botX] = 0;
			else {
				--botY;
				grid[botY][botX] = currentTile;
			}
			break;
		case 2: // South;
			if (currentTile == 0)
				grid[botY + 1][botX] = 0;
			else {
				++botY;
				grid[botY][botX] = currentTile;
			}
			break;
		case 3: // West;
			if (currentTile == 0)
				grid[botY][botX - 1] = 0;
			else {
				--botX;
				grid[botY][botX] = currentTile;
			}
			break;
		case 4: // East;
			if (currentTile == 0)
				grid[botY][botX + 1] = 0;
			else {
				++botX;
				grid[botY][botX] = currentTile;
			}
			break;
		}

		if (currentTile == 2) {
			oxygenX = botX;
			oxygenY = botY;
		}

	}


	queue<Ink> breadth_first;
	set<pair<int, int>> visited;
	breadth_first.push(Ink{ oxygenX, oxygenY, 0 });
	Ink current;
	while (!breadth_first.empty()) {
		current = breadth_first.front();
		grid[current.y][current.x] = 2;
		breadth_first.pop();
		if (visited.count(pair<int, int>{current.x, current.y + 1}) == 0 && grid[current.y + 1][current.x] != 0) {
			breadth_first.push(Ink{ current.x, current.y + 1, current.depth + 1 });
			visited.insert(pair<int, int>{current.x, current.y + 1});
			
		}

		if (visited.count(pair<int, int>{current.x, current.y - 1}) == 0 && grid[current.y - 1][current.x] != 0) {
			breadth_first.push(Ink{ current.x, current.y - 1, current.depth + 1 });
			visited.insert(pair<int, int>{current.x, current.y - 1});
		}

		if (visited.count(pair<int, int>{current.x + 1, current.y}) == 0 && grid[current.y][current.x + 1] != 0) {
			breadth_first.push(Ink{ current.x + 1, current.y, current.depth + 1 });
			visited.insert(pair<int, int>{current.x + 1, current.y});
		}

		if (visited.count(pair<int, int>{current.x - 1, current.y}) == 0 && grid[current.y][current.x - 1] != 0) {
			breadth_first.push(Ink{ current.x - 1, current.y, current.depth + 1 });
			visited.insert(pair<int, int>{current.x - 1, current.y});
		}

		cout << current.depth << endl;
	}

	return current.depth;
}

// 1: 743 too high;
// 2: 390 too low;