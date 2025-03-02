#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
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

void invalid_entry() {
	std::cout << "Invailid entry, please make another selection";
}

bool verify_int(const std::string& input) {
	for (int i = 0; i < input.length(); i++) {
		if (!std::isdigit(input[i])) {
			return true;
		}
	}
	
	return false;
}

void print_archive(const library* archive, int num_books) {
	for (int i = 0; i < num_books; i++) {
		archive[i].print();
	}
}

void print_available_books(const library* archive, int num_books) {
	for (int i = 0; i < num_books; i++) {
		if (archive[i].get_reserved() == "No") {
			archive[i].print();
		}
	}
}

int get_num_authors(const library* archive, int num_books) {
	int num_authors = 0;

	for (int i = 0; i < num_books; i++) {
		bool author_needs_added_to_counter = true;

		for (int j = i + 1; j < num_books; j++) {
			if (archive[i].get_author().compare(archive[j].get_author()) == false) {
				author_needs_added_to_counter = false;
			}
		}

		if (author_needs_added_to_counter == true) {
			num_authors++;
		}
	}

	return num_authors;
}

std::string* build_array_of_authors(const library* archive, int num_books, int num_authors) {
	std::string* authors = new std::string[num_authors];

	for (int i = 0; i < num_books; i++) {
		bool author_needs_added_to_authors = true;

		for (int j = 0; j < num_authors; j++) {
			if (archive[i].get_author().compare(authors[j]) == false) {
				author_needs_added_to_authors = false;
			}
		}

		if (author_needs_added_to_authors == true) {
			bool author_added = false;

			for (int j = 0; j < num_authors; j++) {
				if (authors[j].empty() == true && author_added == false) {
					authors[j] = archive[i].get_author();
					author_added = true;
				}
			}
		}
	}

	return authors;
}

void print_authors(const std::string* authors, int num_authors) {
	std::cout << "Authors" << std::endl;

	for (int i = 0; i < num_authors; i++) {
		std::cout << i + 1 << " " << authors[i] << std::endl;
	}
}

int menu() {
	std::cout << std::endl << "Main Menu" << std::endl
		<< "1 Print out all the books owned by the library" << std::endl 
		<< "2 Print out all of the books that are currently available to check out" << std::endl 
		<< "3 Print out all the books by given author" << std::endl 
		<< "4 Print out all the books published on or after a given year" << std::endl 
		<< "5 Sort all the books in the library by page length" << std::endl 
		<< "6 Print out all the information about a single book by searching its title" << std::endl 
		<< "7 Check out a book" << std::endl 
		<< "8 Return a book" << std::endl 
		<< "9 Quit" << std::endl;

	int selected = 0;
	std::string line;

	do {
		std::cout << std::endl << "Select 1 - 9: ";
		
		std::getline(std::cin, line);

		if (verify_int(line) == true 
			|| line.empty() == true
			|| std::stoi(line) < 1 
			|| std::stoi(line) > 9) {
			
			std::cout << std::endl;
			invalid_entry();
		}
		else {
			selected = std::stoi(line);
		}

	} while (selected == 0);

	std::cout << std::endl;

	return selected;
}

void menu_selection(int selected, const library* archive, int num_books, 
		const std::string* authors, int num_authors) {
	switch (selected) {
	case 1:
		print_archive(archive, num_books);
		break;
	case 2:
		print_available_books(archive, num_books);
		break;
	case 3:
		print_authors(authors, num_authors);
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		std::cout << "Thank you, have a great day" << std::endl;
		break;
	default:
		invalid_entry();
		break;
	}
}

int main() {
	std::string path = "Data\\Library-List.csv";

	int num_books = get_line_count(path) - 1;

	library* archive = fill_archive(path, num_books);

	int num_authors = get_num_authors(archive, num_books);

	std::string* authors = build_array_of_authors(archive, num_books, num_authors);

	int selected = 0;

	do {
		selected = menu();
		menu_selection(selected, archive, num_books, authors, num_authors);

	} while (selected != 9);

	delete[] authors;
	delete[] archive;

	return 0;
}