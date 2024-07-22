#include <iostream>
#include <string>
#include <json/json.h>
#include <sstream> // For std::istringstream
#include <curl/curl.h>

using namespace std;

// Function to handle HTTP responses
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Function to send HTTP requests
string sendHttpRequest(const string& url, const string& data = "", const string& method = "GET") {
    CURL* curl;
    CURLcode res;
    string readBuffer;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        if (method == "POST") {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
            struct curl_slist* headers = nullptr;
            headers = curl_slist_append(headers, "Content-Type: application/json");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        } else if (method == "DELETE") {
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
        }
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return readBuffer;
}

void displayJson(const string& rawJson) {
    Json::CharReaderBuilder readerBuilder;
    Json::Value jsonData;
    string errs;

    // Create a string stream from the raw JSON string
    istringstream s(rawJson);

    // Parse JSON data from the string stream
    if (Json::parseFromStream(readerBuilder, s, &jsonData, &errs)) {
        cout << "Parsed JSON data:\n";
        cout << jsonData.toStyledString() << endl;
    } else {
        cerr << "Failed to parse JSON: " << errs << endl;
    }
}

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
    int choice;
    string id, title, author;
    int year;
    string response;
    
    do {
        printTitle();
        showMenu();
        cin >> choice;
        cin.ignore(); // To ignore the newline character left in the buffer

        switch (choice) {
            case 1: {
                clearConsole();
                cout << "Enter Book ID: ";
                cin >> id;
                cout << "Enter Book Title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter Book Author: ";
                getline(cin, author);
                cout << "Enter Year of Publication: ";
                cin >> year;
                if (year >= 1000 && year <= 3000) {
                    string data = "{\"id\":\"" + formatId(id) + "\",\"title\":\"" + title + "\",\"author\":\"" + author + "\",\"year\":" + to_string(year) + "}";
                    response = sendHttpRequest("http://localhost:3000/api/books", data, "POST");
                    cout << "Response: " << response << endl;
                } else {
                    cout << "Invalid year!\n";
                }
                cin.ignore();
                NewPart();
                break;
            }

            case 2: {
                clearConsole();
                cout << "Enter Book ID to remove: ";
                cin >> id;
                response = sendHttpRequest("http://localhost:3000/api/books/" + formatId(id), "", "DELETE");
                cout << "Response: " << response << endl;
                cin.ignore();
                NewPart();
                break;
            }

            case 3: {
                clearConsole();
                cout << "Choose search criteria:\n";
                cout << "1. By Title\n";
                cout << "2. By Author\n";
                cout << "3. By Year\n";
                cout << "\n\nEnter choice: ";
                int searchType;
                cin >> searchType;
                cin.ignore(); // To ignore the newline character left in the buffer

                switch (searchType) {
                    case 1:
                        cout << "\nEnter Book Title to find: ";
                        getline(cin, title);
                        response = sendHttpRequest("http://localhost:3000/api/books?title=" + title);
                        break;
                    case 2:
                        cout << "\nEnter Book Author to find: ";
                        getline(cin, author);
                        response = sendHttpRequest("http://localhost:3000/api/books?author=" + author);
                        break;
                    case 3:
                        cout << "\nEnter Year of Publication to find: ";
                        cin >> year;
                        response = sendHttpRequest("http://localhost:3000/api/books?year=" + to_string(year));
                        break;
                    default:
                        cout << "Invalid choice!\n";
                        response = "";
                        break;
                }

                if (response.empty()) {
                    cout << "No books found.\n";
                } else {
                    cout << response << endl;
                }
                cin.ignore();
                NewPart();
                break;
            }

            case 4: {
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
                    response = sendHttpRequest("http://localhost:3000/api/books/list?sort=id");
                    cout << response << endl;
                } else if (listOption == 2) {
                    cout << "Listing all books by Year:\n\n";
                    response = sendHttpRequest("http://localhost:3000/api/books/list?sort=year");
                    cout << response << endl;
                } else {
                    cout << "Invalid choice!\n";
                }
                NewPart();
                break;
            }

            case 0:
                cout << "\n\n\n\nExiting...\n\n\n\n\n";
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

