#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include "FileSystem.h"
#include <stdlib.h>

using namespace std;

FileSystem* fileSystem;
bool shellState = true;
const int MAX_FILE_SIZE = 16;
const string CMD_ERROR_MESSAGE = "Wrong input. Try 'help' command for more information";

int resolveCommand(string);

void createFile(vector<string>);
void clearScreen(vector<string>);
void closeFileSystem(vector<string>);

bool validateInput(string, vector<string>); 

int main() {
	fileSystem = new FileSystem();

	string input;
	string word;

	vector<string> commandNames = {"touch", "cls", "close"};//create enum for commands

	while (shellState) {
		getline(cin, input);
		istringstream iss(input, istringstream::in);
		vector<string> wordsVector;

		while (iss >> word) {
			wordsVector.push_back(word);
		}
		if (validateInput(wordsVector[0], commandNames)) {
			switch (resolveCommand(wordsVector[0])) {
			case 1:
				createFile(wordsVector);
				break;
			case 0:
				clearScreen(wordsVector);
				break;
			case -1:
				closeFileSystem(wordsVector);
				break;
			}
		} else {
			cout << CMD_ERROR_MESSAGE << endl;
		}
	}

	return 0;
	/*int a = 5;
	cout << typeid(&a).name();*/
	//char* memory = (char*) calloc(9, sizeof(char));
}

void createFile(vector<string> wordsVector) {
	if (wordsVector.size() == 2) {
		if (wordsVector[1].size() < MAX_FILE_SIZE) {
			fileSystem->createFile(wordsVector[1].c_str());
		} else cout << "Filename is too long" << endl;
	} else {
		cout << CMD_ERROR_MESSAGE << endl;
	}
}

void clearScreen(vector<string> wordsVector) {
	if (wordsVector.size() == 1) {
		system("CLS");
	} else {
		cout << CMD_ERROR_MESSAGE << endl;
	}
}

void closeFileSystem(vector<string> wordsVector) {
	if (wordsVector.size() == 1) {
		shellState = false;
	} else {
		cout << CMD_ERROR_MESSAGE << endl;
	}
}

bool validateInput(string command, vector<string> commandNames) {
	bool commandExists = false;
	for (int i = 0; i < commandNames.size(); i++) {
		if (commandNames[i] == command) {
			commandExists = true;
			break;
		}
	}
	return commandExists;
}

int resolveCommand(string command) {
	if (command == "touch") return 1;
	if (command == "cls") return 0;
	if (command == "close") return -1;
	else return 0;
}