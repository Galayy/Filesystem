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

	int writeInFile(string filename, char*, int);
	int moveFile(string fileFrom, string fileTo);
	int copyFile(string fileFrom, string fileTo);
	int createFile(string filename);
	int deleteFile(string filename);
	int readFromFile(string filename);
	int createDump();
	int loadDump();
	int dir();

	~FileSystem();
private:
	const int MEMORY_SIZE = 1024;
	const string SUCCESS_MESSAGE = "Success";
	const string EXISTANCE_MESSAGE = "File doesn't exist";

	bool exists(string filename);

	int success();
	int findEmptyBlock();

	vector<string> getFileNames();

	void occupyTheBlock(int block);
	void setIntoMemory(int emptyBlock, string filename);
};
