#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Command.h"

vector<string> Command::getInputFromCommandLine() {
	getline(cin, input);
	istringstream iss(input, istringstream::in);
	vector<string> wordsVector;

	while (iss >> word) {
		wordsVector.push_back(word);
	}
	return wordsVector;
}

int Command::processInput(vector<string> wordsVector) {
	commandNames = { "create", "del", "copy", "move", "cls", "close", "write", "read"};

	if (validateInput(wordsVector[0], commandNames)) {
		switch (resolveCommand(wordsVector[0])) {
		case 6:
			if (wordsVector.size() == 2) {
				return 6;
			}
			else {
				return Errors::WRONG_INPUT;
			}
			break;
		case 5:
			if (wordsVector.size() == 2) {
				return 5;
			}
			else {
				return Errors::WRONG_INPUT;
			}
			break;
		case 4:
			if (wordsVector.size() == 3) {
				return 4;
			} else {
				return Errors::WRONG_INPUT;
			}
			break;
		case 3:
			if (wordsVector.size() == 3) {
				return 3;
			} else {
				return Errors::WRONG_INPUT;
			}
			break;
		case 2:
			if (wordsVector.size() == 2) {
				return 2;
			} else {
				return Errors::WRONG_INPUT;
			}
			break;
		case 1:
			if (wordsVector.size() == 2) {
				return 1;
			} else {
				return Errors::WRONG_INPUT;
			}
			break;
		case 0:
			if (wordsVector.size() == 1) {
				return 0;
			} else {
				return Errors::WRONG_INPUT;
			}
			break;
		case -1:
			if (wordsVector.size() == 1) {
				return -1;
			} else {
				return Errors::WRONG_INPUT;
			}
			break;
		}
	}
	else {
		cout << CMD_ERROR_MESSAGE << endl;
		return Errors::WRONG_INPUT;
	}
}

bool Command::validateInput(string command, vector<string> commandNames) {
	bool commandExists = false;
	for (int i = 0; i < commandNames.size(); i++) {
		if (commandNames[i] == command) {
			commandExists = true;
			break;
		}
	}
	return commandExists;
}

int Command::resolveCommand(string command) {
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