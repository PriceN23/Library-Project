#pragma once
#include <iostream>
#include <string>

class library {
private:
	std::string title;
	std::string author;
	std::string genre;
	int page_count;			// page length 
	int published;
	std::string reserved;		// checked out

	// these should not be altered unless done direclty through the library constructor for newly archived books
	void set_title(std::string title);
	void set_author(std::string author);
	void set_genre(std::string genre);
	void set_page_count(int page_count);
	void set_published(int published);

public:
	library();
	library(std::string title, std::string author,
		std::string genre, int page_count, int published, 
		std::string reserved);

	std::string get_title() const;
	std::string get_author() const;
	std::string get_genre() const;
	int get_page_count() const;
	int get_published() const;
	std::string get_reserved() const;

	// reserved can be set true or false as needed
	void set_reserved(std::string reserved);

	void print() const;
};