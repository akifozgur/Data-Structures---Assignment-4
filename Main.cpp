#include <iostream>
#include "ExecuteCommands.h"


using namespace std;


int main(int argc, char** argv)
{
    string inputFile = argv[1];
    string outputFile = argv[2];

    ExecuteCommands executeCommands;
    executeCommands.executeAllCommands(inputFile, outputFile);
}
