/*
 * Copyright (c) Sayyedhassan Shavarani 2023
 * All rights reserved. Unauthorized redistribution is prohibited.
 */
#ifndef UTILS_H
#define UTILS_H
/**
 * Implementation of the common data structures used to store library circulation data.
 */
#include <string>
#include <sstream>
// This is the only place that unordered_map is allowed to exist in the project solely because we need Utils.h to be
// Independent of other components.
#include <unordered_map>
#include "Date.h"
// IMPORT ID: 2
// The classes in this file are already implemented and do not require any modification!
class Book {
public:
    std::string ISBN;
    std::string title;
    std::string author;
    std::string publisher;
    std::string yearPublished;
    int copies;

    Book(std::string& bookISBN, std::string& bookTitle, std::string& bookAuthor, std::string& bookPublisher,
         std::string& bookYearPublished, std::string& bookCopies)
            : ISBN(bookISBN),
              title(bookTitle),
              author(bookAuthor),
              publisher(bookPublisher),
              yearPublished(bookYearPublished),
              copies(std::stoi(bookCopies)) {}

    Book(): copies(0) {}

    struct Hash {
        size_t operator()(const Book& book) const {
            // Combine the hash values of individual attributes to create a unique hash for the book
            size_t hashISBN = std::hash<std::string>{}(book.ISBN);
            size_t hashTitle = std::hash<std::string>{}(book.title);
            size_t hashAuthor = std::hash<std::string>{}(book.author);

            return hashISBN ^ hashTitle ^ hashAuthor;
        }
    };

    bool operator==(const Book& other) const {
        return internalHash(*this) == internalHash(other);
    }

    bool operator!=(const Book& other) const {
        return !(*this == other);
    }

    bool operator<(const Book& other) const {
        return internalHash(*this) < internalHash(other);
    }

    bool operator>(const Book& other) const {
        return internalHash(*this) > internalHash(other);
    }

    void reduceCopiesOnDate(const Date& date) {
        auto it = copiesOnDate.find(date);
        if (it == copiesOnDate.end()) {
            copiesOnDate[date] = copies;
        }

        if (copiesOnDate[date] <= 0) {
            throw std::exception();
        }

        copiesOnDate[date]--;
    }

    // Function to get the number of copies available on a specific date
    int getCopiesOnDate(const Date& date) const {
        auto it = copiesOnDate.find(date);
        if (it != copiesOnDate.end()) {
            return it->second;
        }
        return copies;
    }

private:
    Book::Hash internalHash;
    std::unordered_map<Date, int, Date::Hash> copiesOnDate;
};


class Patron {
public:
    std::string ID;
    std::string name;
    std::string email;
    std::string location;
    int age;

    Patron(std::string& ID, std::string& name, std::string& email,
           std::string& location, std::string& age): ID(ID), name(name), email(email), location(location) {
        this->age = age != "-" ? std::stoi(age): -1;
    }

    Patron(): age(0) {}

    struct Hash {
        std::size_t operator()(const Patron& patron) const {
            // Combine the hash of the userID for the unordered_set
            size_t patronID = std::hash<std::string>{}(patron.ID);
            size_t patronName = std::hash<std::string>{}(patron.name);
            size_t patronEmail = std::hash<std::string>{}(patron.email);
            size_t patronLocation = std::hash<std::string>{}(patron.location);

            return patronID ^ patronName ^ patronEmail ^ patronLocation;
        }
    };

    bool operator==(const Patron& other) const {
        return internalHash(*this) == internalHash(other);
    }

    bool operator!=(const Patron& other) const {
        return !(*this == other);
    }

    bool operator<(const Patron& other) const {
        return internalHash(*this) < internalHash(other);
    }

    bool operator>(const Patron& other) const {
        return internalHash(*this) > internalHash(other);
    }
private:
    Patron::Hash internalHash;
};

class BorrowRecord {
public:
    std::string patronId;
    std::string bookISBN;
    Date checkoutDate;
    Date returnDate;

    BorrowRecord(std::string& ID, std::string& ISBN, std::string& checkoutDate, std::string& returnDate): patronId(ID),
                                                                                                          bookISBN(ISBN), checkoutDate(Date::parseDate(checkoutDate)), returnDate(Date::parseDate(returnDate)) {}
    BorrowRecord(): checkoutDate(Date::parseDate("1971-01-01")), returnDate(Date::parseDate("1971-01-01")) {};

    struct Hash {
        std::size_t operator()(const BorrowRecord& borrowRecord) const {
            size_t pID = std::hash<std::string>{}(borrowRecord.patronId);
            size_t bISBN = std::hash<std::string>{}(borrowRecord.bookISBN);
            size_t cDate = borrowRecord.checkoutDate.getHash();
            size_t rDate = borrowRecord.returnDate.getHash();

            return pID ^ bISBN ^ cDate ^ rDate;
        }
    };

    bool operator==(const BorrowRecord& other) const {
        return internalHash(*this) == internalHash(other);
    }

    bool operator!=(const BorrowRecord& other) const {
        return !(*this == other);
    }

    bool operator<(const BorrowRecord& other) const {
        return internalHash(*this) < internalHash(other);
    }

    bool operator>(const BorrowRecord& other) const {
        return internalHash(*this) > internalHash(other);
    }

private:
    BorrowRecord::Hash internalHash;
};
#endif // UTILS_H