#include <iostream>
#include <string>
#include "library.h"

// custom constructor
library::library(std::string title, std::string author,
	std::string genre, int pages, int published, bool reserved) {
	set_title(title);
	set_author(author);
	set_genre(genre);
	set_pages(pages);
	set_published(published);
	set_reserved(reserved);
}

// getters
std::string library::get_title() const {
	return title;
}

std::string library::get_author() const {
	return author;
}

std::string library::get_genre() const {
	return genre;
}

int library::get_pages() const {
	return pages;
}

int library::get_published() const {
	return published;
}

bool library::get_reserved() const {
	return reserved;
}

// setters
void library::set_title(std::string title) {
	if (title.length() > 0) {
		this->title = title;
	}
	else {
		throw std::exception("Title must not be blank");
	}
}

void library::set_author(std::string author) {
	if (author.length() > 0) {
		this->author = author;
	}
	else {
		throw std::exception("Author must not be blank");
	}
}

void library::set_genre(std::string genre) {
	if (genre.length() > 0 && (genre == "fiction" || genre == "Fiction" 
		|| genre == "nonfiction" || genre == "Nonfiction"
		|| genre == "biography" || genre == "Biography")) {
		this->genre = genre;
	}
	else {
		throw std::exception("Please enter genre fiction, nonfiction, or biography");
	}
}

void library::set_pages(int pages) {
	if (pages > 0 && pages < 25000) {
		this->pages = pages;
	}
	else {
		throw std::exception("Page length must be int within range 1-25000");
	}
}

void library::set_published(int published) {
	if (published >= 868 && pages <= 2025) {
		this->published = published;
	}
	else {
		throw std::exception("Published date must be int within range 868-2025");
	}
}

void library::set_reserved(bool reserved) {
	if (reserved == true) {
		this->reserved = reserved;
	}
	else if (reserved != false) {
		throw std::exception("Reserved must be case sensitive true or fale.");
	}
}

// print
void library::print() const {
	std::cout << "Print template" << std::endl;
}