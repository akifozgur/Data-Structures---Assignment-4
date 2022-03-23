#include "ExecuteCommands.h"

void ExecuteCommands::executeAllCommands(string inputFile, string outputFile) {

    vector<vector<string>> inputLines;

    ReadInput readInput;
    inputLines = readInput.readInputFile(inputFile);

    DictionaryTrie dict;
    DictionaryTrie* root = new DictionaryTrie();

    ofstream outfile;
    outfile.open(outputFile);

    for (vector<string> inputLine : inputLines) {

        if (inputLine[0] == "insert") {
            dict.insertCommand(root, inputLine[1], inputLine[2], outputFile);
        }
        if (inputLine[0] == "search") {
            dict.searchCommand(root, inputLine[1], outputFile);
        }
        if (inputLine[0] == "delete") {
            dict.deleteCommand(root, inputLine[1], inputLine[1], outputFile);
        }
        if (inputLine[0] == "list") {
            dict.listCommand();
            dict.printAll(root, root, outputFile);
        }
    }

    outfile.close();
};