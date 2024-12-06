#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Book {
    std::string title;
    std::string author;
    std::string isbn;
    int year;

    void display() const {
        std::cout << "Title: " << title << ", Author: " << author
                  << ", ISBN: " << isbn << ", Year: " << year << std::endl;
    }
};

class Library {
private:
    std::vector<Book> books;

public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void removeBookByISBN(const std::string& isbn) {
        auto it = std::remove_if(books.begin(), books.end(), 
            [&isbn](const Book& book) {
                return book.isbn == isbn;
            });
        if (it != books.end()) {
            books.erase(it, books.end());
            std::cout << "Book with ISBN " << isbn << " removed successfully.\n";
        } else {
            std::cout << "Book with ISBN " << isbn << " not found.\n";
        }
    }

    void searchBooksByAuthor(const std::string& author) const {
        bool found = false;
        for (const auto& book : books) {
            if (book.author == author) {
                book.display();
                found = true;
            }
        }
        if (!found) {
            std::cout << "No books found by author " << author << ".\n";
        }
    }

    void searchBooksByYearRange(int startYear, int endYear) const {
        bool found = false;
        for (const auto& book : books) {
            if (book.year >= startYear && book.year <= endYear) {
                book.display();
                found = true;
            }
        }
        if (!found) {
            std::cout << "No books found in the range " << startYear << "-" << endYear << ".\n";
        }
    }

    void displayAllBooks() const {
        if (books.empty()) {
            std::cout << "The library is empty.\n";
        } else {
            for (const auto& book : books) {
                book.display();
            }
        }
    }
};

int main() {
    Library library;

    // Додавання книг
    library.addBook({"The Great Gatsby", "F. Scott Fitzgerald", "123456789", 1925});
    library.addBook({"1984", "George Orwell", "987654321", 1949});
    library.addBook({"To Kill a Mockingbird", "Harper Lee", "456789123", 1960});

    // Виведення всіх книг
    std::cout << "All books in the library:\n";
    library.displayAllBooks();

    // Пошук книг за автором
    std::cout << "\nBooks by George Orwell:\n";
    library.searchBooksByAuthor("George Orwell");

    // Пошук книг за діапазоном років
    std::cout << "\nBooks published between 1900 and 1950:\n";
    library.searchBooksByYearRange(1900, 1950);

    // Видалення книги за ISBN
    std::cout << "\nRemoving book with ISBN 123456789.\n";
    library.removeBookByISBN("123456789");

    // Виведення всіх книг після видалення
    std::cout << "\nAll books in the library after removal:\n";
    library.displayAllBooks();

    return 0;
}
