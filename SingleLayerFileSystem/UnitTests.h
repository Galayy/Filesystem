#pragma once

#include <string>
#include "Errors.h"
#include "Command.h"
#include "FileSystem.h"

class UnitTests {
private:
	const int MEMORY_SIZE = 1024;
	const string FILE_NAME = "test_file_name";
	const string ANOTHER_FILE_NAME = "another_test_file_name";
	const string WRONG_COMMAND = "test_file_name";

	Command* command;
	FileSystem* testFileSystem;
	vector<string> commandNames;

	void clear();
	void init(int memorySize);

	void createFile_happyPath();
	void createFileWhenLackOfMemory();
	void createFileWhenFileAlreadyExists();

	void deleteFile_happyPath();
	void deleteFileWhenNotFound();

	void copyFile_happyPath();
	void copyFileWhenNotFound();

	void moveFile_happyPath();
	void moveFileWhenNotFound();

	void performWithWrongCommand();
	void performWithWrongArguments();

public:
	void runTests();
};