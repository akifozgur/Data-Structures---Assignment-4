#include "DictionaryTrie.h"


void DictionaryTrie::insertCommand(DictionaryTrie* root, string key,string value, string outputFile) {

    ofstream outfile(outputFile, ios_base::out | ios_base::app);

    for (int i = 0; i < key.length(); i++)
    {

        if (root->word[key[i]] == nullptr) {
            root->word[key[i]] = new DictionaryTrie();
        }
        root = root->word[key[i]];
        root->letter = key[i];
    }
    outfile<< "\"" << key << "\"";
    if (root->english == "") {
        root->english = value;

        dictWord.push_back(key);
        dictWord.push_back(value);
        dictWords.push_back(dictWord);
        dictWord.clear();
        outfile << " was added" << endl;
    }
    else if (root->english == value) {
        outfile << " already exist" << endl;
    }
    else {

        for (vector<string> words : dictWords) {
            if (words[0] == key) {
                words[1] = value;
            }
        }

        root->english = value;
        outfile << " was updated" << endl;
    }

    root->isLeaf = true;
    
}

bool DictionaryTrie::searchCommand(DictionaryTrie* root, string key, string outputFile){

    ofstream outfile(outputFile, ios_base::out | ios_base::app);
    if (root == nullptr) {
        outfile << "\"no record\"" << endl;
        
        return false;
    }

    for (int i = 0; i < key.length(); i++)
    {
        root = root->word[key[i]];

        if (i == 0 && root == nullptr) {
            outfile << "\"no record\"" << endl;
            
            return false;
        }
        else if (root == nullptr) {
            outfile << "\"incorrect Dothraki word\"" << endl;
            
            return false;
        }
    }

    if (!root->isLeaf) {
        outfile << "\"not enough Dothraki word\"" << endl;
        
        return false;
    }

    outfile << "\"The English equivalent is " << root->english << "\"" << endl;
    
    return root->isLeaf;
}

bool DictionaryTrie::isThereChild(DictionaryTrie const* root)
{
    for (int i = 0; i < CHAR_SIZE; i++)
    {
        if (root->word[i]) {
            return true;
        }
    }

    return false;
}

bool DictionaryTrie::deleteCommand(DictionaryTrie*& root, string key, string originalKey, string outputFile){

    ofstream outfile(outputFile, ios_base::out | ios_base::app);

    if (root == nullptr) {
        outfile << "\"no record\"" << endl;
        
        return false;
    }

    if (key.length())
    {
        if (root->word[key[0]] == nullptr) {
            if (root->letter == '.') {
                outfile << "\"no record\"" << endl;
            }
            else {
                outfile << "\"incorrect Dothraki word\"" << endl;
            }
        }

        else if (root != nullptr &&
            root->word[key[0]] != nullptr &&
            deleteCommand(root->word[key[0]], key.substr(1), originalKey, outputFile) &&
            root->isLeaf == false)
        {
            if (!isThereChild(root))
            {
                delete root;
                root = nullptr;
                
                return true;
            }
            else {
                
                return false;
            }
        }
    }

    if (key.length() == 0)
    {
        if (root->isLeaf) {

            for (int i = 0; i < dictWords.size(); i++) {
                if (dictWords[i][0] == originalKey) {
                    deletedWord = i;
                }
            }
            if (deletedWord != 9999) {
                dictWords.erase(dictWords.begin() + deletedWord);
                deletedWord = 9999;
            }

            if (!isThereChild(root))
            {
                outfile << "\"" << originalKey << "\" deletion is successful" << endl;
                root->english = "";
                delete root;
                root = nullptr;
                
                return true;
            }
            else {
                outfile << "\"" << originalKey << "\" deletion is successful" << endl;
                root->english = "";
                root->isLeaf = false;
                
                return false;
            }
        }
        else {
            outfile << "\"not enough Dothraki word\"" << endl;
        }
    }
    
    return false;  
}


void DictionaryTrie::listCommand() {
    position += 1;
    if (position < dictWords.size()) {
        comparedWord.insert(comparedWord.begin(), dictWords[position][0]);
        isCommon(dictWords[position][0]);
    }
}

void DictionaryTrie::isCommon(string word, int pos) {

    if (pos < dictWords.size()) {
        if (dictWords[pos][0] != word) {
            for (int i = 0; i < min(dictWords[pos][0].size(), word.size()); i++) {
                if (dictWords[pos][0][i] == word[i]) {
                    commonPart += dictWords[pos][0][i];
                    if (!(count(comparedWord.begin(), comparedWord.end(), dictWords[pos][0]))) {
                        counter = 1;
                        comparedWord.push_back(dictWords[pos][0]);
                    }
                }
                else {
                    if (counter == 1) {
                        commonParts.push_back(commonPart);
                        counter = 0;
                        commonPart = "";
                    }
                    isCommon(word, pos + 1);
                    break;
                }
            }
            if (counter == 1) {
                commonParts.push_back(commonPart);
                commonPart = "";
                counter = 0;
                isCommon(word, pos + 1);
            }
        }
        else {
            isCommon(word, pos + 1);
        }
    }

    if (comparedWord.size() > 1) {

        sort(commonParts.begin(), commonParts.end(), less<string>());

        if (commonParts.size() > 0) {
            for (int i = 0;i < commonPartsList.size(); i++) {
                if (commonPartsList[i].size() != 0) {
                    if (commonPartsList[i][0] == commonParts[0]) {
                        commonPartsList[i].insert(commonPartsList[i].end(), commonParts.begin(), commonParts.end());
                        commonParts.clear();
                        break;
                    }
                }
            }
        }

        if (commonParts.size() != 0) {
            commonPartsList.push_back(commonParts);
        }
        comparedWords.push_back(comparedWord);
        comparedWord.clear();
        commonParts.clear();

    }
    else if (comparedWord.size() == 1) {
        notCommon = comparedWord[0];
        commonParts.push_back(notCommon);
        notCommon = "";

        commonPartsList.push_back(commonParts);
        comparedWords.push_back(comparedWord);
        comparedWord.clear();
        commonParts.clear();
    }

    listCommand();
}

void DictionaryTrie::findCommonParts() {

    int index = 0;
    int size = 0;

    for (int i = 0;i < commonPartsList.size();i++) {
        if (!(commonPartsList[i].size() == 1)) {
            index = i;
            size = commonPartsList[i].size();
            for (int j = 0;j < size;j++) {

            }
        }
    }
}

void DictionaryTrie::printAll(DictionaryTrie* root, DictionaryTrie* originalRoot, string outputFile) {

    ofstream outfile(outputFile, ios_base::out | ios_base::app);

    sort(commonPartsList.begin(), commonPartsList.end(), less<vector<string>>());

    for (int i = 0; i < commonPartsList.size();i++) {
        sort(commonPartsList[i].begin(), commonPartsList[i].end(), less<string>());
        commonPartsList[i].erase(unique(commonPartsList[i].begin(), commonPartsList[i].end()), commonPartsList[i].end());
    }

    commonPartsList.erase(unique(commonPartsList.begin(), commonPartsList.end()), commonPartsList.end());

    sort(comparedWords.begin(), comparedWords.end(), less<vector<string>>());

    for (int i = 0; i < comparedWords.size();i++) {
        sort(comparedWords[i].begin(), comparedWords[i].end(), less<string>());
    }

    comparedWords.erase(unique(comparedWords.begin(), comparedWords.end()), comparedWords.end());

    for (int i = 0; i < commonPartsList.size();i++) {
        if (commonPartsList[i].size() > 1) {
            for (int j = 0;j < commonPartsList[i].size();j++) {
                for (int k = 0;k < comparedWords[i].size();k++) {
                    if (comparedWords[i][k].substr(0, commonPartsList[i][j].size()) == commonPartsList[i][j]) {
                        if (comparedWords[i][k].size() > commonPartsList[i][j].size()) {
                            counter4++;
                        }
                    }
                }
                if (counter4 < 2) {
                    commonPartsList[i].erase(commonPartsList[i].begin() + j);
                }
                counter4 = 0;
            }
        } 
    }

    for (int i = 0;i < commonPartsList.size();i++) {
        for (int j = 0; j < commonPartsList[i].size();j++) {
            if (j > 0) {
                if (commonPartsList[i][j].substr(0, commonPartsList[i][j - 1].size()) == commonPartsList[i][j - 1]) {
                    for (int t = 0;t < counter2;t++) {
                        outfile << "\t";
                    }
                    for (int l = 0;l < commonPartsList[i][j].size();l++) {
                        root = root->word[commonPartsList[i][j][l]];
                    }
                    if (root->english != "") {
                        outfile << "-" << commonPartsList[i][j] << "(" << root->english << ")" << endl;
                    }
                    else {
                        outfile << "-" << commonPartsList[i][j] << endl;
                    }
                    root = originalRoot;
                }
                else {
                    counter2--;
                    for (int t = 0;t < counter2;t++) {
                        outfile << "\t";
                    }
                    for (int l = 0;l < commonPartsList[i][j].size();l++) {
                        root = root->word[commonPartsList[i][j][l]];
                    }
                    if (root->english != "") {
                        outfile << "-" << commonPartsList[i][j] << "(" << root->english << ")" << endl;
                    }
                    else {
                        outfile << "-" << commonPartsList[i][j] << endl;
                    }
                    root = originalRoot;
                }
            }
            else {
                for (int t = 0;t < counter2;t++) {
                    outfile << "\t";
                }
                for (int l = 0;l < commonPartsList[i][j].size();l++) {
                    root = root->word[commonPartsList[i][j][l]];
                }
                if (root->english != "") {
                    outfile << "-" << commonPartsList[i][j] << "(" << root->english << ")" << endl;
                }
                else {
                    outfile << "-" << commonPartsList[i][j] << endl;
                }
                root = originalRoot;
            }
            counter2++;

            
            for (int p = 0;p < comparedWords[i].size();p++) { 
                int k = 0;
                while (k < commonPartsList[i].size()) {
                    if (comparedWords[i][p].substr(0, commonPartsList[i][j].size()) == commonPartsList[i][j]) {
                        if ((commonPartsList[i][k] != commonPartsList[i][j]) && (commonPartsList[i][k].size() >= commonPartsList[i][j].size())) {
                            if (comparedWords[i][p].substr(0, commonPartsList[i][k].size()) == commonPartsList[i][k]) {
                                counter5 = 1;
                            }
                        }
                    }
                    else {
                        counter5 = 1;
                    }
                    k++;
                }
                if (counter5 != 1 && (comparedWords[i][p] != commonPartsList[i][j])) {
                    for (int t = 0;t < counter2;t++) {
                        outfile << "\t";
                    }

                    for (int l = 0;l < comparedWords[i][p].size();l++) {
                        root = root->word[comparedWords[i][p][l]];
                    }
                    outfile << "-" << comparedWords[i][p] << "(" << root->english << ")" << endl;
                    root = originalRoot;
                }
                counter5 = 0;
            }
        }
        counter2 = 0;
    }

    commonPartsList.clear();
    comparedWords.clear();
    position = -1;
    
}