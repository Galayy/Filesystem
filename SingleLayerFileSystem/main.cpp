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
const string CMD_ERROR_MESSAGE = "Wrong input. Try 'help' command for more information";

int resolveCommand(string);

void moveFile(vector<string>);
void copyFile(vector<string>);
void deleteFile(vector<string>);
void createFile(vector<string>);
void clearScreen(vector<string>);
void closeFileSystem(vector<string>);
void write_in_file(vector<string>);
void read_from_file(vector<string>);
//7 - load
bool validateInput(string, vector<string>); 

int main() {
	fileSystem = new FileSystem();

	string input;
	string word;

	vector<string> commandNames = {"create", "del", "copy", "move", "cls", "close", "write", "read" };//create enum for commands


	while (shellState) {
		cout << "> ";
		getline(cin, input);
		istringstream iss(input, istringstream::in);
		vector<string> wordsVector;

		while (iss >> word) {
			wordsVector.push_back(word);
		}
		if (validateInput(wordsVector[0], commandNames)) {
			switch (resolveCommand(wordsVector[0])) {
			case 4:
				moveFile(wordsVector);
				break;
			case 3:
				copyFile(wordsVector);
				break;
			case 2:
				deleteFile(wordsVector);
				break;
			case 1:
				createFile(wordsVector);
				break;
			case 0:
				clearScreen(wordsVector);
				break;
			case -1:
				closeFileSystem(wordsVector);
				break;
			case 5:
				// To think about 300 bytes???
				// To think about another way to read data because getline returns String???
				/*cin.getline(data,300);
				data_size = string(data).length();*/
				write_in_file(wordsVector);
				break;
			case 6: 
				read_from_file(wordsVector);
				break;
			}
		} else {
			cout << CMD_ERROR_MESSAGE << endl;
		}
	}

	return 0;
}

void createFile(vector<string> wordsVector) {
	if (wordsVector.size() == 2) {
		fileSystem->createFile(wordsVector[1].c_str());
	} else {
		cout << CMD_ERROR_MESSAGE << endl;
	}
}

void write_in_file(vector<string> wordsVector) {
	if (wordsVector.size() == 2) {
		fileSystem->write_in_file(wordsVector[1].c_str());
		}
	else {
		cout << CMD_ERROR_MESSAGE << endl;
	}
}

void copyFile(vector<string> wordsVector) {
	if (wordsVector.size() == 3) {
		fileSystem->copyFile(wordsVector[1].c_str(), wordsVector[2].c_str());
	}
	else {
		cout << CMD_ERROR_MESSAGE << endl;
	}
}


void read_from_file(vector<string> wordsVector) {
	if (wordsVector.size() == 2) {
		File file = fileSystem->read_from_file(wordsVector[1]);
		char* info = file.get_data();
		for (int i = 0; i < file.get_file_data_size(); i++) {
			cout << info[i];
		}
		cout << endl;
	}
	else { 
		cout << CMD_ERROR_MESSAGE << endl; 
	}
}

void moveFile(vector<string> wordsVector) {
	if (wordsVector.size() == 3) {
		fileSystem->moveFile(wordsVector[1].c_str(), wordsVector[2].c_str());
	}
	else {
		cout << CMD_ERROR_MESSAGE << endl;
	}
}

void deleteFile(vector<string> wordsVector) {
	if (wordsVector.size() == 2) {
		fileSystem->deleteFile(wordsVector[1].c_str());
	}
	else {
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
	if (command == "move") return 4;
	if (command == "copy") return 3;
	if (command == "del") return 2;
	if (command == "create") return 1;
	if (command == "cls") return 0;
	if (command == "close") return -1;
	if (command == "write") return 5;
	if (command == "read") return 6;
	else return 0;
}