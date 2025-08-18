#pragma once
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "Book.hpp"
#include "Member.hpp"

class LibraryManager {
public:
    // Collections
    std::vector<Book> Books;
    std::vector<Member> Members;
    std::unordered_map<Member, std::vector<Book>> BorrowedBooks;

    LibraryManager() = default;

    void AddBook(const Book& book) { Books.push_back(book); }

    void RemoveBook(const Book& book) {
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
        return it != Books.end() ? &(*it) : nullptr;
    }

    void RegisterMember(const Member& member) { Members.push_back(member); }

    void RemoveMember(const Member& member) {
        auto it = std::remove_if(Members.begin(), Members.end(),
            [&](const Member& m){ return m.getMemberId() == member.getMemberId(); });
        Members.erase(it, Members.end());
        BorrowedBooks.erase(member);
    }

    void UpdateMember(const std::string& memberId, const Member& updatedMember) {
        auto it = std::find_if(Members.begin(), Members.end(), [&](const Member& m){ return m.getMemberId() == memberId; });
        if (it != Members.end()) {
            it->setName(updatedMember.getName());
            it->setMemberId(updatedMember.getMemberId());
        }
    }

    Member* FindMember(const std::string& memberId) {
        auto it = std::find_if(Members.begin(), Members.end(), [&](const Member& m){ return m.getMemberId() == memberId; });
        return it != Members.end() ? &(*it) : nullptr;
    }

    void BorrowBook(const Member& member, const Book& book) {
        BorrowedBooks[member].push_back(book);
    }

    void ReturnBook(const Member& member, const Book& book) {
        auto it = BorrowedBooks.find(member);
        if (it != BorrowedBooks.end()) {
            auto& list = it->second;
            auto jt = std::remove_if(list.begin(), list.end(),
                [&](const Book& b){ return b.getTitle() == book.getTitle() && b.getAuthor() == book.getAuthor(); });
            list.erase(jt, list.end());
        }
    }

    std::vector<Book> ViewBorrowedBooks(const Member& member) const {
        auto it = BorrowedBooks.find(member);
        if (it != BorrowedBooks.end()) return it->second;
        return {};
    }
};
