#include <iostream>
#include <string>
#include "library.h"

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
	this->title = title;
}

void library::set_author(std::string author) {
	this->author = author;
}

void library::set_genre(std::string genre) {
	this->genre = genre;
}

void library::set_pages(int pages) {
	this->pages = pages;
}

void library::set_published(int published) {
	this->published = published;
}

void library::set_reserved(bool reserved) {
	this->reserved = reserved;
}

// print
void library::print() const {
	std::cout << std::endl;
}