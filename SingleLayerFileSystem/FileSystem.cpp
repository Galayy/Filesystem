#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <map>
#include <windows.h>
#include "FileSystem.h"
#include <fstream>

using namespace std;

FileSystem::FileSystem(int size) {
	memory = (char*)calloc(size, sizeof(char));
}


int FileSystem::createFile(string filename) {
	int emptyBlock = findEmptyBlock();
	if (emptyBlock == -1) {
		cout << "Lack of memory" << endl;
		return Errors::LACK_OF_MEMORY;
	}
	else {
		if (!exists(filename)) {
			setIntoMemory(emptyBlock, filename);
			return success();
		}
		else {
			cout << "File already exists" << endl;
			return Errors::FILE_ALREADY_EXISTS;
		}
	}
}

int FileSystem::writeInFile(string filename, char* info, int dataSize) {
	if (exists(filename)) {
		int capacity = files.find(filename)->second.getFileCapacity();
		int currentDataSize = files.find(filename)->second.getFileDataSize();
		int newDataSize = currentDataSize + dataSize;
		if (dataSize > capacity || capacity < newDataSize) {
			cout << "Lack of memory" << endl;
			return Errors::LACK_OF_MEMORY;
		}

		// this block has been changed to have the oppotunity to write data in file if it has free memory blocks
		else {
			info[dataSize - 1] = '\0';

			for (int i = currentDataSize; i < newDataSize; i++) {
				files.find(filename)->second.getData()[i] = info[i - currentDataSize];
			}
			files.find(filename)->second.setFileDataSize(newDataSize);
			for (int i = 0; i < dataSize; i++) {
				files.find(filename)->second.addToAddress(findEmptyBlock());
			}
			return success();
		}
	}
	else {
		return Errors::FILE_NOT_FOUND;
	}
}

int FileSystem::readFromFile(string filename) {
	if (exists(filename)) {
		File file = files.find(filename)->second;
		char* info = file.getData();
		cout.write(info, file.getFileDataSize());
		cout << endl;
		return success();
	}
	else {
		cout << EXISTANCE_MESSAGE;
		return Errors::FILE_NOT_FOUND;
	}
}

int FileSystem::deleteFile(string filename) {
	if (exists(filename)) {
		files.erase(filename);
		return success();
	}
	else {
		cout << EXISTANCE_MESSAGE << endl;
		return Errors::FILE_NOT_FOUND;
	}
}

int FileSystem::copyFile(string fileFrom, string fileTo) {
	if (exists(fileFrom)) {
		File file = files.find(fileFrom)->second;
		files.insert(pair<string, File>(fileTo, file));
		return success();
	}
	else {
		cout << EXISTANCE_MESSAGE << endl;
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
		cout << EXISTANCE_MESSAGE << endl;
		return Errors::FILE_NOT_FOUND;
	}

}

int FileSystem::dir() {
	cout << "-----------------------------" << endl;
	for (auto& filename : getFileNames()) {
		cout << filename << endl;
	}
	cout << "-----------------------------" << endl;
	return Errors::SUCCESS;
}

FileSystem::~FileSystem() {
	delete memory;
}

// creates dump file, rewrites if it already exists
int FileSystem::createDump() {
	fstream  fbin("dump.dmp", ios::binary | ios::out);
	if (fbin)
	{
		for (auto& file : files) {
			int nameLength = file.first.length();
			int dataSize = file.second.getFileDataSize();
			fbin.write((char*)&nameLength, sizeof(int));
			fbin.write((char*)file.first.c_str(), sizeof(char) * file.first.length());
			fbin.write((char*)&dataSize, sizeof(int));
			fbin.write((char*)file.second.getData(), sizeof(char) * file.second.getFileCapacity());
			fbin.write((char*)file.second.address, sizeof(int) * file.second.getFileCapacity());
		}
		fbin.close();
		return success();
	}
}

int FileSystem::loadDump() {
	fstream fbin;
	fbin.open("dump.dmp", ios::in | ios::binary);
	if (fbin)
	{
		while (!fbin.eof()) {
			File file;
			char* info = new char[file.getFileCapacity()];
			int* address = new int[file.getFileCapacity()];

			int nameLength;
			fbin.read((char*)&nameLength, sizeof(int));
			char* name = new char[nameLength];
			fbin.read((char*)name, sizeof(char) * nameLength);

			int dataSize;
			fbin.read((char*)&dataSize, sizeof(int));
			fbin.read((char*)info, sizeof(char) * file.getFileCapacity());
			fbin.read((char*)address, sizeof(int) * file.getFileCapacity());

			file.setFileDataSize(dataSize);
			file.setData(info);
			file.address = address;
			files.insert(pair<string, File>(string(name).substr(0, nameLength), file));
		}
		files.erase(prev(files.end()));
		fbin.close();
	}
	return success();
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
			memory[blockIndex] = '1';
			break;
		}
	}
	return emptyBlockIndex;
}

void FileSystem::setIntoMemory(int emptyBlock, string filename) {
	File file;
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

void FileSystem::occupyTheBlock(int number) {
	memory[number] = '1';
}
