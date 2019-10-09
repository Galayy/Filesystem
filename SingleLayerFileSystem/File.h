#pragma once

#include <stdlib.h>

class File {
private:
	const int FILE_SIZE = 64;
	char* data;
	int fileDataSize;
public:
	File();
	int* address;

	void addToAddress(int blockIndex);
	void setFileDataSize(int);
	void setData(char*);

	char* getData();

	int getFileDataSize();
	int getFileCapacity();
	~File();
};
