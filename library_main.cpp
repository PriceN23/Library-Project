/*
Midterm Project Default Proposal
CompSci 222 - 01	03/09/2025
Troy Poniewaz & Nicholas Price 
Stretch Goals
1.
2.
3.
*/
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>
#include "library.h"

void invalid_entry() {
	std::cout << "Invailid entry, please make another selection: ";
}

void end_message() {
	std::cout << "Thank you, have a great day" << std::endl;
}

bool verify_int(const std::string& input) {
	for (int i = 0; i < input.length(); i++) {
		if (!std::isdigit(input[i])) {
			return false;
		}
	}

	return true;
}

int verify_input() {
	int selected = 0;
	std::string line;

	do {
		std::getline(std::cin, line);

		if (verify_int(line) == false || line.empty() == true) {

			invalid_entry();
		}
		else {
			selected = std::stoi(line);
		}
	} while (selected == 0);

	return selected;
}

int verify_input(int lower_bound, int upper_bound) {
	int selected = 0;
	std::string line;
	
	do {
		std::getline(std::cin, line);

		if (verify_int(line) == false || line.empty() == true
			|| std::stoi(line) < lower_bound || std::stoi(line) > upper_bound) {

			invalid_entry();
		}
		else {
			selected = std::stoi(line);
		}
	} while (selected < lower_bound || selected > upper_bound);

	return selected;
}

std::string verify_input(bool title_available, const library* archive, int num_books) {
	std::string title = "Unknown";
	std::string available = "Yes";
	int selected = 0;

	if (title_available == false) {
		available = "No";
	}

	do {
		std::getline(std::cin, title);

		if (verify_int(title) == true && title.empty() == false && std::stoi(title) == 1) {
			selected = std::stoi(title);
		}

		if (selected == 0) {
			for (int i = 0; i < num_books; i++) {
				if (archive[i].get_title().compare(title) == false && archive[i].get_reserved() == available) {
					if (title_available == true) {
						title_available == false;
					}
					else {
						title_available == true;
					}
				}
			}

			if (title.empty() == true || title_available == title_available) {
				invalid_entry();
			}
		}
	} while (title_available == title_available && selected == 0);

	return title;
}

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

void sort_page_length_ascending(library* archive, int num_books) {
	for (int i = 0; i < num_books - 1; i++) {
		int min_index = i;

		for (int j = i + 1; j < num_books; j++) {
			if (archive[j].get_page_count() < archive[min_index].get_page_count()) {
				min_index = j;
			}
		}
		if (min_index != i) {
			std::swap(archive[i], archive[min_index]);
		}
	}
}

void sort_page_length_descending(library* archive, int num_books) {
	for (int i = 0; i < num_books - 1; i++) {
		int max_index = i;

		for (int j = i + 1; j < num_books; j++) {
			if (archive[j].get_page_count() > archive[max_index].get_page_count()) {
				max_index = j;
			}
		}
		if (max_index != i) {
			std::swap(archive[i], archive[max_index]);
		}
	}
}

void sort_alphabetical_ascending(library* archive, int num_books) {
    for (int i = 0; i < num_books - 1; i++) {
        int min_index = i;

        for (int j = i + 1; j < num_books; j++) {
            if (archive[j].get_title() < archive[min_index].get_title()) {
                min_index = j;
            }
        }
        if (min_index != i) {
            std::swap(archive[i], archive[min_index]);
        }
    }
}

void sort_alphabetical_descending(library* archive, int num_books) {
    for (int i = 0; i < num_books - 1; i++) {
        int max_index = i;

        for (int j = i + 1; j < num_books; j++) {
            if (archive[j].get_title() > archive[max_index].get_title()) {
                max_index = j;
            }
        }
        if (max_index != i) {
            std::swap(archive[i], archive[max_index]);
        }
    }
}

// Stretch goal #1
void selection_sort(library* archive, int num_books, int selected) {
	switch (selected) {
	case 1:
		sort_page_length_ascending(archive, num_books);
		break;
	case 2:
		sort_page_length_descending(archive, num_books);
		break;
	case 3:
		sort_alphabetical_ascending(archive, num_books); 
		break;
	case 4:
		sort_alphabetical_descending(archive, num_books); 
		break;
	default:
		break;
	}
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
		bool add_author = true;

		for (int j = 0; j < num_authors; j++) {
			if (archive[i].get_author().compare(authors[j]) == false) {
				add_author = false;
			}
		}

		if (add_author == true) {
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

int get_oldest_book(const library* archive, int num_books) {
	int oldest_book = 2030;

	for (int i = 0; i < num_books; i++) {
		if (archive[i].get_published() < oldest_book) {
			oldest_book = archive[i].get_published();
		}
	}

	return oldest_book;
}

int get_newest_book(const library* archive, int num_books) {
	int newest_book = 0;

	for (int i = 0; i < num_books; i++) {
		if (archive[i].get_published() > newest_book) {
			newest_book = archive[i].get_published();
		}
	}

	return newest_book;
}

// Stretch goal #1
void prompt_sort(library* archive, int num_books) {
	std::cout << "Sort library archive" << std::endl 
		<< "1 Ascending order" << std::endl 
		<< "2 Descending order" << std::endl
		<< "3 Ascending alphabetical order" << std::endl
		<< "4 Descending alphabetical order" << std::endl;

	std::cout << std::endl << "Enter 1, 2, 3 or 4 to make selection: ";

	int selected = 0;
	selected = verify_input(1, 2);

	/*int selected = 0;
	std::string line;

	do {
		std::getline(std::cin, line);

		if (verify_int(line) == false
			|| line.empty() == true
			|| std::stoi(line) < 1
			|| std::stoi(line) > 4) {

			invalid_entry();
		}
		else {
			selected = std::stoi(line);
		}
	} while (selected == 0);*/

	selection_sort(archive, num_books, selected);

	std::cout << std::endl << "Sort successful!" << std::endl;
}

void print_archive(const library* archive, int num_books) {
	std::cout << "Library archive" << std::endl;

	for (int i = 0; i < num_books; i++) {
		archive[i].print();
	}
}

void print_archive_titles(const library* archive, int num_books) {
	for (int i = 0; i < num_books; i++) {
		std::cout << archive[i].get_title() << std::endl;
	}
}

void print_available_books(const library* archive, int num_books) {
	std::cout << "Available books in library archive" << std::endl;
	
	for (int i = 0; i < num_books; i++) {
		if (archive[i].get_reserved() == "No") {
			archive[i].print();
		}
	}
}

void print_checked_out_books(const library* archive, int num_books) {
	std::cout << "Books able to be returned to library archive" << std::endl;

	for (int i = 0; i < num_books; i++) {
		if (archive[i].get_reserved() == "Yes") {
			archive[i].print();
		}
	}
}

void print_authors(const std::string* authors, int num_authors) {
	std::cout << "Authors" << std::endl;

	for (int i = 0; i < num_authors; i++) {
		std::cout << i + 1 << " " << authors[i] << std::endl;
	}
}

void print_books_of_selected_author(const library* archive, int num_books, const std::string* authors, int num_authors) {
	std::cout << std::endl << "Select author 1 - " << num_authors << " to print book list: ";

	int selected = 0;
	selected  = verify_input(1, num_authors);

	/*int selected = 0;
	std::string line;

	do {
		std::getline(std::cin, line);

		if (verify_int(line) == false
			|| line.empty() == true
			|| std::stoi(line) < 1
			|| std::stoi(line) > num_authors) {

			invalid_entry();
		}
		else {
			selected = std::stoi(line);
		}
	} while (selected < 1 || selected > num_authors);*/

	selected--;
	std::cout << std::endl;

	for (int i = 0; i < num_books; i++) {
		if (archive[i].get_author().compare(authors[selected]) == false) {
			archive[i].print();
		}
	}
}

void print_books_after_certain_year(const library* archive, int num_books) {
	int oldest_book = get_oldest_book(archive, num_books);
	int newest_book = get_newest_book(archive, num_books);

	std::cout << "Date range of books currently in library archive " << oldest_book << " - " << newest_book << std::endl;
	std::cout << "Enter year to display all books published on or after entered date: ";

	int selected = 0;
	selected = verify_input();

	/*int selected = 0;
	std::string line;

	do {
		std::getline(std::cin, line);

		if (verify_int(line) == false
			|| line.empty() == true) {

			invalid_entry();
		}
		else {
			selected = std::stoi(line);
		}
	} while (selected == 0);*/

	std::cout << std::endl;

	for (int i = 0; i < num_books; i++) {
		if (archive[i].get_published() >= selected) {
			archive[i].print();
		}
	}
}

void back_to_menu() {
	std::cout << std::endl << "Press 1 to return back to menu: ";

	int selected = 0;
	std::string line;

	do {
		std::getline(std::cin, line);

		if (verify_int(line) == false || line.empty() == true || std::stoi(line) != 1) {
			invalid_entry();
		}
		else {
			selected = std::stoi(line);
		}
	} while (selected != 1);
}

void list_of_titles(const library* archive, int num_books) {
	std::cout << "Titles in library archive" << std::endl;

	print_archive_titles(archive, num_books);

	std::string title = "Unknown";
	bool title_available = false;
	int selected = 0;

	std::cout << std::endl << "Titles are case and space sensitive, enter 1 to return to menu" << std::endl;
	std::cout << "Enter title of book to print all informaiton on that title: ";

	do {
		std::getline(std::cin, title);

		if (verify_int(title) == true && title.empty() == false && std::stoi(title) == 1) {
			selected = std::stoi(title);
		}

		if (selected == 0) {
			for (int i = 0; i < num_books; i++) {
				if (archive[i].get_title().compare(title) == false) {
					title_available = true;
				}
			}

			if (title.empty() == true || title_available == false) {
				invalid_entry();
			}
		}
	} while (title_available == false && selected == 0);

	std::cout << std::endl;

	for (int i = 0; i < num_books; i++) {
		if (archive[i].get_title() == title) {
			archive[i].print();

			back_to_menu();
		}
	}
}

// modify this for stech goal 5.
void check_out_book(library* archive, int num_books) {
	print_available_books(archive, num_books);

	std::string title = "Unknown";
	/*bool title_available = false;
	int selected = 0;*/

	std::cout << std::endl << "Titles are case and space sensitive, enter 1 to return to menu" << std::endl;
	std::cout << "Enter title of book to check out: ";

	title = verify_input(false, archive, num_books);

	/*do {
		std::getline(std::cin, title);

		if (verify_int(title) == true && title.empty() == false && std::stoi(title) == 1) {
			selected = std::stoi(title);
		}

		if (selected == 0) {
			for (int i = 0; i < num_books; i++) {
				if (archive[i].get_title().compare(title) == false && archive[i].get_reserved() == "No") {
					title_available = true;
				}
			}

			if (title.empty() == true || title_available == false) {
				invalid_entry();
			}
		}		
	} while (title_available == false && selected == 0);*/

	std::cout << std::endl;

	for (int i = 0; i < num_books; i++) {
		if (archive[i].get_reserved() == "No" && archive[i].get_title() == title) {
			archive[i].set_reserved("Yes");
			std::cout << "Checked out '" << title << "' successfully" << std::endl;

			back_to_menu();
		}
	}
}

void reshelf_book(library* archive, int num_books) {
	print_checked_out_books(archive, num_books);

	std::string title = "Unknown";
	/*bool title_available = true;
	int selected = 0;*/

	std::cout << std::endl << "Titles are case and space sensitive, enter 1 to return to menu" << std::endl;
	std::cout << "Enter title of book to return: ";

	title = verify_input(true, archive, num_books);

	/*do {
		std::getline(std::cin, title);

		if (verify_int(title) == true && title.empty() == false && std::stoi(title) == 1) {
			selected = std::stoi(title);
		}

		if (selected == 0) {
			for (int i = 0; i < num_books; i++) {
				if (archive[i].get_title().compare(title) == false && archive[i].get_reserved() == "Yes") {
					title_reserved = false;
				}
			}
			if (title.empty() == true || title_reserved == true) {
				invalid_entry();
			}
		}
	} while (title_reserved == true && selected == 0);*/

	std::cout << std::endl;

	for (int i = 0; i < num_books; i++) {
		if (archive[i].get_reserved() == "Yes" && archive[i].get_title() == title) {
			archive[i].set_reserved("No");
			std::cout << "Returned '" << title << "' successfully" << std::endl;

			back_to_menu();
		}
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

	std::cout << std::endl << "Enter 1 - 9 to make a selection: ";

	int selected = 0;
	selected = verify_input(1, 9);

	/*int selected = 0;
	std::string line;

	do {
		std::getline(std::cin, line);

		if (verify_int(line) == false 
			|| line.empty() == true
			|| std::stoi(line) < 1 
			|| std::stoi(line) > 9) {
			
			invalid_entry();
		}
		else {
			selected = std::stoi(line);
		}
	} while (selected == 0);*/

	std::cout << std::endl;

	return selected;
}

void menu_selection(int selected, library* archive, int num_books, 
		const std::string* authors, int num_authors) {
	switch (selected) {
	case 1:
		// Print out all the books owned by the library
		print_archive(archive, num_books);
		back_to_menu();
		break;
	case 2:
		// Print out all the books which are currently available to check out
		print_available_books(archive, num_books);
		back_to_menu();
		break;
	case 3:
		// Print out all the books by a give author
		print_authors(authors, num_authors);
		print_books_of_selected_author(archive, num_books, authors, num_authors);
		back_to_menu();
		break;
	case 4:
		// Print out all the books published on or after a given year
		print_books_after_certain_year(archive, num_books);
		back_to_menu();
		break;
	case 5:
		// Sort all of the books owned by the library by page length
		prompt_sort(archive, num_books);
		back_to_menu();
		break;
	case 6:
		// Print out all the information about a single book by searching its title
		list_of_titles(archive, num_books);
		back_to_menu();
		break;
	case 7:
		// Check out a book
		check_out_book(archive, num_books);
		break;
	case 8:
		// Return a book
		reshelf_book(archive, num_books);
		break;
	case 9:
		// Quit
		end_message();
		break;
	default:
		invalid_entry();
		back_to_menu();
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