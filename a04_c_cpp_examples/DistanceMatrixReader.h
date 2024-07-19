#pragma once
#include <string>
#include <iostream>
#include <fstream>

template<class T>
class DistanceMatrixReader
{
public:
	DistanceMatrixReader(std::string filename);
	~DistanceMatrixReader();
	T** readRows(T** storage, int numRows, int numCols);

private:
	std::ifstream* file = NULL;
	std::string filename = "";
};

template<class T>
DistanceMatrixReader<T>::DistanceMatrixReader(std::string filename) {
	this->filename = filename;
	if (filename.size() > 0) {
		file = new std::ifstream(filename);
		if (*file) {
			if (!file->is_open()) {
				std::cout << "Failed to open file: " << filename << std::endl;
				delete file;
				file = NULL;
			}
			std::cout << filename << " is open for reading." << std::endl;
		}
	}
};

template<class T>
DistanceMatrixReader<T>::~DistanceMatrixReader() {
	if (file) {
		file->close();
		delete file;
		std::cout << "DistanceMatrixReader ends." << std::endl;
	}
};

template<class T>
T** DistanceMatrixReader<T>::readRows(T** storage, int numRows, int numCols) {
	if (file == NULL || !file->is_open()) {
		return NULL;
	}

	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			try {
				*file >> storage[row][col];
			}
			catch (std::ifstream::failure e) {
				std::cout << "IOException: " << e.what() << std::endl;
			}
		}
	}

	std::cout << numRows << " rows was read." << std::endl;
	return storage;
}
