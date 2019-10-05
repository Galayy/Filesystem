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

int FileSystem::write_in_file(string filename, char* info, int data_size) {
	if (exists(filename)) {
		int capacity = files.find(filename)->second.get_file_capacity();
		int current_data_size = files.find(filename)->second.get_file_data_size();
		int new_data_size = current_data_size + data_size;
		if (data_size > capacity|| capacity < new_data_size) { 
			cout << "Lack of memory" << endl;
			return Errors::LACK_OF_MEMORY;
		}

		// this block has been changed to have the oppotunity to write data in file if it has free memory blocks
		else {
			info[data_size-1] = '\n';
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
		cout.write(file.get_data(), file.get_file_data_size());
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

// creates dump file, rewrites if it already exists
int FileSystem::create_dump() {
	FILE* dump;
	ofstream ofs("test"); //создать
	ofs.close();
	/* открытие на запись */
	if ((dump = fopen("dump.txt", "wb")) == NULL) {
		printf("Cannot open file.");
		return Errors::FILE_NOT_FOUND;
	}
	fwrite(&files, sizeof(files), 1, dump);
	fclose(dump);
	return success();
}

int FileSystem::load_dump() {
	FILE* dump;
	if ((dump = fopen("dump.txt", "rb")) == NULL) {
		printf("Cannot open file.");
		return Errors::FILE_NOT_FOUND;
	}
	fread(&files, sizeof(files), 1, dump);
	fclose(dump);
	return success();
}