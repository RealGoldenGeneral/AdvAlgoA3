/*
 * Copyright (c) Sayyedhassan Shavarani 2023
 * All rights reserved. Unauthorized redistribution is prohibited.
 */
#ifndef DATE_H
#define DATE_H
#include <iostream>
#include <sstream>
#include <string>
// IMPORT ID: 1
// This class is already implemented and does not require any modification!
class Date {
public:
    Date(int year, int month, int day) : year_(year), month_(month), day_(day) {}

    int getYear() const { return year_; }
    int getMonth() const { return month_; }
    int getDay() const { return day_; }

    // Comparison operators for range-based for loop
    bool operator==(const Date& other) const {
        return year_ == other.year_ && month_ == other.month_ && day_ == other.day_;
    }

    bool operator!=(const Date& other) const {
        return !(*this == other);
    }

    bool operator<=(const Date& other) const {
        if (year_ != other.year_) return year_ < other.year_;
        if (month_ != other.month_) return month_ < other.month_;
        return day_ <= other.day_;
    }

    bool operator>(const Date& other) const {
        return !(*this <= other);
    }

    bool operator>=(const Date& other) const {
        return (*this > other) || (*this == other);
    }

    bool operator<(const Date& other) const {
        return !(*this >= other);
    }

    size_t getHash() const {
        return internalHash(*this);
    }

    struct Hash {
        size_t operator()(const Date& date) const {
            return (static_cast<size_t>(date.year_) << 9) | (static_cast<size_t>(date.month_) << 5) | static_cast<size_t>(date.day_);
        }
    };

    static Date parseDate(const std::string& dateString) {
        int year, month, day;
        char dash1, dash2;
        std::istringstream iss(dateString);
        iss >> year >> dash1 >> month >> dash2 >> day;

        if (iss.fail() || dash1 != '-' || dash2 != '-') {
            throw std::invalid_argument("Invalid date format. Expected YYYY-MM-DD.");
        }
        return {year, month, day};
    }

    static Date getNextDate(const Date& currentDate) {
        int year = currentDate.getYear();
        int month = currentDate.getMonth();
        int day = currentDate.getDay();

        // Calculate the next date based on the current date
        // You need to handle month overflow and leap years here
        // For simplicity, let's assume all months have 30 days and ignore leap years.
        day++;
        if (day > 30) {
            day = 1;
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }

        return {year, month, day};
    }

    static int diffDuration(const Date& startDate, const Date& endDate) {
        if (startDate.getYear() == endDate.getYear() && startDate.getMonth() == endDate.getMonth() &&
            startDate.getDay() == endDate.getDay()) {
            return 0;
        } else if (startDate.getYear() == endDate.getYear() && startDate.getMonth() == endDate.getMonth()) {
            return endDate.getDay() - startDate.getDay();
        }

        int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        int startYear = startDate.getYear();
        int startMonth = startDate.getMonth();
        int startDay = startDate.getDay();

        int endYear = endDate.getYear();
        int endMonth = endDate.getMonth();
        int endDay = endDate.getDay();

        int days = 0;

        for (int year = startYear; year < endYear; ++year) {
            days += 365;
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
                days += 1; // Leap year
        }

        if (startDate.getMonth() == endDate.getMonth())
            return days + (endDate.getDay() - startDate.getDay());

        if ((endYear % 4 == 0 && endYear % 100 != 0) || (endYear % 400 == 0))
            daysInMonth[2] = 29;

        for (int month = startMonth; month <= endMonth; ++month) {
            if (month == startMonth)
                days += daysInMonth[month] - startDay; // Days in start month
            else if (month == endMonth)
                days += endDay; // Days in end month
            else
                days += daysInMonth[month]; // Days in months between start and end
        }
        return days;
    }

private:
    int year_;
    int month_;
    int day_;
    Date::Hash internalHash;
};
#endif //DATE_H
