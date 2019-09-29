#include <iostream>
#include <map>
#include <windows.h>
#include "FileSystem.h"

using namespace std;

FileSystem::FileSystem(int size) {
	memory = (char*)calloc(size, sizeof(char));
}

int FileSystem::createFile(string filename) {
	int emptyBlock = findEmptyBlock();
	if (emptyBlock == -1) {
		cout << "Lack of memory" << endl;
		return Errors::LACK_OF_MEMORY;
	} else {
		if (!exists(filename)) {
			setIntoMemory(emptyBlock, filename);
			return success();
		} else {
			cout << "File already exists" << endl;
			return Errors::FILE_ALREADY_EXISTS;
		}
	}
}

int FileSystem::deleteFile(string filename) {
	if (exists(filename)) {
		files.erase(filename);
		return success();
	} else {
		cout << "File doesn't exist" << endl;
		return Errors::FILE_NOT_FOUND;
	} 
}

int FileSystem::copyFile(string fileFrom, string fileTo) {
	if (exists(fileFrom)) {
		File file = files.find(fileFrom)->second;
		files.insert(pair<string, File>(fileTo, file));
		return success();
	} else {
		cout << "File doesn't exist" << endl;
		return Errors::FILE_NOT_FOUND;
	}
}

int FileSystem::moveFile(string fileFrom, string fileTo) {
	if (exists(fileFrom)) {
		File file = files.find(fileFrom)->second;
		files.insert(pair<string, File>(fileTo, file));
		return deleteFile(fileFrom);
	}
	else {
		cout << "File doesn't exist" << endl;
		return Errors::FILE_NOT_FOUND;
	}

}

FileSystem::~FileSystem() {
	delete memory;
}

//PRIVATE
bool FileSystem::exists(string filename) {
	bool exists = false;
	vector<string> filenames = getFileNames();
	for (int i = 0; i < filenames.size(); i++) {
		if (filename == filenames[i]) {
			exists = true;
			break;
		}
	}
	return exists;
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

int FileSystem::success() {
	cout << SUCCESS_MESSAGE << endl;
	return Errors::SUCCESS;
}

vector<string> FileSystem::getFileNames() {
	vector<string> filenames;
	for (auto it = files.begin(); it != files.end(); ++it) {
		filenames.push_back(it->first);
    }
	return filenames;
}
