#pragma once

#include<map>
#include<string>

using namespace std;

class Errors {
public:
	static const short FILE_ERROR = 11;
	static const short WRONG_INPUT = 10;
	static const short FILE_NOT_FOUND = 2;
	static const short FILE_ALREADY_EXISTS = 1;
	static const short SUCCESS = 0;
	static const short LACK_OF_MEMORY = -1;
};
