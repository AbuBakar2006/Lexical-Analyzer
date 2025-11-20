#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <map>
using namespace std;

vector<string> keywords = {"assignment", "if", "else", "print"};
vector<string> operatorsList = {"=", "+", "-", "*", "/", "<", ">", "<=", ">=", "==", "!="};
vector<char> delimiters = {'(', ')', '{', '}', ';', '"'};

map<string, int> symbolTable;

bool isKeyword(const string &word)
{
    for (auto &kw : keywords)
        if (word == kw)
            return true;
    return false;
}

bool isIdentifier(const string &word)
{
    return regex_match(word, regex("[A-Za-z_][A-Za-z0-9_]*"));
}

bool isNumber(const string &word)
{
    return regex_match(word, regex("[0-9]+(\\.[0-9]+)?"));
}

bool isStringLiteral(const string &word)
{
    return regex_match(word, regex("\".*\""));
}

bool isOperator(const string &word)
{
    for (auto &op : operatorsList)
        if (word == op)
            return true;
    return false;
}

bool isDelimiter(char ch)
{
    for (auto &d : delimiters)
        if (ch == d)
            return true;
    return false;
}

int main()
{
    string FileAddress;
    cout << "Enter File Address: ";
    getline(cin, FileAddress);
    ifstream inputFile(FileAddress);
    ofstream tokensFile("tokens.txt");
    ofstream symbolFile("symbol_table.txt");
    ofstream errorFile("errors.txt");

    if (!inputFile)
    {
        cout << "Error: Cannot open input.txt\n";
        return 1;
    }

    string line;
    int lineNumber = 0;

    while (getline(inputFile, line))
    {
        lineNumber++;

        size_t singleComment = line.find('#');
        if (singleComment != string::npos)
            line = line.substr(0, singleComment);

        size_t multiStart = line.find("/*");
        size_t multiEnd = line.find("*/");
        if (multiStart != string::npos && multiEnd != string::npos)
            line.erase(multiStart, (multiEnd - multiStart) + 2);

        string token = "";
        for (size_t i = 0; i < line.size(); i++)
        {
            char ch = line[i];

            if (isspace(ch))
            {
                if (!token.empty())
                {
                    if (isKeyword(token))
                        tokensFile << token << "\tKeyword\tLine " << lineNumber << endl;
                    else if (isOperator(token))
                        tokensFile << token << "\tOperator\tLine " << lineNumber << endl;
                    else if (isNumber(token))
                        tokensFile << token << "\tNumber\tLine " << lineNumber << endl;
                    else if (isStringLiteral(token))
                        tokensFile << token << "\tString\tLine " << lineNumber << endl;
                    else if (isIdentifier(token))
                    {
                        tokensFile << token << "\tIdentifier\tLine " << lineNumber << endl;
                        if (symbolTable.find(token) == symbolTable.end())
                            symbolTable[token] = lineNumber;
                    }
                    else
                        errorFile << "Invalid token: " << token << " at line " << lineNumber << endl;
                    token = "";
                }
            }
            else if (isDelimiter(ch))
            {
                if (!token.empty())
                {
                    if (isKeyword(token))
                        tokensFile << token << "\tKeyword\tLine " << lineNumber << endl;
                    else if (isOperator(token))
                        tokensFile << token << "\tOperator\tLine " << lineNumber << endl;
                    else if (isNumber(token))
                        tokensFile << token << "\tNumber\tLine " << lineNumber << endl;
                    else if (isIdentifier(token))
                    {
                        tokensFile << token << "\tIdentifier\tLine " << lineNumber << endl;
                        if (symbolTable.find(token) == symbolTable.end())
                            symbolTable[token] = lineNumber;
                    }
                    else
                        errorFile << "Invalid token: " << token << " at line " << lineNumber << endl;
                    token = "";
                }
                string s(1, ch);
                tokensFile << s << "\tSymbol\tLine " << lineNumber << endl;
            }
            else
            {
                token += ch;
            }
        }

        if (!token.empty())
        {
            if (isKeyword(token))
                tokensFile << token << "\tKeyword\tLine " << lineNumber << endl;
            else if (isOperator(token))
                tokensFile << token << "\tOperator\tLine " << lineNumber << endl;
            else if (isNumber(token))
                tokensFile << token << "\tNumber\tLine " << lineNumber << endl;
            else if (isIdentifier(token))
            {
                tokensFile << token << "\tIdentifier\tLine " << lineNumber << endl;
                if (symbolTable.find(token) == symbolTable.end())
                    symbolTable[token] = lineNumber;
            }
            else
                errorFile << "Invalid token: " << token << " at line " << lineNumber << endl;
        }
    }

    for (auto &entry : symbolTable)
        symbolFile << entry.first << "\tLine " << entry.second << endl;

    cout << "Lexical analysis completed successfully!" << endl;
    cout << "Files Generated!" << endl;

    inputFile.close();
    tokensFile.close();
    symbolFile.close();
    errorFile.close();
    return 0;
}
