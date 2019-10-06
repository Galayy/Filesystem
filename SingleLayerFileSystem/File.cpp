#include "File.h"
#include <iostream>

using namespace std;

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