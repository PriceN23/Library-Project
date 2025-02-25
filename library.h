#pragma once
#include <iostream>
#include <string>

class library {
private:
	std::string title;
	std::string author;
	std::string genre;
	int pages;			// page length 
	int published;
	bool reserved;		// checked out

public:
	library(std::string title, std::string author,
		std::string genre, int pages, int published, bool reserved);

	std::string get_title() const;
	std::string get_author() const;
	std::string get_genre() const;
	int get_pages() const;
	int get_published() const;
	bool get_reserved() const;

	void set_title(std::string title);
	void set_author(std::string author);
	void set_genre(std::string genre);
	void set_pages(int pages);
	void set_published(int published);
	void set_reserved(bool reserved);

	void print() const;
};