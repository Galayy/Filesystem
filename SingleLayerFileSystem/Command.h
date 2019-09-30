#pragma once

#include <string>
#include <vector>
#include "Errors.h"

using namespace std;

class Command {
private:
	const string CMD_ERROR_MESSAGE = "Wrong input. Try 'help' command for more information";

	string input;
	string word;

	vector<string> commandNames;

	int resolveCommand(string command);

public:
	int processInput(vector<string> inputString);

	bool validateInput(string command, vector<string> commandNames);

	vector<string> getInputFromCommandLine();
};
