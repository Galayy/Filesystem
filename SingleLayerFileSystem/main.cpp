 //Operation systems course. 4th laboratory work, 4th variant 
 //Single-layer filesystem with block physical file organization 
 //Created by Galay A.D., Salimova Y.S., 721702
 //October 2019

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
const int MAX_FILE_SIZE = 64; 
const string CMD_ERROR_MESSAGE = "Wrong input";

void dir(vector<string>);
void moveFile(vector<string>);
void copyFile(vector<string>);
void deleteFile(vector<string>);
void createFile(vector<string>);
void clearScreen(vector<string>);
void closeFileSystem(vector<string>);
void writeInFile(vector<string>);
void readFromFile(vector<string>);
bool validateInput(string, vector<string>);
void createDump(vector<string>);
void loadDump(vector<string>);


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
		case 9:
			dir(wordsVector);
			break;
		case 8:
			loadDump(wordsVector);
			break;
		case 7:
			createDump(wordsVector);
			break;
		case 6:
			readFromFile(wordsVector);
			break;
		case 5:
			writeInFile(wordsVector);
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
	}
	else {
		cout << CMD_ERROR_MESSAGE << endl;
	}
}

void writeInFile(vector<string> wordsVector) {
	if (wordsVector.size() == 2) {
		char* info = new char[MAX_FILE_SIZE];
		cin.get(info, MAX_FILE_SIZE);
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		int data_size = string(info).length() + 1;
		fileSystem->writeInFile(wordsVector[1].c_str(), info, data_size);
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


void readFromFile(vector<string> wordsVector) {
	if (wordsVector.size() == 2) {
		fileSystem->readFromFile(wordsVector[1]);
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
	}
	else {
		cout << CMD_ERROR_MESSAGE << endl;
	}
}

void closeFileSystem(vector<string> wordsVector) {
	if (wordsVector.size() == 1) {
		shellState = false;
	}
	else {
		cout << CMD_ERROR_MESSAGE << endl;
	}
}

void createDump(vector<string> wordsVector) {
	if (wordsVector.size() == 1) {
		fileSystem->createDump();
	}
	else {
		cout << CMD_ERROR_MESSAGE << endl;
	}
}

void loadDump(vector<string> wordsVector) {
	if (wordsVector.size() == 1) {
		fileSystem->loadDump();
	}
	else {
		cout << CMD_ERROR_MESSAGE << endl;
	}
}

void dir(vector<string> wordsVector) {
	if (wordsVector.size() == 1) {
		fileSystem->dir();
	}
	else {
		cout << CMD_ERROR_MESSAGE << endl;
	}
}
