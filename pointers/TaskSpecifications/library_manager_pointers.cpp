// Dynamic Library System (Pointers Practice) — Starter Skeleton
// ----------------------------------------------------------------------------------
// Goals:
//  - Practice raw pointers, pointer arithmetic, double pointers (Book**)
//  - Manual ownership with new/delete and new[]/delete[]
//  - Functions that take/return pointers (no references; no smart pointers yet)
//  - Iterate with pointer arithmetic (not just indexing)
//  - Prepare for leak-checking (Valgrind or your IDE's analyzer)
//
// Build:
//   g++ -std=c++17 -O2 -Wall -Wextra -pedantic library_pointers_starter.cpp -o library
// Run:
//   ./library
//
// NOTE: This is a skeleton. Fill in all TODOs. You may change signatures if you have
// strong reasons, but try to keep the raw-pointer focus.
// ----------------------------------------------------------------------------------

#include <iostream>
#include <cstring>   // for std::strlen, std::memcmp (avoid std::string on purpose)
#include <cstddef>   // for std::size_t
#include <limits>    // for std::numeric_limits
#include <string>    // for std::string buffer in read_line_alloc
#include <new>       // for std::nothrow

// ----------------------------------------------------------------------------------
// Book: uses C-strings (char*) intentionally to practice manual allocation.
// ----------------------------------------------------------------------------------
struct Book {
    char* title;   // owned C-string (null-terminated)
    char* author;  // owned C-string (null-terminated)
    int   year;
};

// ---- Utility prototypes ----------------------------------------------------------

// Allocate a new null-terminated C-string and copy src into it.
char* copy_cstr(const char* src);

// Create a new Book on the heap; returns pointer to Book or nullptr on failure.
Book* create_book(const char* title, const char* author, int year);

// Free all resources owned by *book and delete the Book itself. Accepts nullptr.
void destroy_book(Book* book);

// Print a Book; accepts nullptr (prints a message).
void print_book(const Book* book);

// Compare two C-strings case-sensitively; returns true if equal. Accepts nullptrs.
bool cstr_equal(const char* a, const char* b);

// Read a full line from stdin into a newly allocated C-string (without trailing '\n').
// Returns nullptr on EOF or allocation failure. Caller owns the result and must delete[].
char* read_line_alloc(const char* prompt);

// ----------------------------------------------------------------------------------
// Library: dynamic array of Book* (double pointer usage: Book**)
// ----------------------------------------------------------------------------------
struct Library {
    Book** books;   // dynamic array of pointers to Book
    int    count;   // number of valid entries in [0, count)
    int    capacity;// allocated slots in books array
};

// Initialize an empty library
void init_library(Library* lib, int initial_capacity = 4);

// Free all books and the books array itself
void destroy_library(Library* lib);

// Ensure capacity >= min_capacity; grow (e.g., *2) if needed
bool ensure_capacity(Library* lib, int min_capacity);

// Add: takes ownership of `book` pointer on success; on failure, does NOT take ownership
bool add_book(Library* lib, Book* book);

// Find first book with matching title; returns pointer to Book or nullptr
Book* find_by_title(Library* lib, const char* title);

// Remove first book with matching title; returns true if removed (and frees it)
bool remove_by_title(Library* lib, const char* title);

// Swap two Book* at positions i and j using ONLY pointers (no refs)
void swap_books(Library* lib, int i, int j);

// List all books using pointer arithmetic instead of indexing
void list_books_ptr_arith(const Library* lib);

// ----------------------------------------------------------------------------------
// Menu helpers (provided; you may extend)
// ----------------------------------------------------------------------------------
void menu_loop();
void handle_add(Library* lib);
void handle_list(Library* lib);
void handle_find(Library* lib);
void handle_remove(Library* lib);

// ==================================================================================
// Implementations — Fill the TODOs
// ==================================================================================

char* copy_cstr(const char* src) {
    if (!src) return nullptr;
    std::size_t n = std::strlen(src);
    char* dst = new (std::nothrow) char[n + 1];
    if (!dst) return nullptr;
    for (std::size_t i = 0; i < n; ++i) dst[i] = src[i];
    dst[n] = '\0';
    return dst;
}

Book* create_book(const char* title, const char* author, int year) {
    // TODO: allocate Book with new (nothrow)
    // TODO: allocate and copy title & author using copy_cstr
    // TODO: on any failure, clean up and return nullptr
    // HINT: Set fields to owned pointers; keep year
    Book* b = nullptr; // replace with your allocation & initialization
    (void)title; (void)author; (void)year; // silence unused warnings during skeleton
    return b;
}

void destroy_book(Book* book) {
    if (!book) return;
    // TODO: delete[] title; delete[] author; then delete book
}

void print_book(const Book* book) {
    if (!book) {
        std::cout << "<null book>\n";
        return;
    }
    // NOTE: Handle potential nullptr fields defensively
    std::cout << "Title : " << (book->title ? book->title : "<null>") << "\n"
              << "Author: " << (book->author ? book->author : "<null>") << "\n"
              << "Year  : " << book->year << "\n";
}

bool cstr_equal(const char* a, const char* b) {
    if (a == b) return true;         // covers both nullptr or identical pointer
    if (!a || !b) return false;
    // Compare character by character (avoid strcmp for learning)
    for (; *a && *b; ++a, ++b) {
        if (*a != *b) return false;
    }
    return *a == *b; // both must be '\0'
}

char* read_line_alloc(const char* prompt) {
    if (prompt) std::cout << prompt;
    std::string tmp; // Using std::string as a buffer for I/O convenience only
    if (!std::getline(std::cin, tmp)) return nullptr;
    return copy_cstr(tmp.c_str()); // Return an owned C-string
}

void init_library(Library* lib, int initial_capacity) {
    if (!lib) return;
    lib->count = 0;
    lib->capacity = (initial_capacity > 0 ? initial_capacity : 4);
    // TODO: allocate books array with new (nothrow) Book*[capacity]; set to nullptrs
    lib->books = nullptr; // placeholder
}

void destroy_library(Library* lib) {
    if (!lib) return;
    // TODO: free all Book* in the array (destroy_book), then delete[] the array
    lib->books = nullptr;
    lib->count = 0;
    lib->capacity = 0;
}

bool ensure_capacity(Library* lib, int min_capacity) {
    if (!lib) return false;
    // TODO: if capacity >= min_capacity, return true
    // TODO: compute new_capacity (e.g., max(capacity*2, min_capacity))
    // TODO: allocate new Book** array, copy old pointers, delete[] old array
    // HINT: Do not allocate/copy Book objects here, only the pointer array
    (void)min_capacity; // silence warning in skeleton
    return false; // replace with true/false
}

bool add_book(Library* lib, Book* book) {
    if (!lib || !book) return false;
    // TODO: ensure capacity for count+1
    // TODO: insert pointer; increment count; take ownership
    return false; // replace
}

Book* find_by_title(Library* lib, const char* title) {
    if (!lib || !title) return nullptr;
    // TODO: iterate using either indexing or pointer arithmetic and compare titles
    // Return the matching Book* or nullptr
    return nullptr;
}

bool remove_by_title(Library* lib, const char* title) {
    if (!lib || !title) return false;
    // TODO: find index; destroy_book on the removed element
    // TODO: shift remaining pointers left (no gaps), decrement count
    return false;
}

void swap_books(Library* lib, int i, int j) {
    if (!lib) return;
    if (i < 0 || j < 0 || i >= lib->count || j >= lib->count) return;
    // TODO: implement purely with pointers to elements (no std::swap, no references)
}

void list_books_ptr_arith(const Library* lib) {
    if (!lib) return;
    // Iterate using pointer arithmetic (Book** p = lib->books; *(p + i))
    // TODO: print index + 1 and book details via print_book
}

// ----------------------------------------------------------------------------------
// Minimal console UI to exercise the API
// ----------------------------------------------------------------------------------

void handle_add(Library* lib) {
    char* title = read_line_alloc("Title: ");
    if (!title) return;
    char* author = read_line_alloc("Author: ");
    if (!author) { delete[] title; return; }

    std::cout << "Year: ";
    int year = 0;
    if (!(std::cin >> year)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid year.\n";
        delete[] title; delete[] author;
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // eat newline

    Book* b = create_book(title, author, year);
    // We copied strings inside create_book, so free the temporary inputs
    delete[] title; delete[] author;

    if (!b) { std::cout << "Allocation failed.\n"; return; }

    if (!add_book(lib, b)) {
        std::cout << "Add failed.\n";
        destroy_book(b); // we still own it on failure
    }
}

void handle_list(Library* lib) {
    list_books_ptr_arith(lib);
}

void handle_find(Library* lib) {
    char* title = read_line_alloc("Find Title: ");
    if (!title) return;
    Book* b = find_by_title(lib, title);
    if (b) print_book(b); else std::cout << "Not found.\n";
    delete[] title;
}

void handle_remove(Library* lib) {
    char* title = read_line_alloc("Remove Title: ");
    if (!title) return;
    bool ok = remove_by_title(lib, title);
    std::cout << (ok ? "Removed.\n" : "Not found.\n");
    delete[] title;
}

void menu_loop() {
    Library lib{};
    init_library(&lib, 4);

    bool running = true;
    while (running) {
        std::cout << "\n--- Library Menu ---\n"
                  << "1) Add book\n"
                  << "2) List books\n"
                  << "3) Find by title\n"
                  << "4) Remove by title\n"
                  << "5) Swap first two (demo)\n"
                  << "0) Quit\n"
                  << "> ";
        int choice = -1;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: handle_add(&lib); break;
            case 2: handle_list(&lib); break;
            case 3: handle_find(&lib); break;
            case 4: handle_remove(&lib); break;
            case 5:
                if (lib.count >= 2) { swap_books(&lib, 0, 1); std::cout << "Swapped.\n"; }
                else { std::cout << "Need at least 2 books.\n"; }
                break;
            case 0: running = false; break;
            default: break;
        }
    }

    destroy_library(&lib);
}

int main() {
    std::cout << "Dynamic Library System (Pointers Practice)\n";
    menu_loop();
    return 0;
}
