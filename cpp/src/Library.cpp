#include "Library.h"
#include <iostream>
#include <algorithm>

using namespace std;

bool Library::idExists(const string& id) const {
    return any_of(books.begin(), books.end(), [&id](const Book& book) {
        return book.getId() == id;
    });
}

void Library::addBook(const Book& book) {
    if (idExists(book.getId())) {
        cout<<endl;
        cout << "Error: Book with ID " << book.getId() << " already exists.\n";
        return;
    }
    else{
        cout << "Book added successfully!\n";
    }
    books.push_back(book);
}

bool Library::removeBook(const string& id) {
    auto it = remove_if(books.begin(), books.end(), [&id](const Book& book) {
        return book.getId() == id;
    });

    if (it != books.end()) {
        books.erase(it, books.end());
        return true;
    }
    return false;
}

vector<Book> Library::findBooks(const string& query) const {
    vector<Book> result;
    for (const auto& book : books) {
        if (book.getTitle() == query || book.getAuthor() == query || to_string(book.getYear()) == query) {
            result.push_back(book);
        }
    }
    return result;
}

void Library::listBooks() const {
    for (const auto& book : books) {
        cout << book.getId() << ": " << book.getTitle() << " by " << book.getAuthor() << " (" << book.getYear() << ")\n";
    }
}

void Library::listBooksById() const {
    vector<Book> sortedBooks = books;
    sort(sortedBooks.begin(), sortedBooks.end(), [](const Book& a, const Book& b) {
        return a.getId() < b.getId();
    });
    for (const auto& book : sortedBooks) {
        cout << book.getId() << ": " << book.getTitle() << " by " << book.getAuthor() << " (" << book.getYear() << ")\n";
    }
}

void Library::listBooksByYear() const {
    vector<Book> sortedBooks = books;
    sort(sortedBooks.begin(), sortedBooks.end(), [](const Book& a, const Book& b) {
        return a.getYear() < b.getYear();
    });
    for (const auto& book : sortedBooks) {
        cout << book.getId() << ": " << book.getTitle() << " by " << book.getAuthor() << " (" << book.getYear() << ")\n";
    }
}

void Library::sortBooks() {
    sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
        return a.getYear() < b.getYear();
    });
}

void Library::handleConcurrentOperations() {
    // Dummy implementation for concurrent operations
    cout << "Handling concurrent operations...\n";
}

