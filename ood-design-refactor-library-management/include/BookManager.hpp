# pragma once
#include <vector>
# include <string>
# include "Book.hpp"


class BookManager{
public:
    BookManager() = default;
    BookManager(const std::vector<Book>& books) : Books(books) {}

    void AddBook(const Book& book) {
        Books.push_back(book);
    }

    void RemoveBook(const Book& book){
        auto it = std::remove_if(Books.begin(), Books.end(),
            [&](const Book& b){ return b.getTitle() == book.getTitle() && b.getAuthor() == book.getAuthor(); });
        Books.erase(it, Books.end());
    }

    void UpdateBook(const std::string& originalTitle, const Book& updatedBook) {
        auto it = std::find_if(Books.begin(), Books.end(), [&](const Book& b){ return b.getTitle() == originalTitle; });
        if (it != Books.end()) {
            it->setTitle(updatedBook.getTitle());
            it->setAuthor(updatedBook.getAuthor());
        }
    }

    Book* FindBook(const std::string& title) {
        auto it = std::find_if(Books.begin(), Books.end(), [&](const Book& b){ return b.getTitle() == title; });
        return (it != Books.end()) ? &(*it) : nullptr;
    }

private:
    std::vector<Book> Books;
};