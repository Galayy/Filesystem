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

	void moveFile(string fileFrom, string fileTo);
	void copyFile(string fileFrom, string fileTo);
	void createFile(string filename);
	void deleteFile(string filename);
	~FileSystem();

private:
	const string SUCCESS_MESSAGE = "Success";
	const int MEMORY_SIZE = 1024;

	bool exists(string filename);

	int findEmptyBlock();

	vector<string> getFileNames();

	void setIntoMemory(int emptyBlock, string filename);
	void success();

};
