#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

struct BreadthFinder {
	vector<char> blockingDoors;
	int x, y;
};


vector<vector<char>> blockingDoors(26, (vector<char>()));

void findBlocking(vector<vector<char>>& labyrinth) {

}


int day18_1() {
	fstream in;

	in.open("input18.txt");
	
	vector<vector<char>> labyrinth;
	
	using Position = pair<int, int>;
	vector<Position> keyPos(26);
	vector<Position> doorPos(26);
	{
		vector<char> row;
		char input;
		while (in >> input) {
			if (input >= 'a' && input <= 'z') {
				keyPos[input - 'a'] = Position{ row.size(), labyrinth.size() };
			}
			if (input >= 'A' && input <= 'Z') {
				doorPos[input - 'A'] = Position{ row.size(), labyrinth.size() };
			}

			row.push_back(input);

			if (in.peek() == '\n') {
				labyrinth.push_back(row);
				row.clear();
			}
			
		}
	}
	/*for (auto key : keyPos) {
		cout << key.first << " " << key.second << endl;
		labyrinth[key.second][key.first] = 'X';
	}*/

	for (auto row : labyrinth) {
		for (auto elem : row) {
			cout << elem;

		}
		cout << endl;
	}

	vector<vector<char>> blockingDoors(26, (vector<char>()));
	for (int i = 0; i < keyPos.size(); ++i) {
		set<Position> visited;
		cout << "finding blocks for: " << char('a' + i) ;
		vector<BreadthFinder> breadthFirst;
		breadthFirst.push_back(BreadthFinder{ vector<char>(),keyPos[i].first,keyPos[i].second });
		while (!breadthFirst.empty()) {
			BreadthFinder current = breadthFirst.front();
			breadthFirst.pop_back();
			int x = current.x;
			int y = current.y;
			int c = labyrinth[y][x];
			if (c == '@') {
				blockingDoors[i] = current.blockingDoors;
				break;
			}
			else if (c != '#') {
				if (c != '.') {
					
					current.blockingDoors.push_back(c);
				}

				if (x > 0 && visited.count(Position{ x - 1,y }) <1) {
					breadthFirst.push_back(BreadthFinder{ vector<char>(current.blockingDoors), x - 1,y });
					visited.insert(Position{ x - 1,y });
				}

				if (y > 0 && visited.count(Position{ x,y - 1 }) < 1) {
					breadthFirst.push_back(BreadthFinder{ vector<char>(current.blockingDoors), x ,y - 1 });
					visited.insert(Position{ x ,y - 1 });
				}
				if (x < labyrinth[0].size() - 1 && visited.count(Position{ x + 1,y }) < 1) {
					breadthFirst.push_back(BreadthFinder{ vector<char>(current.blockingDoors), x + 1,y });
					visited.insert(Position{ x + 1,y });
				}
				if (y < labyrinth.size() - 1 && visited.count(Position{ x ,y + 1 }) < 1) {
					breadthFirst.push_back(BreadthFinder{ vector<char>(current.blockingDoors), x, y + 1 });
					visited.insert(Position{ x,y + 1 });
				}
			}
		}
		for (auto elem : blockingDoors[i])
			cout << " " << elem;
		cout << endl;
	}

	
	return 1;
}

int day18_2() {
	return 2;
}