#pragma once

#include <map>
#include <vector>
#include <string>
#include "File.h"

//add constructor to initialize params
using namespace std;

class FileSystem {
public:
	char* memory = (char*)calloc(MEMORY_SIZE, sizeof(char));
	map<string, File> files;

	void createFile(string filename);
	~FileSystem();

private:
	const int MEMORY_SIZE = 1024;

	bool validateFilename(string filename);

	int findEmptyBlock();

	void setIntoMemory(int emptyBlock, string filename);

};
