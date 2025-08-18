#pragma once
#include <string>

class Book {
public:
    Book() = default;
    Book(std::string title, std::string author) : title_(std::move(title)), author_(std::move(author)) {}

    const std::string& getTitle() const { return title_; }
    void setTitle(const std::string& title) { title_ = title; }

    const std::string& getAuthor() const { return author_; }
    void setAuthor(const std::string& author) { author_ = author; }

private:
    std::string title_;
    std::string author_;
};
