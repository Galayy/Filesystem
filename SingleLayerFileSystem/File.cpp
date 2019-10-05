#include "File.h"
#include <iostream>

using namespace std;

void File::addToAddress(int blockIndex) {
	for (int i = 0; i < FILE_SIZE; i++) {
		if (address[i] == '\0') {
			address[i] = blockIndex;
			break;
		}
	}
}

void File::set_data(char* info) {
	data = info;
}

char* File::get_data() {
	return data;
}

void File::set_file_data_size(int data_size) {
	file_data_size = data_size;
}

int File::get_file_data_size() {
	return file_data_size;
}

int File::get_file_capacity() {
	return FILE_SIZE;
}

char* File::get_address() {
	char* address_to_return = new char[file_data_size];
	for (int i = 0; i < file_data_size; i++) {
		address_to_return[i] = static_cast<char>(address[i]);
		//cout << char(address[i]);
	}
	return address_to_return;
}