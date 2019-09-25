#include <iostream>
#include <windows.h>
#include "FileSystem.h"

using namespace std;

void FileSystem::createFile(string filename) {
	int emptyBlock = findEmptyBlock();
	if (emptyBlock == -1) {
		cout << "Lack of memory" << endl;
	} else {
		if (!exists(filename)) {
			setIntoMemory(emptyBlock, filename);
			success();
		} else {
			cout << "File already exists" << endl;
		}
	}
}

void FileSystem::deleteFile(string filename) {
	if (exists(filename)) {
		files.erase(filename);
		success();
	} else {
		cout << "File doesn't exist" << endl;
	} 
}

void FileSystem::copyFile(string fileFrom, string fileTo) {
	if (exists(fileFrom)) {
		File file = files.find(fileFrom)->second;
		files.insert(pair<string, File>(fileTo, file));
		success();
	} else {
		cout << "File doesn't exist" << endl;
	}
}

void FileSystem::moveFile(string fileFrom, string fileTo) {
	if (exists(fileFrom)) {
		File file = files.find(fileFrom)->second;
		files.insert(pair<string, File>(fileTo, file));
		deleteFile(fileFrom);
	}
	else {
		cout << "File doesn't exist" << endl;
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

void FileSystem::success() {
	cout << SUCCESS_MESSAGE << endl;
}

vector<string> FileSystem::getFileNames() {
	vector<string> filenames;
	for (auto it = files.begin(); it != files.end(); ++it) {
		filenames.push_back(it->first);
    }
	return filenames;
}
