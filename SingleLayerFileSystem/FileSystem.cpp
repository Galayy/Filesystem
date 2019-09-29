#include <iostream>
#include <windows.h>
#include "FileSystem.h"

using namespace std;

void FileSystem::createFile(string filename) {
	
	int emptyBlock = findEmptyBlock();
	if (emptyBlock == -1) {
		cout << "Lack of memory" << endl;
	} else {
		if (!validateFilename(filename)) {
			setIntoMemory(emptyBlock, filename);
			cout << "Success" << endl;
		} else {
			cout << "File already exists" << endl;
		}
	}
}
// add lack of memory
void FileSystem::write_in_file(string filename, char* info, int data_size) {
	files.find(filename)->second.set_data(info);
	files.find(filename)->second.set_file_data_size(data_size);
	for (int i = 0; i < data_size; i++) {
		files.find(filename)->second.addToAddress(findEmptyBlock());
	}
	cout << "Success" << endl;
}

File FileSystem::read_from_file(string filename) {
	return files.find(filename)->second;
}

FileSystem::~FileSystem() {
	delete memory;
}

//PRIVATE
bool FileSystem::validateFilename(string filename) {
	/*bool exists = false;
	for (int i = 0; i < files.size(); i++) {
		if (files.[i] == filename) {
			exists = true;
			break;
		}
	}
	return exists;*/
	return false;
}

int FileSystem::findEmptyBlock() {
	int emptyBlockIndex = -1;
	for (int blockIndex = 0; blockIndex < MEMORY_SIZE; blockIndex++) {
		if (memory[blockIndex] == '\0') {
			emptyBlockIndex = blockIndex;
			break;
		}
	}
	return emptyBlockIndex;
}

void FileSystem::setIntoMemory(int emptyBlock, string filename) {
	File file;
	file.addToAddress(emptyBlock);
	files.insert(pair<string, File>(filename, file));
}
