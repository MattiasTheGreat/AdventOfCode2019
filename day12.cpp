
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <tuple>

#include <stdio.h>

using namespace std;

class Moon {
public:
	int pos[3];
	int vel[3] = { 0,0,0 };
	string name;

	Moon(int x, int y, int z, string name = "noName") :pos{ x,  y, z }, name{ name }{}

	void applyGravity(Moon& other) {
		for (int i = 0; i < 3; ++i) {
			if (pos[i] > other.pos[i]) {
				--vel[i];
				++other.vel[i];
			}
			else if (pos[i] < other.pos[i]) {
				++vel[i];
				--other.vel[i];
			}
		}
	}

	void applyVelocity() {
		for (int i = 0; i < 3; ++i) {
			pos[i] += vel[i];
		}
	}

	void printPos() {
		cout << "x = " << pos[0] << ", y = " << pos[1] << ", z= " << pos[3] << endl;
	}
};

int calcEnergy(vector<Moon> moons) {
	int energy = 0;
	for (auto moon : moons) {
		int potential = 0;
		int kinetic = 0;
		for (int j = 0; j < 3; ++j) {
			potential += abs(moon.pos[j]);
			kinetic += abs(moon.vel[j]);
		}
		energy += potential * kinetic;
	}
	return energy;
}

int day12_1() {

	freopen("input12.txt", "r", stdin);
	vector<Moon> moons;
	string names[4] = { "Io", "Europa", "Ganymede", "Callisto" };
	for (int i = 0; i < 4; ++i) {
		int x = 0, y = 0, z = 0;
		scanf("%*[x<>=, \n] %d %*[ ,y=] %d %*[z=, ] %d", &x, &y, &z);
		moons.push_back(Moon(x, y, z, names[i]));
	}

	set < tuple<int, int, int, int, int, int>> test;
	for (int gen = 0; gen < 1000; ++gen) {
		for (int i = 0; i < 4; ++i) {
			for (int j = i + 1; j < 4; ++j) {
				//cout << "Applying gravity between " << moons[i].name << " and " << moons[j].name << endl;
				moons[i].applyGravity(moons[j]);
			}
		}

		for (int i = 0; i < 4; ++i) {
			moons[i].applyVelocity();
		}
	}
	
	return calcEnergy(moons);;
}

long long day12_2() {
	freopen("input12.txt", "r", stdin);
	vector<Moon> moons;
	string names[4] = { "Io", "Europa", "Ganymede", "Callisto" };
	for (int i = 0; i < 4; ++i) {
		int x = 0, y = 0, z = 0;
		scanf("%*[x<>=, \n] %d %*[ ,y=] %d %*[z=, ] %d", &x, &y, &z);
		moons.push_back(Moon(x, y, z, names[i]));
	}

	set < tuple<int, int, int, int, int, int,
				int, int, int, int, int, int, 
				int, int, int, int, int, int, 
				int, int, int, int, int, int >> instance;
	for (long long gen = 0; gen < 1000000000000; ++gen) {
		for (int i = 0; i < 4; ++i) {
			for (int j = i + 1; j < 4; ++j) {
				//cout << "Applying gravity between " << moons[i].name << " and " << moons[j].name << endl;
				moons[i].applyGravity(moons[j]);
			}
		}

		for (int i = 0; i < 4; ++i) {
			moons[i].applyVelocity();
		}
		Moon moon1 = moons[0];
		Moon moon2 = moons[1];
		Moon moon3 = moons[2];
		Moon moon4 = moons[3];
		auto t = make_tuple(moon1.pos[0], moon1.pos[1], moon1.pos[2], moon1.vel[0], moon1.vel[1], moon1.vel[2],
			moon2.pos[0], moon2.pos[1], moon2.pos[2], moon2.vel[0], moon2.vel[1], moon2.vel[2],
			moon3.pos[0], moon3.pos[1], moon3.pos[2], moon3.vel[0], moon3.vel[1], moon3.vel[2],
			moon4.pos[0], moon4.pos[1], moon4.pos[2], moon4.vel[0], moon4.vel[1], moon4.vel[2]);

		if (instance.count(t) > 0) {
			cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << " " << get<3>(t) << " " << get<4>(t) << " " << get<5>(t) << endl;
			return gen;
		}
		else
			instance.insert(t);

	}
	return -1;
}
