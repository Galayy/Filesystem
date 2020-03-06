#include "File.h"
#include <iostream>
#include <vector>

using namespace std;

File::File() {
	fileDataSize = 0;
}

void File::addToAddress(int blockIndex) {
	address.push_back(blockIndex);
}

void File::setData(vector<char> info) {
	data = info;
};

vector<char> File::getData() {
	return data;
}

void File::setFileDataSize(int dataSize) {
	fileDataSize = dataSize;
}

int File::getFileDataSize() {
	return fileDataSize;
}

File::~File() {
	data.~vector();
	address.~vector();
}