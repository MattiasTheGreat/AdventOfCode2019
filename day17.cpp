#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "calculateIntcode.h"

using namespace std;

int day17_1() {
	IntComp comp = generateIntComp("input17.txt");
	comp.calculateIntcode();
	vector<vector<int>> map;
	vector<int> input_row;
	for (auto elem : comp.output) {
		
		if (elem == '\n') {
			map.push_back(input_row);
			input_row.clear();
		}
		else
			input_row.push_back(elem);
		
	}
	int alignment_parameters = 0;
	for (int i = 0; i < map.size(); ++i) {
		auto row = map[i];
		for (int j = 0; j < row.size(); ++j) {
			int count = 0;

			if(i > 0)
				if (map[i - 1][j] == '#')
					++count;
			if (j > 0)
				if (row[j - 1] == '#')
					++count;
			if (i < map.size() - 2)
				if (map[i + 1][j] == '#')
					++count;
			if (j < row.size() - 2)
				if (row[j + 1] == '#')
					++count;
			if (count > 3)
				alignment_parameters += i * j;
			cout << (char)map[i][j];
		}
		cout << endl;
	}
	return alignment_parameters;
}

int day17_2() {
	using Position = pair<int, int>;

	IntComp comp = generateIntComp("input17.txt");
	comp.changeOpcode(0, 2);
	comp.calculateIntcode();
	vector<vector<int>> map;
	vector<int> input_row;
	Position cleaner{ 0,0 };
	char cleanerDir;
	int cleanX = 0, cleanY = 0;
	for (auto elem : comp.output) {
		if (elem == '<' || elem == '^' || elem == '>' || elem == 'v') {
			cleanerDir = elem;
			cleaner = Position{ cleanX,cleanY };
		}

		if (elem == '\n') {
			map.push_back(input_row);
			input_row.clear();
			++cleanY;
			cleanX = 0;
		}
		else {
			input_row.push_back(elem);
			++cleanX;
		}
	}
	string scaffolding = "";

	int stretchCounter = 0;
	bool noPath = false;
	while (!noPath) {
		int x = cleaner.first;
		int y = cleaner.second;
		if (cleanerDir == '<') {
			--x;
		}
		if (cleanerDir == '^') {
			--y;
		}
		if (cleanerDir == '>') {
			++x;
		}
		if (cleanerDir == 'v') {
			++y;
		}

		if (y >= 0 && y < map.size() && x >= 0 && x < map[y].size() && map[y][x] == '#') {
			if (cleanerDir == '<') {
				--cleaner.first;
			}
			if (cleanerDir == '^') {
				--cleaner.second;
			}
			if (cleanerDir == '>') {
				++cleaner.first;
			}
			if (cleanerDir == 'v') {
				++cleaner.second;
			}
			++stretchCounter;
		}
		else {
			if (stretchCounter > 0) {
				scaffolding.append(to_string(stretchCounter));
				scaffolding.push_back(',');
			}

			if (cleanerDir != '>' && cleaner.first > 0 && map[cleaner.second][cleaner.first - 1] == '#') {
				if (cleanerDir == '^')
					scaffolding.push_back('L');
				else
					scaffolding.push_back('R');
				cleanerDir = '<';
			}
			else if (cleanerDir != 'v' && cleaner.second > 0 && map[cleaner.second - 1][cleaner.first] == '#') {
				if (cleanerDir == '>')
					scaffolding.push_back('L');
				else
					scaffolding.push_back('R');
				cleanerDir = '^';
			}
			else if (cleanerDir != '<' && cleaner.first <= map[cleaner.second].size() - 2 && map[cleaner.second][cleaner.first + 1] == '#') {
				if (cleanerDir == 'v')
					scaffolding.push_back('L');
				else
					scaffolding.push_back('R');
				cleanerDir = '>';
			}
			else if (cleanerDir != '^' && cleaner.second <= map.size() - 2 && map[cleaner.second + 1][cleaner.first] == '#') {
				if (cleanerDir == '<')
					scaffolding.push_back('L');
				else
					scaffolding.push_back('R');
				cleanerDir = 'v';
			}
			else
				noPath = true;
			stretchCounter = 0;
			scaffolding.push_back(',');
		}
	}
	cout << "scaffolding: " << scaffolding << endl;

	char mmr[20] = { 'A', ',' ,
					 'B', ',' ,
					 'A', ',' ,
					 'C', ',' ,
					 'A', ',' ,
					 'B', ',' ,
					 'C', ',' ,
					 'B', ',' ,
					 'C', ',' ,
					 'B','\n' };

	char A[17] = {'L', ',', '1', '0', ',',
				  'R', ',', '8' , ',',
				  'L', ',', '6' , ',',
				  'R', ',', '6', '\n' };

	char B[12] = {'L', ',', '8', ',' ,
				  'L', ',', '8', ',',
				  'R', ',', '8', '\n' };

	char C[18] = { 'R', ',', '8', ',',
				  'L', ',', '6', ',',
				  'L', ',', '1', '0', ',',
				  'L', ',', '1', '0', '\n'};

	for (auto elem : mmr) {
		comp.addInput(elem);
	}

	for (auto elem : A) {
		comp.addInput(elem);
	}

	for (auto elem : B) {
		comp.addInput(elem);
	}

	for (auto elem : C) {
		comp.addInput(elem);
	}

	comp.addInput('n');
	comp.addInput('\n');
	comp.calculateIntcode();

	
	return comp.output.back();
}

// 1: 7302 too high;
// 2: 46 not correct;	
/*
..............###########.###########................
..............#.........#.#.........#................
..............#.......#########.....#................
..............#.......#.#.#...#.....#................
..............#.......#.#.#...#.....#................
..............#.......#.#.#...#.....#................
..............#.#########.#...#.....#................
..............#.#.....#...#...#.....#................
..............#.#.....#...#########.#................
..............#.#.....#.......#...#.#................
..............#########.......#######................
................#.................#..................
................#...........#########................
................#...........#.....#.#................
................#########...#.....#.#................
........................#...#.....#.#................
........................#...#.....#.#................
........................#...#.......#................
........................#...#.......#######..........
........................#...#.............#..........
....................#########.............#..........
....................#...#.................#..........
..................#######.................#..........
..................#.#.....................#..........
..................#.#.....................#..........
..................#.#.....................#..........
..................#.#.....................##########^
..................#.#................................
#######...#########.#................................
#.....#...#.........#................................
#.....#...#.#########................................
#.....#...#.#........................................
#.....#...#.#........................................
#.....#...#.#........................................
#.....#...#.#........................................
#.....#...#.#........................................
#.....#######........................................
#.........#..........................................
###########..........................................
*/