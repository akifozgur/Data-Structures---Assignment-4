#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;


class ReadInput
{
private:
	vector<string>	split(string str, char delimiter);
	string line;
	vector<string> inputLine;
	vector<vector<string>> inputLines;

public:
	vector<vector<string>> readInputFile(string inputFile);
};

