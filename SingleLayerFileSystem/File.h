#pragma once

#include <stdlib.h>

class File {
private:
	const int FILE_SIZE = 64;
public:
	int* address = (int*)calloc(FILE_SIZE, sizeof(char));

	void addToAddress(int blockIndex);
};
