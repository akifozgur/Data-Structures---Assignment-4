#include "ReadInput.h"

vector<string> ReadInput::split(string str, char delimiter) {

	stringstream ss(str);
	string tok;

	while (getline(ss, tok, delimiter)) {
		if (tok.find(",") != string::npos) {
			split(tok, ',');
		}
		else if (tok.find(")") != string::npos) {
			tok.erase(remove(tok.begin(), tok.end(), ')'), tok.end());
			inputLine.push_back(tok);
		}
		else {
			inputLine.push_back(tok);
		}
	}

	return inputLine;
}

vector<vector<string>> ReadInput::readInputFile(string inputFile) {

	ifstream MyReadFile(inputFile);

	while (getline(MyReadFile, line)) {

		if (line.size() == 4) {
			inputLine.push_back(line);
			inputLines.push_back(inputLine);
			inputLine.clear();
		}
		else {
			inputLine = split(line, '(');
			inputLines.push_back(inputLine);
			inputLine.clear();
		}
	}
	MyReadFile.close();
	return inputLines;
}