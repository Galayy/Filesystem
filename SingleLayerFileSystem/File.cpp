#include "File.h"
#include <iostream>

using namespace std;

File::File() {
	address = (char*)calloc(FILE_SIZE, sizeof(char));
	data = new char[FILE_SIZE];
	fileDataSize = 0;
}

void File::addToAddress(int blockIndex) {
	for (int i = 0; i < FILE_SIZE; i++) {
		if (address[i] == '\0') {
			address[i] = blockIndex;
			break;
		}
	}
}

void File::setData(char* info) {
	data = info;
}

char* File::getData() {
	return data;
}

void File::setFileDataSize(int dataSize) {
	fileDataSize = dataSize;
}

int File::getFileDataSize() {
	return fileDataSize;
}

int File::getFileCapacity() {
	return FILE_SIZE;
}

File::~File() {
	delete address;
	delete data;
}