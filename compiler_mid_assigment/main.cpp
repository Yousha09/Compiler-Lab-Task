
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;


string identifiers[100];
string keywordsFound[100];
string operatorsFound[100];
string punctuationFound[100];
string numericFound[100];
string stringFound[100];

int identifierCount = 0;
int keywordCount = 0;
int operatorCount = 0;
int punctuationCount = 0;
int numericCount = 0;
int stringCount = 0;


ofstream MyOutputFile("D:\\compiler lab works\\compiler_mid_task\\output.txt");


void printOutput(string text)
{
    cout << text << endl;
    MyOutputFile << text << endl;
}


bool checkKeyword(string word)
{
    string Keywords[] = {"int","bool","float","char","void","if","else","return","void","return","for","while","break","switch","catch",
                         "break","case","main","namespace"};

    for (int i = 0; i < 19; i++)
    {
        if (word == Keywords[i])
            return true;
    }
    return false;
}


bool checkOperator(string word)
{
    string Operators[] = {"+","-","*","/","%","=","==","!","<",">","<=",">=","<<",">>","++","--"};

    for (int i = 0; i < 16; i++)
    {
        if (word == Operators[i])
            return true;
    }
    return false;
}


bool checkPunctuation(string word)
{
    string punctuation[] = {";",",","(",")","[","]","{","}"};

    for (int i = 0; i < 8; i++)
    {
        if (word == punctuation[i])
            return true;
    }
    return false;
}


bool checkNumeric(string word)
{
    bool numeric = true;
    int dot = 0;
    int digit = 0;

    for (int i = 0; i < word.length(); i++)
    {
        if ((int)word[i] >= 48 && (int)word[i] <= 57)
            digit++;

        else if ((int)word[i] == 46)
            dot++;

        else
            numeric = false;
    }

    if (numeric && dot <= 1 && digit > 0)
        return true;

    return false;
}


bool checkIdentifier(string word)
{
    bool identifier = true;

    if (!(((int)word[0] >= 65 && (int)word[0] <= 90) ||
          ((int)word[0] >= 97 && (int)word[0] <= 122) ||
           (int)word[0] == 95))
    {
        identifier = false;
    }

    for (int i = 1; i < word.length(); i++)
    {
        if (!(((int)word[i] >= 65 && (int)word[i] <= 90) ||
              ((int)word[i] >= 97 && (int)word[i] <= 122) ||
              ((int)word[i] >= 48 && (int)word[i] <= 57) ||
               (int)word[i] == 95))
        {
            identifier = false;
        }
    }

    return identifier;
}


bool isDuplicate(string word, string arr[], int count)
{
    for (int i = 0; i < count; i++)
    {
        if (arr[i] == word)
            return true;
    }
    return false;
}


void printUnique(string word, string type,
                 string arr[], int &count)
{
    if (!isDuplicate(word, arr, count))
    {
        printOutput("    " + word + " -> " + type);

        if (count < 100)
        {
            arr[count] = word;
            count++;
        }
    }
}


void identifyToken(string word)
{
    if (checkKeyword(word))
        printUnique(word, "Keyword",
                    keywordsFound, keywordCount);

    else if (checkOperator(word))
        printUnique(word, "Operator",
                    operatorsFound, operatorCount);

    else if (checkPunctuation(word))
        printUnique(word, "Punctuation",
                    punctuationFound, punctuationCount);

    else if (checkNumeric(word))
        printUnique(word, "Numeric Constant",
                    numericFound, numericCount);

    else if (checkIdentifier(word))
        printUnique(word, "Identifier",
                    identifiers, identifierCount);

    else
        printOutput("    " + word + " -> Unknown Token");
}


void checkString(string word, bool &insideString,string &stringConstant)
{
    if (insideString)
    {
        stringConstant += " " + word;

        for (int i = 0; i < word.length(); i++)
        {
            if ((int)word[i] == 34)
            {
                printUnique(stringConstant, "String Constant",
                            stringFound, stringCount);

                stringConstant = "";
                insideString = false;
                break;
            }
        }
    }

    else if ((int)word[0] == 34)
    {
        stringConstant = word;
        insideString = true;

        for (int i = 1; i < word.length(); i++)
        {
            if ((int)word[i] == 34)
            {
                printUnique(stringConstant, "String Constant",
                            stringFound, stringCount);

                stringConstant = "";
                insideString = false;
                break;
            }
        }
    }

    else
    {
        identifyToken(word);
    }
}


void readFile()
{
    string myText;

    ifstream MyReadFile("D:\\compiler lab works\\compiler_mid_task\\compiler.txt");

    bool insideString = false;
    string stringConstant = "";
    int lineNumber = 0;

    while (getline(MyReadFile, myText))
    {
        lineNumber++;

        printOutput("\nLine " + to_string(lineNumber) + ":");

        stringstream ss(myText);
        string word;

        while (ss >> word)
        {
            checkString(word, insideString, stringConstant);
        }
    }

    MyReadFile.close();
}


int main()
{
    readFile();

    MyOutputFile.close();

    system("notepad.exe \"D:\\compiler lab works\\compiler_mid_task\\output.txt\"");

    return 0;
}
