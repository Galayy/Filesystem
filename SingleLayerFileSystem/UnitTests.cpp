#include <iostream>
#include <assert.h>
#include "UnitTests.h"

void UnitTests::init(int memorySize) {
	commandNames = { "create", "del", "copy", "move", "cls", "close" };
	command = new Command();
	testFileSystem = new FileSystem(memorySize);
}

void UnitTests::clear() {
	delete command;
	delete testFileSystem;
}

void UnitTests::runTests() {
	createFile_happyPath();
	createFileWhenFileAlreadyExists();
	createFileWhenLackOfMemory();
	clear();

	copyFile_happyPath();
	copyFileWhenNotFound();
	clear();

	deleteFile_happyPath();
	deleteFileWhenNotFound();
	clear();

	moveFile_happyPath();
	moveFileWhenNotFound();
	clear();

	performWithWrongCommand();
	performWithWrongArguments();

	system("CLS");
	cout << "Success running tests" << endl;
}

void UnitTests::performWithWrongCommand() {
	init(MEMORY_SIZE);
	bool validationResult = command->validateInput(WRONG_COMMAND, commandNames);
	assert(validationResult == false);
}

void UnitTests::performWithWrongArguments() {
	init(MEMORY_SIZE);
	vector<string> wordsVector = { "create", "long", "input", "command"};
	int output = command->processInput(wordsVector);
	assert(output == Errors::WRONG_INPUT);
}

//---------------------CREATE_BLOCK-------------------
void UnitTests::createFile_happyPath() {
	init(MEMORY_SIZE);
	int output = testFileSystem->createFile(FILE_NAME);
	assert(output == Errors::SUCCESS);
}

void UnitTests::createFileWhenFileAlreadyExists() {
	init(MEMORY_SIZE);
	testFileSystem->createFile(FILE_NAME);
	int output = testFileSystem->createFile(FILE_NAME);
	assert(output == Errors::FILE_ALREADY_EXISTS);
}

void UnitTests::createFileWhenLackOfMemory() {
	init(0);
	testFileSystem->createFile(FILE_NAME);
	int output = testFileSystem->createFile(FILE_NAME);
	assert(output == Errors::FILE_ALREADY_EXISTS);
}
//---------------------CREATE_BLOCK-------------------

//---------------------DELETE_BLOCK-------------------
void UnitTests::deleteFile_happyPath() {
	init(MEMORY_SIZE);
	testFileSystem->createFile(FILE_NAME);
	int output = testFileSystem->deleteFile(FILE_NAME);
	assert(output == Errors::SUCCESS);
}

void UnitTests::deleteFileWhenNotFound() {
	init(MEMORY_SIZE);
	int output = testFileSystem->deleteFile(FILE_NAME);
	assert(output == Errors::FILE_NOT_FOUND);
}
//---------------------DELETE_BLOCK-------------------

//---------------------COPY_BLOCK-------------------
void UnitTests::copyFile_happyPath() {
	init(MEMORY_SIZE);
	testFileSystem->createFile(FILE_NAME);
	int output = testFileSystem->copyFile(FILE_NAME, ANOTHER_FILE_NAME);
	assert(output == Errors::SUCCESS);
}

void UnitTests::copyFileWhenNotFound() {
	init(MEMORY_SIZE);
	int output = testFileSystem->copyFile(FILE_NAME, ANOTHER_FILE_NAME);
	assert(output == Errors::FILE_NOT_FOUND);
}
//---------------------COPY_BLOCK-------------------

//---------------------MOVE_BLOCK-------------------
void UnitTests::moveFile_happyPath() {
	init(MEMORY_SIZE);
	int firstOutput = testFileSystem->createFile(FILE_NAME);
	int output = testFileSystem->moveFile(FILE_NAME, ANOTHER_FILE_NAME);
	assert(output == Errors::SUCCESS);
}

void UnitTests::moveFileWhenNotFound() {
	init(MEMORY_SIZE);
	int output = testFileSystem->moveFile(FILE_NAME, ANOTHER_FILE_NAME);
	assert(output == Errors::FILE_NOT_FOUND);
}
//---------------------MOVE_BLOCK-------------------