#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include "Command.h"
#include "FileSystem.h"
#include "UnitTests.h"
#include <stdlib.h>

using namespace std;

Command* command;
FileSystem* fileSystem;
UnitTests* unitTests;
bool shellState = true;

const int MEMORY_SIZE = 1024;
const int MAX_FILE_SIZE = 64; // ??????????
const string CMD_ERROR_MESSAGE = "Wrong input. Try 'help' command for more information";

void moveFile(vector<string>);
void copyFile(vector<string>);
void deleteFile(vector<string>);
void createFile(vector<string>);
void clearScreen(vector<string>);
void closeFileSystem(vector<string>);
void write_in_file(vector<string>);
void read_from_file(vector<string>);
bool validateInput(string, vector<string>);
void create_dump(vector<string>);
void load_dump(vector<string>);


int main() {
	unitTests = new UnitTests();
	command = new Command();
	fileSystem = new FileSystem(MEMORY_SIZE);

	unitTests->runTests();

	while (shellState) {
		cout << "> ";
		vector<string> wordsVector = command->getInputFromCommandLine();
		int com = command->processInput(wordsVector);

		switch (com) {
		case 8:
			load_dump(wordsVector);
			break;
		case 7:
			create_dump(wordsVector);
			break;
		case 6:
			read_from_file(wordsVector);
			break;
		case 5:
			write_in_file(wordsVector);
			break;
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
		char* info = new char[MAX_FILE_SIZE];
		cin.get(info, MAX_FILE_SIZE);
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		//int data_size = string(info).length()+1;
		int data_size = string(info).length();
		fileSystem->write_in_file(wordsVector[1].c_str(),info,data_size);
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
		fileSystem->read_from_file(wordsVector[1]);
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

void create_dump(vector<string> wordsVector) {
	if (wordsVector.size() == 1) {
		fileSystem->create_dump();
	}
	else {
		cout << CMD_ERROR_MESSAGE << endl;
	}
}

void load_dump(vector<string> wordsVector) {
	if (wordsVector.size() == 1) {
		fileSystem->load_dump();
	}
	else {
		cout << CMD_ERROR_MESSAGE << endl;
	}
}
