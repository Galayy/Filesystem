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
void write_in_file(vector<string>, char*, int);
void read_from_file(vector<string>);

bool validateInput(string, vector<string>); 

int main() {
	fileSystem = new FileSystem();
	char* data = new char[16];
	int data_size = 0;


	string input;
	string word;

	vector<string> commandNames = {"touch", "cls", "close", "write", "read"};//create enum for commands

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
			case 5:
				// To think about 300 bytes???
				// To think about another way to read data because getline returns String???
				cin.getline(data,300);
				data_size = string(data).length();
				if (data_size > MAX_FILE_SIZE) 
				{ data_size = MAX_FILE_SIZE; }
				write_in_file(wordsVector, data, data_size);
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

void write_in_file(vector<string> wordsVector, char* info, int data_size) {
	if (wordsVector.size() == 2) {
		if (wordsVector[1].size() < MAX_FILE_SIZE) {
			fileSystem->write_in_file(wordsVector[1].c_str(), info, data_size);
			//return;
		}
	}
	else {
		cout << CMD_ERROR_MESSAGE << endl;
	}
}

void read_from_file(vector<string> wordsVector) {
	if (wordsVector.size() == 2) {
		File file = fileSystem->read_from_file(wordsVector[1]);
		for (int i = 0; i < file.get_file_data_size(); i++) {
			cout << file.get_data()[i];
		}
		cout << endl;
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
	if (command == "write") return 5;
	if (command == "read") return 6;
	else return 0;
}