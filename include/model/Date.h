//
// Created by horeb on 25-4-18.
//

#ifndef DATE_H
#define DATE_H

#include "log/Logger.h"

#include <format>
#include <ostream>
#include <sstream>
#include <string>

namespace udc {

struct Date {
    int year = 0;
    int month = 0;
    int day = 0;

    [[nodiscard]] std::string toString() const {
        return std::format("{:04}-{:02}-{:02}", year, month, day);
    }

    [[nodiscard]] bool isValid() const {
        return year > 0 && month > 0 && day > 0;
    }

    static Date parse(const std::string& str) {
        Date d;
        if (str.empty()) return d;
        std::istringstream ss(str);
        char sep1, sep2;
        ss >> d.year >> sep1 >> d.month >> sep2 >> d.day;
        if (sep1 != '-' || sep2 != '-' || ss.fail()) {
            LOG_D("parse error: {}", ss.str());
            return {};
        }
        return d;
    }

    static Date today() {
        std::time_t t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);
        return {tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday};
    }

    friend bool operator==(const Date& lhs, const Date& rhs) {
        return lhs.year == rhs.year && lhs.month == rhs.month &&
               lhs.day == rhs.day;
    }

    friend bool operator!=(const Date& lhs, const Date& rhs) {
        return !(lhs == rhs);
    }

    friend bool operator<(const Date& lhs, const Date& rhs) {
        if (lhs.year < rhs.year)
            return true;
        if (rhs.year < lhs.year)
            return false;
        if (lhs.month < rhs.month)
            return true;
        if (rhs.month < lhs.month)
            return false;
        return lhs.day < rhs.day;
    }

    friend bool operator<=(const Date& lhs, const Date& rhs) {
        return !(rhs < lhs);
    }

    friend bool operator>(const Date& lhs, const Date& rhs) {
        return rhs < lhs;
    }

    friend bool operator>=(const Date& lhs, const Date& rhs) {
        return !(lhs < rhs);
    }

    friend std::ostream& operator<<(std::ostream& os, const Date& obj) {
        return os << "year: " << obj.year << " month: " << obj.month
                  << " day: " << obj.day;
    }
};

} // namespace udc

#endif // DATE_H
