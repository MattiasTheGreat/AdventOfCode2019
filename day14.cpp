
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

struct Resource {
	int amount;
	string name;
	vector<Resource*> components;
	
};

int fuelCost(unordered_set<Resource*> resultants) {
	unordered_set<Resource*> needed;

	return 1;
}

int day14_1() {

	fstream in;

	in.open("input14.txt");

	int rate;
	string rName;
	string equals;
	bool result = false;
	vector<Resource*> components;
	unordered_set<Resource*> resultants;
	while (in >> rate >> rName) {
		if (rName.back() == ',')
			rName.pop_back();

		Resource* resource = new Resource{ rate, rName };
		if (result) {
			resource->components = components;
			components.clear();
			resultants.insert(resource);
		}
		else {
			components.push_back(resource);
		}

		in.ignore(1);
		if (in.peek() == '=') {
			in >> equals;
			result = true;
		}
		else
			result = false;
		
		
		
		
	}
	for (auto elem : resultants) {
		cout << elem->name << " consists of: ";
		for (auto component : elem->components)
			cout << component->amount << " " << component->name << ", ";
		cout << endl;
	}
	
	return 1;
}

int day14_2() {
	return 2;
}