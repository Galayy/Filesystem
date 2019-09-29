#pragma once

#include <map>
#include <vector>
#include <string>
#include "File.h"
#include "Errors.h"

using namespace std;

class FileSystem {
public:
	FileSystem(int memorySize);

	char* memory;
	map<string, File> files;

	int moveFile(string fileFrom, string fileTo);
	int copyFile(string fileFrom, string fileTo);
	int createFile(string filename);
	int deleteFile(string filename);
	~FileSystem();

private:
	const int MEMORY_SIZE = 1024;
	const string SUCCESS_MESSAGE = "Success";

	bool exists(string filename);

	int success();
	int findEmptyBlock();

	vector<string> getFileNames();

	void setIntoMemory(int emptyBlock, string filename);
};
