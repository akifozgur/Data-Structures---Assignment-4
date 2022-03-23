#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#define CHAR_SIZE 126
using namespace std;


class DictionaryTrie
{
private:    
    

public:

    int position = -1;
    int counter = 0;
    int counter2 = 0;
    int counter3 = 0;
    int counter4 = 0;
    int counter5 = 0;
    int counter6 = 0;
    int counter7 = 0;
    string commonPart = "";
    string notCommon="";
    vector<string> commonParts;
    vector<vector<string>> commonPartsList;
    vector<string> comparedWord;
    vector<vector<string>> comparedWords;
    int counterForCompare=0;

    vector<vector<vector<string>>> allWords;
    vector<vector<string>> allWord;


    vector<vector<string>> dictWords;
    vector<string> dictWord;
    int deletedWord=9999;
    char letter='.';
    bool isLeaf;
    string english="";
    //string dothraki;
    DictionaryTrie* word[CHAR_SIZE];

    // Constructor
    DictionaryTrie()
    {
        this->isLeaf = false;

        for (int i = 0; i < CHAR_SIZE; i++) {
            this->word[i] = nullptr;
        }
    }

    void insertCommand(DictionaryTrie* root,string key, string value,string outputFile);
    bool deleteCommand(DictionaryTrie*& curr, string key, string originalKey,string outputFile);
    bool searchCommand(DictionaryTrie* root, string key,string outputFile);
    bool isThereChild(DictionaryTrie const* curr);
    void listCommand();
    void findCommonParts();
    void isCommon(string word,int pos=0);

    void printAll(DictionaryTrie* root, DictionaryTrie* originalRoot,string outputFile);

};

