#include <iostream>
#include <windows.h>
#include "FileSystem.h"

using namespace std;

void FileSystem::createFile(string filename) {
	
	int emptyBlock = findEmptyBlock();
	if (emptyBlock == -1) {
		cout << "Lack of memory" << endl;
	} else {
		HANDLE file = CreateFile(filename.c_str(), GENERIC_READ | GENERIC_WRITE, 0,	nullptr, CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL, nullptr);

		if (!validateFilename(filename) && file) {
			setIntoMemory(emptyBlock, filename);
			cout << "Success" << endl;
			CloseHandle(file);
		} else {
			cout << "File already exists" << endl;
		}
	}
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
