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
#include "library.h"

library::library() {
	title = "Untitled";
	author = "Unknown Artist";
	genre = "Fiction";
	page_count = 100;
	published = 2000;
	reserved = "Yes";
}

// custom constructor
library::library(std::string title, std::string author,
	std::string genre, unsigned short page_count, unsigned short published, std::string reserved) {
	set_title(title);
	set_author(author);
	set_genre(genre);
	set_page_count(page_count);
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

unsigned short library::get_page_count() const {
	return page_count;
}

unsigned short library::get_published() const {
	return published;
}

std::string library::get_reserved() const {
	return reserved;
}

// setters
void library::set_title(std::string title) {
	if (title.length() > 0) {
		this->title = title;
	}
	else {
		throw std::invalid_argument("Title must not be blank");
	}
}

void library::set_author(std::string author) {
	if (author.length() > 0) {
		this->author = author;
	}
	else {
		throw std::invalid_argument("Author must not be blank");
	}
}

void library::set_genre(std::string genre) {
	if (genre.length() > 0) {
		this->genre = genre;
	}
	else {
		throw std::invalid_argument("Genre must not be blank");
	}
}

void library::set_page_count(unsigned short page_count) {
	if (page_count > 0 && page_count < 25000) {
		this->page_count = page_count;
	}
	else {
		throw std::invalid_argument("Page length must be int within range 1-25000");
	}
}

void library::set_published(unsigned short published) {
	if (published >= 868 && published <= 2025) {
		this->published = published;
	}
	else {
		throw std::invalid_argument("Published date must be int within range 868-2025");
	}
}

void library::set_reserved(std::string reserved) {
	if (reserved.length() > 0 && (reserved == "Yes" || reserved == "No")) {
		this->reserved = reserved;
	}
	else {
		throw std::invalid_argument("Reserved must be case sensitive true or fale.");
	}
}

// print
void library::print() const {
	if (get_reserved() == "No") {
		std::cout << "'" << get_title() << "' By " << get_author() << ", Published " 
			<< get_published() << " [" << get_genre() << "] (Page Count: " 
			<< get_page_count() << ") [Available]" << std::endl;
	}
	else {
		std::cout << "'" << get_title() << "' By " << get_author() << ", Published "
			<< get_published() << " [" << get_genre() << "] (Page Count: "
			<< get_page_count() << ") [Checked Out]" << std::endl;
	}
}