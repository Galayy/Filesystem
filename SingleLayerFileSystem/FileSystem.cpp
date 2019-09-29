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
// add lack of memory
void FileSystem::write_in_file(string filename) {
	if (exists(filename)) {
		int file_copacity = files.find(filename)->second.get_file_copacity();
		char* info = new char[file_copacity];
		cin.getline(info, file_copacity);
		cin.clear();
		cin.ignore(10000, '\n');
		int data_size = string(info).length();

		if (data_size > file_copacity) {
			data_size = file_copacity;
		}
		files.find(filename)->second.set_file_data_size(data_size);
		files.find(filename)->second.set_data(info);
		for (int i = 0; i < data_size; i++) {
			files.find(filename)->second.addToAddress(findEmptyBlock());
		}
		cout << SUCCESS_MESSAGE << endl;
	}
	else {
		cout << EXISTANCE_MESSAGE;
	}
}

File FileSystem::read_from_file(string filename) {
	if (exists(filename)) {
		return files.find(filename)->second;
	}
	else {
		cout << EXISTANCE_MESSAGE;
	}
}

void FileSystem::deleteFile(string filename) {
	if (exists(filename)) {
		files.erase(filename);
		success();
	} else {
		cout << EXISTANCE_MESSAGE << endl;
	} 
}

void FileSystem::copyFile(string fileFrom, string fileTo) {
	if (exists(fileFrom)) {
		File file = files.find(fileFrom)->second;
		files.insert(pair<string, File>(fileTo, file));
		success();
	} else {
		cout << EXISTANCE_MESSAGE << endl;
	}
}

void FileSystem::moveFile(string fileFrom, string fileTo) {
	if (exists(fileFrom)) {
		File file = files.find(fileFrom)->second;
		files.insert(pair<string, File>(fileTo, file));
		deleteFile(fileFrom);
	}
	else {
		cout << EXISTANCE_MESSAGE << endl;
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
