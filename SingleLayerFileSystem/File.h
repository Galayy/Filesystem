#pragma once

#include <stdlib.h>

class File {
private:
	const int FILE_SIZE = 64;
	char* data=new char[FILE_SIZE];
	int file_data_size = 0;
public:
	int* address = (int*)calloc(FILE_SIZE, sizeof(char));
	void addToAddress(int blockIndex);
	void set_data(char*);
	char* get_data();
	void set_file_data_size(int);
	int get_file_data_size();
	int get_file_capacity();
};
