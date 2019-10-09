#pragma once

#include <map>
#include <string>
#include "File.h"
#include "Errors.h"

using namespace std;

class FileSystem {
public:
	FileSystem(int memorySize);

	char* memory;
	map<string, File*> files;

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

	const string FILE_ERROR_MESSAGE = "Error while processing file";
	const string SUCCESS_MESSAGE = "Success";
	const string EXISTANCE_MESSAGE = "File doesn't exist";

	bool fileNotNull(File* file);
	bool exists(string filename);

	int success();
	int findEmptyBlock();
	int fileError(string errorMessage);

	void removeFile(string filename);
	void occupyTheBlock(int block);
	void setIntoMemory(int emptyBlock, string filename);
};
