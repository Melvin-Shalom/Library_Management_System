#include "Book.h"

Book::Book() : year(0) {}

Book::Book(const string& id, const string& title, const string& author, int year)
    : id(id), title(title), author(author), year(year) {}

string Book::getId() const { return id; }
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
int Book::getYear() const { return year; }

void Book::setId(const string& id) { this->id = id; }
void Book::setTitle(const string& title) { this->title = title; }
void Book::setAuthor(const string& author) { this->author = author; }
void Book::setYear(int year) { this->year = year; }

