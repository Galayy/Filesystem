#pragma once

#include <stdlib.h>
#include <vector>

using namespace std;

class File {
private:
	vector<char> data;
	int fileDataSize;
public:
	File();
	vector<int> address;

	void addToAddress(int);
	void setFileDataSize(int);
	void setData(vector<char> info);

	vector<char> getData();

	int getFileDataSize();
	~File();
};
