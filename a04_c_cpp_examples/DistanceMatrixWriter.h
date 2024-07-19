#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

template<class T>
class DistanceMatrixWriter
{
public:
	DistanceMatrixWriter(std::string filename);
	~DistanceMatrixWriter();
	T** writeRows(T** storage, int numRows, int numCols);

private:
	std::ofstream* file = NULL;
	std::string filename = "";
};

template<class T>
DistanceMatrixWriter<T>::DistanceMatrixWriter(std::string filename) {
	this->filename = filename;
	if (filename.size() > 0) {
		file = new std::ofstream(filename);
		if (*file) {
			if (!file->is_open()) {
				std::cout << "Failed to open file: " << filename << std::endl;
				delete file;
				file = NULL;
			}
			std::cout << filename << " is open for writing." << std::endl;
		}
	}
};

template<class T>
DistanceMatrixWriter<T>::~DistanceMatrixWriter() {
	if (file) {
		file->close();
		delete file;
		std::cout << "DistanceMatrixWriter ends." << std::endl;
	}
};

template<class T>
T** DistanceMatrixWriter<T>::writeRows(T** storage, int numRows, int numCols) {
	if (file == NULL) {
		return NULL;
	}
	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			*file << std::fixed << std::setprecision(4) << storage[row][col] << " ";
		}
		*file << std::endl;
	}
	std::cout << numRows << " rows was written to file." << std::endl;
	return storage;
}