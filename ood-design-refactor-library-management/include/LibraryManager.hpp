#pragma once
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "Book.hpp"
#include "BookManager.hpp"
#include "Member.hpp"
#include "MemberManager.hpp"
#include "BorrowService.hpp"

class LibraryManager {
public:
    // Collections
    BookManager bookManager;
    MemberManager memberManager;
    BorrowService borrowService;
    

    LibraryManager() = default;
    LibraryManager(const std::vector<Book>& books, const std::vector<Member>& members){
        bookManager = BookManager(books);
        memberManager = MemberManager(members);
        // Initialize borrowed books as empty
        borrowService = BorrowService();
    }
    void RemoveMemberWithBooks(const Member& member) {
        memberManager.RemoveMember(member.getMemberId());
        borrowService.ClearRentedBooks(member);
    }
};
