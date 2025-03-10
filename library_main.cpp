/*
Midterm Project Default Proposal
CompSci 222 - 01	03/09/2025
Troy Poniewaz & Nicholas Price

Files: library.h, library.cpp, library_main.cpp
Stretch Goals
1. Sort books owned by library by their title (alphabetical ascending or descenting order)
2. Donate book to the library
3. Update CSV file with donated books
*/
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "library.h"

void invalid_entry()
{
	std::cout << "Invalid entry, please make another selection: ";
}

void end_message()
{
	std::cout << std::endl << "Update complete, have a great day!" << std::endl;
}

bool verify_int(const std::string &input)
{
	for (int i = 0; i < input.length(); i++)
	{
		if (!std::isdigit(input[i]))
		{
			return false;
		}
	}

	return true;
}

int verify_input()
{
	int selected = 0;
	std::string line;

	do
	{
		std::getline(std::cin, line);

		if (verify_int(line) == false || line.length() <= 0)
		{

			invalid_entry();
		}
		else
		{
			selected = std::stoi(line);
		}
	} while (selected == 0);

	return selected;
}

int verify_input(int lower_bound, int upper_bound)
{
	int selected = 0;
	std::string line;

	do
	{
		std::getline(std::cin, line);

		if (verify_int(line) == false || line.length() <= 0 || std::stoi(line) < lower_bound || std::stoi(line) > upper_bound)
		{

			invalid_entry();
		}
		else
		{
			selected = std::stoi(line);
		}
	} while (selected < lower_bound || selected > upper_bound);

	return selected;
}

std::string verify_input(bool reserved, const library *archive, int num_books)
{

	std::string title = "";
	std::string verify = "Yes";
	bool value = reserved;
	int selected = 0;

	if (reserved == false)
	{
		verify = "No";
	}

	do
	{
		std::getline(std::cin, title);

		if (verify_int(title) == true && title.length() > 0 && std::stoi(title) == 1)
		{
			selected = std::stoi(title);
		}

		if (selected == 0)
		{
			for (int i = 0; i < num_books; i++)
			{
				if (archive[i].get_title().compare(title) == false && archive[i].get_reserved() == verify)
				{
					if (value == false)
					{
						value = true;
					}
					else
					{
						value = false;
					}
				}
			}

			if (title.length() <= 0 || value == reserved)
			{
				invalid_entry();
			}
		}
	} while (value == reserved && selected == 0);

	return title;
}

std::string verify_title(const library *archive, int num_books)
{
	std::string title = "";
	bool title_available = false;
	int selected = 0;

	do
	{
		std::getline(std::cin, title);

		if (verify_int(title) == true && title.length() > 0 && std::stoi(title) == 1)
		{
			selected = std::stoi(title);
		}

		if (selected == 0)
		{
			for (int i = 0; i < num_books; i++)
			{
				if (archive[i].get_title().compare(title) == false)
				{
					title_available = true;
				}
			}

			if (title.length() <= 0 || title_available == false)
			{
				invalid_entry();
			}
		}
	} while (title_available == false && selected == 0);

	return title;
}

int get_line_count(const std::string &path)
{
	std::ifstream stream;
	stream.open(path);

	int count = 0;

	if (stream.is_open())
	{
		std::string line;
		while (std::getline(stream, line))
		{
			count++;
		}
		stream.close();
	}
	return count;
}

void sort_page_length_ascending(library *archive, int num_books)
{
	for (int i = 0; i < num_books - 1; i++)
	{
		int min_index = i;

		for (int j = i + 1; j < num_books; j++)
		{
			if (archive[j].get_page_count() < archive[min_index].get_page_count())
			{
				min_index = j;
			}
		}
		if (min_index != i)
		{
			std::swap(archive[i], archive[min_index]);
		}
	}
}

void sort_page_length_descending(library *archive, int num_books)
{
	for (int i = 0; i < num_books - 1; i++)
	{
		int max_index = i;

		for (int j = i + 1; j < num_books; j++)
		{
			if (archive[j].get_page_count() > archive[max_index].get_page_count())
			{
				max_index = j;
			}
		}
		if (max_index != i)
		{
			std::swap(archive[i], archive[max_index]);
		}
	}
}

void sort_alphabetical_ascending(library *archive, int num_books)
{
	for (int i = 0; i < num_books - 1; i++)
	{
		int min_index = i;

		for (int j = i + 1; j < num_books; j++)
		{
			if (archive[j].get_title() < archive[min_index].get_title())
			{
				min_index = j;
			}
		}
		if (min_index != i)
		{
			std::swap(archive[i], archive[min_index]);
		}
	}
}

void sort_alphabetical_descending(library *archive, int num_books)
{
	for (int i = 0; i < num_books - 1; i++)
	{
		int max_index = i;

		for (int j = i + 1; j < num_books; j++)
		{
			if (archive[j].get_title() > archive[max_index].get_title())
			{
				max_index = j;
			}
		}
		if (max_index != i)
		{
			std::swap(archive[i], archive[max_index]);
		}
	}
}

void selection_sort(library *archive, int num_books, int selected)
{
	switch (selected)
	{
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

library* fill_archive(const std::string &path, int count)
{
	library *archive = new library[count];

	std::ifstream stream;
	stream.open(path);

	if (stream.is_open())
	{
		std::string line;

		std::getline(stream, line);

		for (int i = 0; i < count; i++)
		{
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

library* donate_book(library *archive, int num_books)
{
	library *donated_archive = new library[num_books + 1];
	std::string line;

	for (int i = 0; i < num_books; i++)
	{
		donated_archive[i] = archive[i];
	}

	std::cout << std::endl
			  << "Title name: ";
	std::string title = "";
	do
	{
		std::getline(std::cin, line);

		if (line.length() > 0)
		{
			title = line;
		}
		else
		{
			invalid_entry();
		}
	} while (title == "");

	std::cout << "Published year: ";
	unsigned short published = 0;

	do
	{
		std::getline(std::cin, line);

		if (verify_int(line) == true && line.length() > 0 && std::stoi(line) > 0 && std::stoi(line) <= 2025)
		{
			published = std::stoi(line);
		}
		else
		{
			invalid_entry();
		}
	} while (published == 0);

	std::cout << "Author's name: ";
	std::string author = "";
	do
	{
		std::getline(std::cin, line);

		if (line.length() > 0)
		{
			author = line;
		}
		else
		{
			invalid_entry();
		}
	} while (author == "");

	std::cout << "Page Count: ";
	unsigned short page_count = 0;
	do
	{
		std::getline(std::cin, line);

		if (verify_int(line) == true && line.length() > 0 && std::stoi(line) > 0 && std::stoi(line) <= 65500)
		{
			page_count = std::stoi(line);
		}
		else
		{
			invalid_entry();
		}
	} while (page_count == 0);

	std::cout << "Genre: ";
	std::string genre = "";
	do
	{
		std::getline(std::cin, line);

		if (line.length() > 0)
		{
			genre = line;
		}
		else
		{
			invalid_entry();
		}
	} while (genre == "");

	std::cout << std::endl
			  << "Book being donated: " << std::endl
			  << "'" << title << "' By " << author << ", Published "
			  << published << " [" << genre << "] (Page Count: "
			  << page_count << ")" << std::endl
			  << std::endl;


	std::cout << "1 return to main menu" << std::endl
		<< "2 confirm book donation" << std::endl
		<< std::endl
		<< "Enter 1 - 2 to make selection: ";
	
	int value = 0;
	do
	{
		std::getline(std::cin, line);

		if (verify_int(line) == true && line.length() > 0 && (std::stoi(line) == 1 || std::stoi(line) == 2))
		{
			value = std::stoi(line);
		}
		else
		{
			invalid_entry();
		}
	} while (value == 0);

	if (verify_input(1,2) == 1) { 
		delete[] donated_archive; 
		return archive;
	} 
	else  {
		donated_archive[num_books] = library(title, author, genre, page_count, published, "No");
		
		delete[] archive;
		return donated_archive;
	}


	// back_to_menu();

	//donated_archive[num_books] = library(title, author, genre, page_count, published, "No");

	//delete[] archive;

	// delete[] donated_archive;

	//return donated_archive;
}

int get_num_authors(const library *archive, int num_books)
{
	int num_authors = 0;

	for (int i = 0; i < num_books; i++)
	{
		bool author_needs_added_to_counter = true;

		for (int j = i + 1; j < num_books; j++)
		{
			if (archive[i].get_author().compare(archive[j].get_author()) == false)
			{
				author_needs_added_to_counter = false;
			}
		}

		if (author_needs_added_to_counter == true)
		{
			num_authors++;
		}
	}

	return num_authors;
}

std::string *build_array_of_authors(const library *archive, int num_books, int num_authors)
{
	std::string *authors = new std::string[num_authors];

	for (int i = 0; i < num_books; i++)
	{
		bool add_author = true;

		for (int j = 0; j < num_authors; j++)
		{
			if (archive[i].get_author().compare(authors[j]) == false)
			{
				add_author = false;
			}
		}

		if (add_author == true)
		{
			bool author_added = false;

			for (int j = 0; j < num_authors; j++)
			{
				if (authors[j].length() <= 0 && author_added == false)
				{
					authors[j] = archive[i].get_author();
					author_added = true;
				}
			}
		}
	}

	return authors;
}

int get_oldest_book(const library *archive, int num_books)
{
	int oldest_book = 2030;

	for (int i = 0; i < num_books; i++)
	{
		if (archive[i].get_published() < oldest_book)
		{
			oldest_book = archive[i].get_published();
		}
	}

	return oldest_book;
}

int get_newest_book(const library *archive, int num_books)
{
	int newest_book = 0;

	for (int i = 0; i < num_books; i++)
	{
		if (archive[i].get_published() > newest_book)
		{
			newest_book = archive[i].get_published();
		}
	}

	return newest_book;
}

void prompt_sort(library *archive, int num_books)
{
	std::cout << "Sort library archive" << std::endl
			  << "1 Ascending page length" << std::endl
			  << "2 Descending page length" << std::endl
			  << "3 Ascending alphabetical order" << std::endl
			  << "4 Descending alphabetical order" << std::endl;

	std::cout << std::endl
			  << "Enter 1 - 4 to make selection: ";

	int selected = verify_input(1, 4);

	selection_sort(archive, num_books, selected);

	std::cout << std::endl
			  << "Sort successful!" << std::endl;
}

void print_archive(const library *archive, int num_books)
{
	std::cout << "Library archive" << std::endl;

	for (int i = 0; i < num_books; i++)
	{
		archive[i].print();
	}
}

void print_archive_titles(const library *archive, int num_books)
{
	for (int i = 0; i < num_books; i++)
	{
		std::cout << archive[i].get_title() << std::endl;
	}
}

void print_available_books(const library *archive, int num_books)
{
	std::cout << "Available books in library archive" << std::endl;

	for (int i = 0; i < num_books; i++)
	{
		if (archive[i].get_reserved() == "No")
		{
			archive[i].print();
		}
	}
}

void print_checked_out_books(const library *archive, int num_books)
{
	std::cout << "Books able to be returned to library archive" << std::endl;

	for (int i = 0; i < num_books; i++)
	{
		if (archive[i].get_reserved() == "Yes")
		{
			archive[i].print();
		}
	}
}

void print_authors(const std::string *authors, int num_authors)
{
	std::cout << "Authors" << std::endl;

	for (int i = 0; i < num_authors; i++)
	{
		std::cout << i + 1 << " " << authors[i] << std::endl;
	}
}

void print_books_of_selected_author(const library *archive, int num_books, const std::string *authors, int num_authors)
{
	std::cout << std::endl
			  << "Select author 1 - " << num_authors << " to print book list: ";

	int selected = verify_input(1, num_authors) - 1;

	std::cout << std::endl;

	for (int i = 0; i < num_books; i++)
	{
		if (archive[i].get_author().compare(authors[selected]) == false)
		{
			archive[i].print();
		}
	}
}

void print_books_after_certain_year(const library *archive, int num_books)
{
	int oldest_book = get_oldest_book(archive, num_books);
	int newest_book = get_newest_book(archive, num_books);

	std::cout << "Date range of books currently in library archive " << oldest_book << " - " << newest_book << std::endl;
	std::cout << "Enter year to display all books published on or after entered date: ";

	int selected = verify_input();

	std::cout << std::endl;

	for (int i = 0; i < num_books; i++)
	{
		if (archive[i].get_published() >= selected)
		{
			archive[i].print();
		}
	}
}

void back_to_menu()
{
	std::cout << std::endl
			  << "Press 1 to return back to menu: ";

	int selected = 0;
	std::string line;

	do
	{
		std::getline(std::cin, line);

		if (verify_int(line) == false || line.length() <= 0 || std::stoi(line) != 1)
		{
			invalid_entry();
		}
		else
		{
			selected = std::stoi(line);
		}
	} while (selected != 1);
}

void list_of_titles(const library *archive, int num_books)
{
	std::cout << "Titles in library archive" << std::endl;

	print_archive_titles(archive, num_books);

	std::string title = "";

	std::cout << std::endl
			  << "Titles are case and space sensitive, enter 1 to return to menu" << std::endl;
	std::cout << "Enter title of book to print all informaiton on that title: ";

	title = verify_title(archive, num_books);

	std::cout << std::endl;

	for (int i = 0; i < num_books; i++)
	{
		if (archive[i].get_title() == title)
		{
			archive[i].print();

			back_to_menu();
		}
	}
}

void check_out_book(library *archive, int num_books)
{
	print_available_books(archive, num_books);

	std::string title = "";

	std::cout << std::endl
			  << "Titles are case and space sensitive, enter 1 to return to menu" << std::endl;
	std::cout << "Enter title of book to check out: ";

	title = verify_input(false, archive, num_books);

	std::cout << std::endl;

	for (int i = 0; i < num_books; i++)
	{
		if (archive[i].get_reserved() == "No" && archive[i].get_title() == title) {
			archive[i].set_reserved("Yes");
			
			std::cout << "Checked out '" << title << "' successfully" << std::endl;

			back_to_menu();
		}
	}
}

void reshelf_book(library *archive, int num_books)
{
	print_checked_out_books(archive, num_books);

	std::string title = "";

	std::cout << std::endl
			  << "Titles are case and space sensitive, enter 1 to return to menu" << std::endl;
	std::cout << "Enter title of book to return: ";

	title = verify_input(true, archive, num_books);

	std::cout << std::endl;

	for (int i = 0; i < num_books; i++)
	{
		if (archive[i].get_reserved() == "Yes" && archive[i].get_title() == title)
		{
			archive[i].set_reserved("No");
			std::cout << "Returned '" << title << "' successfully" << std::endl;

			back_to_menu();
		}
	}
}

int menu()
{
	std::cout << std::endl
			  << "Main Menu" << std::endl
			  << "1 Print out all the books owned by the library" << std::endl
			  << "2 Print out all of the books that are currently available to check out" << std::endl
			  << "3 Print out all the books by given author" << std::endl
			  << "4 Print out all the books published on or after a given year" << std::endl
			  << "5 Sort all the books in the library" << std::endl
			  << "6 Print out all the information about a single book by searching its title" << std::endl
			  << "7 Check out a book" << std::endl
			  << "8 Return a book" << std::endl
			  << "9 Donate a book" << std::endl
			  << "10 Quit" << std::endl;

	std::cout << std::endl
			  << "Enter 1 - 10 to make a selection: ";

	int selected = 0;
	selected = verify_input(1, 10);

	std::cout << std::endl;

	return selected;
}

void menu_selection(int selected, library *archive, int num_books,
					const std::string *authors, int num_authors)
{
	switch (selected)
	{
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
		// Donate a book
		// Return to main and build new archive
		break;
	case 10:
		// Quit
		break;
	default:
		invalid_entry();
		back_to_menu();
		break;
	}
}

void update_arhcive_file(const library* archive, int num_books) {
	std::cout << "Updating library archive..." << std::endl;
	
	const std::string path = "Data\\Library-List.csv";

	std::ofstream output;

	output.open(path);
	if (output.is_open()) {
		output << "Published" << "," << "Title" << "," << "Author" << "," << "Page Count" 
			<< "," << "Genre" << "," << "Reserved" << std::endl;
		for (int i = 0; i < num_books; i++) {
			output << archive[i].get_published() << ","
				<< archive[i].get_title() << ","
				<< archive[i].get_author() << ","
				<< archive[i].get_page_count() << ","
				<< archive[i].get_genre() << ","
				<< archive[i].get_reserved() << std::endl;
		}
	}
	output.close();
}

int main()
{
	std::string path = "Data\\Library-List.csv";

	int num_books = get_line_count(path) - 1;

	library *archive = fill_archive(path, num_books);

	int num_authors = get_num_authors(archive, num_books);

	std::string *authors = build_array_of_authors(archive, num_books, num_authors);

	int selected = 0;

	do
	{
		selected = menu();
		menu_selection(selected, archive, num_books, authors, num_authors);

		if (selected == 9)
		{
			archive = donate_book(archive, num_books);
			num_books++;

			num_authors = get_num_authors(archive, num_books);
			delete[] authors;

			authors = build_array_of_authors(archive, num_books, num_authors);
		}

	} while (selected != 10);

	update_arhcive_file(archive, num_books);

	end_message();

	delete[] authors;
	delete[] archive;

	return 0;
}