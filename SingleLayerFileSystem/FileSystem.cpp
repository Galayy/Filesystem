#include <iostream>
#include <map>
#include <windows.h>
#include "FileSystem.h"

using namespace std;

FileSystem::FileSystem(int size) {
	memory = (char*)calloc(size, sizeof(char));
}

File FileSystem::get_file(string filename) {
	return files.find(filename)->second;
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
// Как протестировать???
// Чтобы нормально протестировать нужно тогда передавать три аргумента: filename, char* info, int data_size,
// тогда нужно передавать их из main, а там нужно будет получить доступ к записываемому файлу, то есть нужна будет
// функция типа File FileSystem::getFile(), но её быть не должно (или может быть?), только функции работы с файлами 
int FileSystem::write_in_file(string filename) {
	if (exists(filename)) {
		int file_copacity = files.find(filename)->second.get_file_copacity();
		char* info = new char[file_copacity];
		cin.read(info, file_copacity);
		cin.clear();
		cin.ignore(10000, '\n');
		int data_size = string(info).length();

		if (data_size > file_copacity) {
			cout << "Lack of memory" << endl;
			return Errors::LACK_OF_MEMORY;
		}
		else {
			files.find(filename)->second.set_file_data_size(data_size);
			files.find(filename)->second.set_data(info);
			for (int i = 0; i < data_size; i++) {
				files.find(filename)->second.addToAddress(findEmptyBlock());
			}
			success();
		}
	}
	else {
		return Errors::FILE_NOT_FOUND;
	}
}

int FileSystem::read_from_file(string filename) {
	if (exists(filename)) {
		File file = files.find(filename)->second;
		char* info = file.get_data();
		for (int i = 0; i < file.get_file_data_size; i++) {
			cout << info[i];
		}
		cout << endl;
		success();
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
	} else {
		cout << EXISTANCE_MESSAGE << endl;
		return Errors::FILE_NOT_FOUND;
	} 
}

int FileSystem::copyFile(string fileFrom, string fileTo) {
	if (exists(fileFrom)) {
		File file = files.find(fileFrom)->second;
		files.insert(pair<string, File>(fileTo, file));
		return success();
	} else {
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
