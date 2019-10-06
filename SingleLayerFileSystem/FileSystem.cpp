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

int FileSystem::write_in_file(string filename, char* info, int data_size) {
	if (exists(filename)) {
		int capacity = files.find(filename)->second.get_file_capacity();
		int current_data_size = files.find(filename)->second.get_file_data_size();
		int new_data_size = current_data_size + data_size;
		if (data_size > capacity || capacity < new_data_size) {
			cout << "Lack of memory" << endl;
			return Errors::LACK_OF_MEMORY;
		}

		// this block has been changed to have the oppotunity to write data in file if it has free memory blocks
		else {
			info[data_size - 1] = '\0';
			//files.find(filename)->second.set_data(info);

			for (int i = current_data_size; i < new_data_size; i++) {
				files.find(filename)->second.get_data()[i] = info[i - current_data_size];
			}
			files.find(filename)->second.set_file_data_size(new_data_size);
			for (int i = 0; i < data_size; i++) {
				files.find(filename)->second.addToAddress(findEmptyBlock());
			}
			return success();
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
		cout.write(info, file.get_file_data_size());
		//cout.write(info, 9);
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
	//file.addToAddress(emptyBlock);
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

void FileSystem::occupy_the_block(int number) {
	memory[number] = '1';
}

// creates dump file, rewrites if it already exists
int FileSystem::create_dump() {
	fstream  fbin("dump.dmp", ios::binary | ios::out);
	if (fbin)
	{
		for(auto& file:files) {
			int name_length = file.first.length();
			int data_size = file.second.get_file_data_size();
			fbin.write((char*)&name_length, sizeof(int));
			fbin.write((char*)file.first.c_str(), sizeof(char) * file.first.length());
			fbin.write((char*)&data_size, sizeof(int));
			fbin.write((char*)file.second.get_data(), sizeof(char) * file.second.get_file_capacity());
			fbin.write((char*)file.second.address, sizeof(int) * file.second.get_file_capacity());
		}
		fbin.close();
		return success();
	}
}

int FileSystem::load_dump() {
	fstream fbin;
	fbin.open("dump.dmp", ios::in | ios::binary);
	if (fbin)
	{
		while (!fbin.eof()) {
			File file;
			char* info = new char[file.get_file_capacity()];
			int* address = new int[file.get_file_capacity()];
			int name_length;
			fbin.read((char*)&name_length, sizeof(int));
			char* name = new char[name_length];
			fbin.read((char*)name, sizeof(char) * name_length);
			int data_size;
			fbin.read((char*)&data_size, sizeof(int));
			fbin.read((char*)info, sizeof(char) * file.get_file_capacity());
			fbin.read((char*)address, sizeof(int) * file.get_file_capacity());
			file.set_file_data_size(data_size);
			file.set_data(info);
			file.address = address;
			files.insert(pair<string, File>(string(name).substr(0, name_length), file));
		}
		files.erase(prev(files.end()));
		fbin.close();
	}
	return success();
}