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

int FileSystem::moveFile(string fileFrom, string fileTo) {
	if (exists(fileFrom)) {
		File* file = files.at(fileFrom);
		if (fileNotNull(file)) {
			files.insert(pair<string, File*>(fileTo, file));
			return deleteFile(fileFrom);
		}
		else {
			return fileError(FILE_ERROR_MESSAGE);
		}
	}
	else {
		cout << EXISTANCE_MESSAGE << endl;
		return Errors::FILE_NOT_FOUND;
	}
}

int FileSystem::writeInFile(string filename, char* info, int dataSize) {
	if (exists(filename)) {
		int capacity = files.at(filename)->getFileCapacity();
		int currentDataSize = files.at(filename)->getFileDataSize();
		int newDataSize = currentDataSize + dataSize;

		if (dataSize > capacity || capacity < newDataSize) {
			cout << "Lack of memory" << endl;
			return Errors::LACK_OF_MEMORY;
		}
		else {
			for (int i = currentDataSize; i < newDataSize; i++) {
				files.at(filename)->getData()[i] = info[i - currentDataSize];
			}

			File* file = files.at(filename);

			if (fileNotNull(file)) {
				file->setFileDataSize(newDataSize);

				for (int i = 0; i < dataSize; i++) {
					files.at(filename)->addToAddress(findEmptyBlock());
				}
				return success();
			}
			else {
				return fileError(FILE_ERROR_MESSAGE);
			}
		}
	}
	else {
		return Errors::FILE_NOT_FOUND;
	}
}

int FileSystem::readFromFile(string filename) {
	if (exists(filename)) {
		File* file = files.at(filename);
		char* info = file->getData();
		cout << "--------------" << endl;
		cout.write(info, file->getFileDataSize());
		cout << "\n--------------" << endl;
		return success();
	}
	else {
		cout << EXISTANCE_MESSAGE << endl;
		return Errors::FILE_NOT_FOUND;
	}
}

int FileSystem::deleteFile(string filename) {
	if (exists(filename)) {
		removeFile(filename);
		return success();
	}
	else {
		cout << EXISTANCE_MESSAGE << endl;
		return Errors::FILE_NOT_FOUND;
	}
}

int FileSystem::copyFile(string fileFrom, string fileTo) {
	if (exists(fileFrom)) {
		File* file = files.at(fileFrom);
		if (fileNotNull(file)) {
			files.insert(pair<string, File*>(fileTo, file));
			return success();
		}
		else {
			return fileError(FILE_ERROR_MESSAGE);
		}

	}
	else {
		cout << EXISTANCE_MESSAGE << endl;
		return Errors::FILE_NOT_FOUND;
	}
}

int FileSystem::dir() {
	cout << "-----------------------------" << endl;
	for (pair<string, File*> pairFile : files) {
		cout << pairFile.first << endl;
	}
	cout << "-----------------------------" << endl;
	return Errors::SUCCESS;
}

FileSystem::~FileSystem() {
	for (pair<string, File*> pairFile : files) {
		removeFile(pairFile.first);
	}
	delete memory;
}

int FileSystem::createDump() {
	fstream  fbin("dump.dmp", ios::binary | ios::out);
	if (fbin) {
		for (pair<string, File*> pairFile : files) {
			int nameLength = pairFile.first.length();
			int dataSize = pairFile.second->getFileDataSize();
			fbin.write((char*)& nameLength, sizeof(int));
			fbin.write((char*)pairFile.first.c_str(), sizeof(char) * pairFile.first.length());
			fbin.write((char*)& dataSize, sizeof(int));
			fbin.write((char*)pairFile.second->getData(), sizeof(char) * pairFile.second->getFileCapacity());
			fbin.write((char*)pairFile.second->address, sizeof(char) * pairFile.second->getFileCapacity());
		}
		fbin.close();
		return success();
	}
	else {
		return fileError("Error while creating dump");
	}
}

int FileSystem::loadDump() {
	fstream fbin;
	string filename;
	fbin.open("dump.dmp", ios::in | ios::binary);

	if (fbin) {
		while (!fbin.eof()) {
			File* file = new File();
			char* info = new char[file->getFileCapacity()];
			char* address = new char[file->getFileCapacity()];

			int nameLength;
			fbin.read((char*)& nameLength, sizeof(int));
			char* name = new char[nameLength];
			fbin.read((char*)name, sizeof(char) * nameLength);

			int dataSize;
			fbin.read((char*)& dataSize, sizeof(int));
			fbin.read((char*)info, sizeof(char) * file->getFileCapacity());
			fbin.read((char*)address, sizeof(char) * file->getFileCapacity());

			file->setFileDataSize(dataSize);
			file->setData(info);
			file->address = address;
			filename = string(name).substr(0, nameLength);

			if (fileNotNull(file)) {
				files.insert(pair<string, File*>(string(name).substr(0, nameLength), file));
			}
		}
		removeFile(filename);
		fbin.close();
		return success();
	}
	else {
		return fileError("Error while loading dump");
	}

}

//PRIVATE
bool FileSystem::exists(string filename) {
	bool exists = false;
	for (pair<string, File*> pairFile : files) {
		if (filename == pairFile.first) {
			exists = true;
			break;
		}
	}
	return exists;
}

bool FileSystem::fileNotNull(File* file) {
	return file != NULL;
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
	File* file = new File();
	if (fileNotNull(file)) {
		files.insert(pair<string, File*>(filename, file));
	}
}

int FileSystem::fileError(string errorMessage) {
	cout << errorMessage << endl;
	return Errors::FILE_ERROR;
}

int FileSystem::success() {
	cout << SUCCESS_MESSAGE << endl;
	return Errors::SUCCESS;
}

void FileSystem::occupyTheBlock(int number) {
	memory[number] = '1';
}

void FileSystem::removeFile(string filename) {
	File* file = files.at(filename);
	if (fileNotNull(file)) {
		delete file;
	}
	files.erase(filename);
}
