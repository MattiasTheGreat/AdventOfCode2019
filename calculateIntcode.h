#pragma once
#include <vector>
#include <string>

// Deprecated since 7.1;
std::vector<int> calculateIntcode(std::vector<int>& opcode, std::vector<int>* input = nullptr);



class IntComp {
private:
	int PC = 0;
	int IC = 0;
	int RB = 0;
	const int MAX_PARAMETERS= 3;
	
	std::vector<long long> opcode;
	std::vector<long long> input;
public:
	bool halted = false;

	std::vector<long long> output;

	IntComp(std::vector<long long> opcode);

	bool changeOpcode(int position, int value);
	void addInput(long long in);
	void calculateIntcode();
};

IntComp generateIntComp(std::string fileName);