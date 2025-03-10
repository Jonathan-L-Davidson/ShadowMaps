#pragma once

#ifndef FILEHELPERS_H
#define FILEHELPERS_H
#include <fstream>

namespace Helpers {
	// Helper to check if a file exists from a given path, returns 1 if it exists, 0 if not.
	// Based off of a guide from https://www.tutorialspoint.com/the-best-way-to-check-if-a-file-exists-using-standard-c-cplusplus
	bool FileExists(const char* path) {
		std::ifstream file;

		file.open(path);

		if (file) {
			file.close();
			return true;
		}
		file.close();
		return false;
	};
};

#endif // !FILEHELPERS_H
