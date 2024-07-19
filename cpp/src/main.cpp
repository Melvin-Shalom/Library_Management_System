#include "Library.h"
#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>  // For std::setw and std::setfill

using namespace std;

void NewPart() {
    cout << "\nPress Enter to continue ...";
    cin.get();
}

void clearConsole() {
    cout << "\033[2J\033[1;1H";
}

void printTitle() {
    clearConsole();
    cout << "\n";
    cout << "\t\t\t---------------------------------------------\n";
    cout << "\t\t\t|         Library Management System         |\n";
    cout << "\t\t\t---------------------------------------------\n";
    cout << "\n\n";
}

void showMenu() {
    cout << "1. Add Book\n";
    cout << "2. Remove Book\n";
    cout << "3. Find Books\n";
    cout << "4. List Books\n";
    cout << "0. Exit\n";
    cout << "\n\nEnter your choice: ";
}

string formatId(const string& id) {
    return string(6 - id.size(), '0') + id;
}

int main() {
    Library library;
    int choice;
    string id, title, author;
    int year;
    vector<Book> foundBooks; // Initialize vector here

    do {
        printTitle();
        showMenu();
        cin >> choice;
        cin.ignore(); // To ignore the newline character left in the buffer

        switch (choice) {
            case 1:
                clearConsole();
                cout << "Enter Book ID: ";
                cin >> id;
                cout << "Enter Book Title: ";
                cin.ignore(); // To ignore the newline character left in the buffer
                getline(cin, title);
                cout << "Enter Book Author: ";
                getline(cin, author);
                cout << "Enter Year of Publication: ";
                cin >> year;
                if (year >= 1000 && year <= 3000) {
                    library.addBook(Book(formatId(id), title, author, year));
                } else {
                    cout << "Invalid year!\n";
                }
                cin.ignore();
                NewPart();
                break;

            case 2:
                clearConsole();
                cout << "Enter Book ID to remove: ";
                cin >> id;
                if (library.removeBook(formatId(id))) {
                    cout << "Book removed successfully!\n";
                } else {
                    cout << "Book not found!\n";
                }
                cin.ignore();
                NewPart();
                break;

            case 3:
                clearConsole();
                cout << "Choose search criteria:\n";
                cout << "1. By Title\n";
                cout << "2. By Author\n";
                cout << "3. By Year\n";
                cout << "\n\nEnter choice: ";
                int searchType;
                cin >> searchType;
                cin.ignore(); // To ignore the newline character left in the buffer

                foundBooks.clear(); // Clear previous search results
                switch (searchType) {
                    case 1:
                        cout << "\nEnter Book Title to find: ";
                        getline(cin, title);
                        foundBooks = library.findBooks(title); // Assuming findBooks is used for title search
                        break;
                    case 2:
                        cout << "\nEnter Book Author to find: ";
                        getline(cin, author);
                        foundBooks = library.findBooks(author); // Use findBooks for author search
                        break;
                    case 3:
                        cout << "\nEnter Year of Publication to find: ";
                        cin >> year;
                        foundBooks = library.findBooks(to_string(year)); // Use findBooks for year search
                        break;
                    default:
                        cout << "Invalid choice!\n";
                        NewPart();
                        break;
                }

                if (foundBooks.empty()) {
                    cout << "No books found.\n";
                } else {
                    for (const auto& book : foundBooks) {
                        cout << book.getId() << ": " << book.getTitle() << " by " << book.getAuthor() << " (" << book.getYear() << ")\n";
                    }
                }
                cin.ignore();
                NewPart();
                break;

            case 4:
                clearConsole();
                cout << "Choose an option:\n";
                cout << "1. List Books by ID\n";
                cout << "2. List Books by Year\n";
                cout << "\n\nEnter choice: ";
                int listOption;
                cin >> listOption;
                cin.ignore(); // To ignore the newline character left in the buffer

                if (listOption == 1) {
                    cout << "Listing all books by ID:\n\n";
                    library.listBooksById();
                } else if (listOption == 2) {
                    cout << "Listing all books by Year:\n\n";
                    library.listBooksByYear();
                } else {
                    cout << "Invalid choice!\n";
                }
                NewPart();
                break;

            case 0:
                cout << "\n\n\n\nExiting...\n";
                NewPart();
                clearConsole();
                break;

            default:
                clearConsole();
                cout << "\nInvalid choice! Please try again.\n";
                NewPart();
                break;
        }
    } while (choice != 0);
    clearConsole();

    return 0;
}

