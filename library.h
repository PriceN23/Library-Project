/*
Midterm Project Default Proposal
CompSci 222 - 01	03/09/2025
Troy Poniewaz & Nicholas Price
*/
#pragma once
#include <iostream>
#include <string>

class library {
private:
	std::string title;
	std::string author;
	std::string genre;
	unsigned short page_count; // page length 
	unsigned short published;
	std::string reserved; // checked out

	// these should not be altered unless done direclty through the library constructor for newly archived books
	void set_title(std::string title);
	void set_author(std::string author);
	void set_genre(std::string genre);
	void set_page_count(unsigned short page_count);
	void set_published(unsigned short published);
	
  

public:
	library();
	library(std::string title, std::string author,
		std::string genre, unsigned short page_count, unsigned short published,
		std::string reserved);

	std::string get_title() const;
	std::string get_author() const;
	std::string get_genre() const;
	unsigned short get_page_count() const;
	unsigned short get_published() const;
	std::string get_reserved() const;

	// reserved can be set Yes or No as needed
	void set_reserved(std::string reserved);

	void print() const;
};