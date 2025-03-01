#include <iostream>
#include <string>
#include <fstream>
#include "library.h"

int get_line_count(const std::string& path) {
	std::ifstream stream;
	stream.open(path);

	int count = 0;

	if (stream.is_open()) {
		std::string line;
		while (std::getline(stream, line)) {
			count++;
		}
		stream.close();
	}
	return count;
}

library* fill_archive(const std::string& path, int count) {
	library* archive = new library[count];

	std::ifstream stream;
	stream.open(path);

	if (stream.is_open()) {
		std::string line;

		std::getline(stream, line);

		for (int i = 0; i < count; i++) {
			std::getline(stream, line, ',');
			unsigned short published = std::stoi(line);
			
			std::getline(stream, line, ',');
			std::string title = line;

			std::getline(stream, line, ',');
			std::string author = line;

			std::getline(stream, line, ',');
			unsigned short page_count = std::stoi(line);

			std::getline(stream, line, ',');
			std::string genre = line;

			std::getline(stream, line);
			std::string reserved = line;

			archive[i] = library(title, author, genre, page_count, published, reserved);
		}
		stream.close();
	}
	return archive;
}

int main() {
	std::string path = "Data\\Library-List.csv";

	int num_books = get_line_count(path) - 1;

	library* archive = fill_archive(path, num_books);
	
	for (int i = 0; i < num_books; i++) {
		archive[i].print();
	}

	delete[] archive;

	return 0;
}