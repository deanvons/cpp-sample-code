#pragma once
#include <unordered_map>
#include <vector>
#include "Book.hpp"
#include "Member.hpp"

class BorrowService {
public:
    BorrowService() = default;

    void BorrowBook(const Member& member, const Book& book) {
        rentedBooks[member].push_back(book);
    }

    void ReturnBook(const Member& member, const Book& book) {
        auto it = rentedBooks.find(member);
        if (it != rentedBooks.end()) {
            auto& list = it->second;
            auto jt = std::remove_if(list.begin(), list.end(),
                [&](const Book& b){ return b.getTitle() == book.getTitle() && b.getAuthor() == book.getAuthor(); });
            list.erase(jt, list.end());
        }
    }

    std::vector<Book> GetRentedBooks(const Member& member) const {
        auto it = rentedBooks.find(member);
        if (it != rentedBooks.end()) return it->second;
        return {};
    }

    void ClearRentedBooks(const Member& member) {
        rentedBooks.erase(member);
    }

    std::vector<Book> ViewRentedBooks(const Member& member) const {
        auto it = rentedBooks.find(member);
        if (it != rentedBooks.end()) return it->second;
        return {};
    }


private:
    std::unordered_map<Member, std::vector<Book>> rentedBooks;
};
