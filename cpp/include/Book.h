#ifndef BOOK_H
#define BOOK_H

#include <string>

using namespace std;

class Book {
public:
    Book();
    Book(const string& id, const string& title, const string& author, int year);

    string getId() const;
    string getTitle() const;
    string getAuthor() const;
    int getYear() const;

    void setId(const string& id);
    void setTitle(const string& title);
    void setAuthor(const string& author);
    void setYear(int year);

private:
    string id;
    string title;
    string author;
    int year;
};

#endif // BOOK_H

