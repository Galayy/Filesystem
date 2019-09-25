#include "File.h"

void File::addToAddress(int blockIndex) {
	for (int i = 0; i < FILE_SIZE; i++) {
		if (address[i] == '\0') {
			address[i] = blockIndex;
			break;
		}
	}
}