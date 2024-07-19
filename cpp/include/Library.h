#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include "Book.h"

class Library {
public:
    void addBook(const Book& book);
    bool removeBook(const std::string& id);
    std::vector<Book> findBooks(const std::string& query) const;
    void listBooks() const;
    void sortBooks();
    void handleConcurrentOperations();

    // New methods
    void listBooksById() const;
    void listBooksByYear() const;

private:
    std::vector<Book> books;

    bool idExists(const std::string& id) const;
};

#endif

