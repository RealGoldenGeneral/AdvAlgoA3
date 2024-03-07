/*
 * Copyright (c) Sayyedhassan Shavarani 2023
 * All rights reserved. Unauthorized redistribution is prohibited.
 */
#ifndef LEXCEPTIONS_H
#define LEXCEPTIONS_H
#include <stdexcept>
#include "Utils.h"

class ReservationRecordUnavailable : public std::exception {
public:
    const char * what () {
        return "No reservation record is available to process!";
    }
};

class LibraryReservationQueueFull : public std::exception {
public:
    const char * what () {
        return "Library does not have the resources to receive your reservation request, please try again later!";
    }
};

class UnavailableBookToBorrow : public std::exception {
private:
    Book book;

public:
    explicit UnavailableBookToBorrow(Book& b) : book(b) {}
    const char * what () {
        return "Book unavailable to borrow!";
    }
};

class InvalidBorrowRecordDates : public std::exception {
public:
    const char * what () {
        return "Checkout date must be before or equal to return date!";
    }
};

#endif //LEXCEPTIONS_H
