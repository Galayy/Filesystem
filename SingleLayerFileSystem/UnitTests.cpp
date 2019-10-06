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

	writeInFile_happyPath();
	writeInFileWhenLackOfMemory();
	writeInFileNotFound();
	clear();

	/*readFromFile_happyPath();
	readFromFileNotFound();
	clear();*/

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


//---------------------WRITE_BLOCK-------------------

void UnitTests::writeInFile_happyPath() {
	init(MEMORY_SIZE);
	testFileSystem->createFile(FILE_NAME);
	char RIGHT_DATA[25] = "this is the wright data";
	int output = testFileSystem->write_in_file(FILE_NAME,&RIGHT_DATA[0], 25);
	assert(output == Errors::SUCCESS);
}

void UnitTests::writeInFileNotFound() {
	init(MEMORY_SIZE);
	//testFileSystem->write_in_file(FILE_NAME);
	char RIGHT_DATA[25] = "this is the wright data";
	int output = testFileSystem->write_in_file(FILE_NAME, &RIGHT_DATA[0], 25);
	assert(output == Errors::FILE_NOT_FOUND);
}
// I have some doubts about Memory_size because it's different lack of memory
void UnitTests::writeInFileWhenLackOfMemory() {
	init(MEMORY_SIZE);//???
	testFileSystem->createFile(FILE_NAME);
	char WRONG_DATA[75] = "hhssfjshfjshf skhfkjdhfsjhfk sdjfhsjhfshfdks skfhdjfhdsfh sdjjfhsdjkfhskfh";
	int output = testFileSystem->write_in_file(FILE_NAME, &WRONG_DATA[0], 75);
	assert(output == Errors::LACK_OF_MEMORY);
}
//---------------------WRITE_BLOCK-------------------


//---------------------READ_BLOCK-------------------
void UnitTests::readFromFile_happyPath() {
	init(MEMORY_SIZE);
	testFileSystem->createFile(FILE_NAME);
	int firstOutput = testFileSystem->read_from_file(FILE_NAME);
	int output = testFileSystem->read_from_file(FILE_NAME);
	assert(output == Errors::SUCCESS);
}

void UnitTests::readFromFileNotFound() {
	init(MEMORY_SIZE);
	int firstOutput = testFileSystem->read_from_file(FILE_NAME);
	int output = testFileSystem->read_from_file(FILE_NAME);
	assert(output == Errors::FILE_NOT_FOUND);
}
//---------------------READ_BLOCK-------------------