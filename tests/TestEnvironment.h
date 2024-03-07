/*
 * Copyright (c) Sayyedhassan Shavarani 2023
 * All rights reserved. Unauthorized redistribution is prohibited.
 */
#ifndef TESTENVIRONMENT_H
#define TESTENVIRONMENT_H

#include "../include/Utils.h"

static inline int a_assert(bool condition) {
    return condition ? 1 : 0;
}

class TestEnvironment {
public:
    Patron user1;
    Patron user2;
    Patron user3;
    Patron user4;
    Patron user5;
    Patron user6;
    Patron user7;
    Patron user8;
    Patron user9;
    Patron user10;
    Book book1;
    Book book2;
    Book book3;
    Book book4;
    Book book5;
    Book book6;
    Book book7;
    Book book8;
    Book book9;
    Book book10;
    BorrowRecord record1;
    BorrowRecord record2;
    BorrowRecord record3;
    BorrowRecord record4;
    BorrowRecord record5;
    BorrowRecord record6;
    BorrowRecord record7;
    BorrowRecord record8;
    BorrowRecord record9;
    TestEnvironment() {
        user1 = Patron();
        user1.ID = "user1";
        user2 = Patron();
        user2.ID = "user2";
        user3 = Patron();
        user3.ID = "user3";
        user4 = Patron();
        user4.ID = "user4";
        user4.email = "brandon.gillespie@morris.com";
        user5 = Patron();
        user5.ID = "user5";
        user5.name = "Charles Williams";
        user6 = Patron();
        user6.ID = "user6";
        user7 = Patron();
        user7.ID = "user7";
        user8 = Patron();
        user8.ID = "user8";
        user9 = Patron();
        user9.ID = "user9";
        user10 = Patron();
        user10.ID = "user10";

        book1 = Book();
        book1.ISBN = "0486411044";
        book1.title = "First Fig and Other Poems (Dover Thrift Editions)";
        book1.author = "Edna St. Vincent Millay";
        book2 = Book();
        book2.ISBN = "0289796997";
        book2.title = "Canvas embroidery for beginners";
        book2.author = "Sylvia Green";
        book3 = Book();
        book3.ISBN = "0801485045";
        book3.title = "Racism and Philosophy";
        book3.author = "Susan E. Babbitt";
        book4 = Book();
        book4.ISBN = "0446973483";
        book4.title = "Until the Sun Dies";
        book4.author = "Robert Jastrow";
        book5 = Book();
        book5.ISBN = "0233990925";
        book5.title = "Spook Files: Fiends from Planet X (The Spook Files)";
        book5.author = "Michael Johnstone";
        book6 = Book();
        book6.ISBN = "034542705X";
        book6.title = "The Man Who Listens to Horses";
        book6.author = "Monty Roberts";
        book7 = Book();
        book7.ISBN = "0440331420";
        book7.title = "Great Russian Short Stories";
        book7.author = "Norris Houghton";
        book8 = Book();
        book8.ISBN = "0570060184";
        book8.title = "Daniel in the Lions Den (Arch Books: Set 3)";
        book8.author = "Jane Latourette";
        book9 = Book();
        book9.ISBN = "0739429736";
        book9.title = "500 Low-Carb Recipes (500 Recipes, from Snacks to Dessert)";
        book9.author = "Dana Carpender";
        book10 = Book();
        book10.ISBN = "0515118567";
        book10.title = "Darkest Instinct";
        book10.author = "Robert W. Walker";
        
        record1.bookISBN = book1.ISBN;
        record1.patronId = user1.ID;
        record1.checkoutDate = Date::parseDate("2022-09-01");
        record1.returnDate = Date::parseDate("2023-09-15");
        record2.bookISBN = book2.ISBN;
        record2.patronId = user1.ID;
        record2.checkoutDate = Date::parseDate("2023-09-05");
        record2.returnDate = Date::parseDate("2023-09-20");
        record3.bookISBN = book3.ISBN;
        record3.patronId = user2.ID;
        record3.checkoutDate = Date::parseDate("2023-09-10");
        record3.returnDate = Date::parseDate("2023-09-25");
        record4.bookISBN = book4.ISBN;
        record4.patronId = user3.ID;
        record4.checkoutDate = Date::parseDate("2023-09-03");
        record4.returnDate = Date::parseDate("2023-09-18");
        record5.bookISBN = book5.ISBN;
        record5.patronId = user3.ID;
        record5.checkoutDate = Date::parseDate("2023-09-07");
        record5.returnDate = Date::parseDate("2023-09-22");
        record6.bookISBN = book6.ISBN;
        record6.patronId = user4.ID;
        record6.checkoutDate = Date::parseDate("2023-09-08");
        record6.returnDate = Date::parseDate("2023-09-17");
        record7.bookISBN = book1.ISBN;
        record7.patronId = user1.ID;
        record7.checkoutDate = Date::parseDate("2022-01-01");
        record7.returnDate = Date::parseDate("2022-01-10");
        record8.bookISBN = book2.ISBN;
        record8.patronId = user1.ID;
        record8.checkoutDate = Date::parseDate("2022-02-01");
        record8.returnDate = Date::parseDate("2022-02-10");
        record9.bookISBN = book2.ISBN;
        record9.patronId = user2.ID;
        record9.checkoutDate = Date::parseDate("2022-03-02");
        record9.returnDate = Date::parseDate("2022-03-15");
    }
};

#endif //TESTENVIRONMENT_H
