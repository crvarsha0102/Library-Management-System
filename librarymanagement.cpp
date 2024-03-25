#include <iostream>
#include <vector>
#include <algorithm>

class Book {
public:
    std::string isbn;
    std::string title;
    std::string author;

    Book(const std::string& i, const std::string& t, const std::string& a) : isbn(i), title(t), author(a) {}
};

class Member {
public:
    std::string memberId;
    std::string name;

    Member(const std::string& id, const std::string& n) : memberId(id), name(n) {}
};

class Library {
private:
    std::vector<Book> books;
    std::vector<Member> members;

public:
    void addBook(const std::string& isbn, const std::string& title, const std::string& author) {
        books.emplace_back(isbn, title, author);
        std::cout << "Book added successfully.\n";
    }

    Book* searchBookByISBN(const std::string& isbn) {
        auto it = std::find_if(books.begin(), books.end(), [&](const Book& book) {
            return book.isbn == isbn;
        });

        if (it != books.end()) {
            return &(*it);
        } else {
            return nullptr;
        }
    }

    void displayBooks() {
        std::cout << "Books in the library:\n";
        for (const auto& book : books) {
            std::cout << "ISBN: " << book.isbn << ", Title: " << book.title << ", Author: " << book.author << "\n";
        }
    }

    void addMember(const std::string& memberId, const std::string& name) {
        members.emplace_back(memberId, name);
        std::cout << "Member added successfully.\n";
    }

    Member* findMemberById(const std::string& memberId) {
        auto it = std::find_if(members.begin(), members.end(), [&](const Member& member) {
            return member.memberId == memberId;
        });

        if (it != members.end()) {
            return &(*it);
        } else {
            return nullptr;
        }
    }

    void displayMembers() {
        std::cout << "Members in the library:\n";
        for (const auto& member : members) {
            std::cout << "Member ID: " << member.memberId << ", Name: " << member.name << "\n";
        }
    }

    void borrowBook(const std::string& memberId, const std::string& isbn) {
        Member* member = findMemberById(memberId);
        if (member) {
            Book* book = searchBookByISBN(isbn);
            if (book) {
                std::cout << "Book borrowed successfully by member " << member->name << ".\n";
            } else {
                std::cout << "Book not found.\n";
            }
        } else {
            std::cout << "Member not found.\n";
        }
    }

    void returnBook(const std::string& memberId, const std::string& isbn) {
        Member* member = findMemberById(memberId);
        if (member) {
            Book* book = searchBookByISBN(isbn);
            if (book) {
                std::cout << "Book returned successfully by member " << member->name << ".\n";
            } else {
                std::cout << "Book not found.\n";
            }
        } else {
            std::cout << "Member not found.\n";
        }
    }
};

int main() {
    Library library;
    int choice;

    do {
        std::cout << "\nLibrary Management System Menu:\n";
        std::cout << "1. Add Book\n";
        std::cout << "2. Search Book by ISBN\n";
        std::cout << "3. Display Books\n";
        std::cout << "4. Add Member\n";
        std::cout << "5. Display Members\n";
        std::cout << "6. Borrow Book\n";
        std::cout << "7. Return Book\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string isbn, title, author;
                std::cout << "Enter ISBN: ";
                std::cin >> isbn;
                std::cout << "Enter Title: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                std::cout << "Enter Author: ";
                std::getline(std::cin, author);
                library.addBook(isbn, title, author);
                break;
            }
            case 2: {
                std::string isbn;
                std::cout << "Enter ISBN to search: ";
                std::cin >> isbn;
                Book* foundBook = library.searchBookByISBN(isbn);
                if (foundBook) {
                    std::cout << "Book found:\n";
                    std::cout << "ISBN: " << foundBook->isbn << ", Title: " << foundBook->title << ", Author: " << foundBook->author << "\n";
                } else {
                    std::cout << "Book not found.\n";
                }
                break;
            }
            case 3:
                library.displayBooks();
                break;
            case 4: {
                std::string memberId, name;
                std::cout << "Enter Member ID: ";
                std::cin >> memberId;
                std::cout << "Enter Member Name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                library.addMember(memberId, name);
                break;
            }
            case 5:
                library.displayMembers();
                break;
            case 6: {
                std::string memberId, isbn;
                std::cout << "Enter Member ID: ";
                std::cin >> memberId;
                std::cout << "Enter ISBN of the book to borrow: ";
                std::cin >> isbn;
                library.borrowBook(memberId, isbn);
                break;
            }
            case 7: {
                std::string memberId, isbn;
                std::cout << "Enter Member ID: ";
                std::cin >> memberId;
                std::cout << "Enter ISBN of the book to return: ";
                std::cin >> isbn;
                library.returnBook(memberId, isbn);
                break;
            }
            case 0:
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
