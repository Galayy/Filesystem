#pragma once

#include <stdlib.h>

class File {
private:
	const int FILE_SIZE = 64;
	char* data = new char[FILE_SIZE];
	int fileDataSize = 0;
public:
	int* address = (int*)calloc(FILE_SIZE, sizeof(char));

	void addToAddress(int blockIndex);
	void setFileDataSize(int);
	void setData(char*);

	char* getData();

	int getFileDataSize();
	int getFileCapacity();
};
