#include "File.h"

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