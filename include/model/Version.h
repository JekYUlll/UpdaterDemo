//
// Created by horeb on 25-4-18.
//

#ifndef VERSION_H
#define VERSION_H

#include <iostream>
#include <ostream>
#include <regex>
#include <string>

namespace udc {

struct Version {
    int major;
    int minor;
    int patch;
    std::string prerelease; // e.g. "alpha", "beta1", "rc.1"

    Version() : major(0), minor(0), patch(0) {}

    explicit Version(const char* versionStr) {
        std::string version(versionStr);
        const size_t firstDot = version.find('.');
        const size_t secondDot = version.find('.', firstDot + 1);
        major = std::stoi(version.substr(0, firstDot));
        minor = std::stoi(version.substr(firstDot + 1, secondDot - firstDot - 1));
        patch = std::stoi(version.substr(secondDot + 1));
    }

    [[nodiscard]] std::string toString() const {
        std::ostringstream ss;
        ss << major << "." << minor << "." << patch;
        if (!prerelease.empty()) {
            ss << "-" << prerelease;
        }
        return ss.str();
    }

    static Version parse(const std::string& str) {
        Version v;
        std::regex versionRegex(R"((\d+)\.(\d+)\.(\d+)(?:-([\w\.\-]+))?)");
        std::smatch match;
        if (std::regex_match(str, match, versionRegex)) {
            v.major = std::stoi(match[1]);
            v.minor = std::stoi(match[2]);
            v.patch = std::stoi(match[3]);
            if (match[4].matched)
                v.prerelease = match[4];
        } else {
            // todo
            // fallback or throw
            LOG_E("Failed to parse version: {}.", str);
        }
        return v;
    }

    bool operator==(const Version& other) const {
        return std::tie(major, minor, patch, prerelease) ==
               std::tie(other.major, other.minor, other.patch, other.prerelease);
    }

    bool operator<(const Version& other) const {
        if (std::tie(major, minor, patch) < std::tie(other.major, other.minor, other.patch))
            return true;
        if (std::tie(major, minor, patch) > std::tie(other.major, other.minor, other.patch))
            return false;
        // both numeric parts are equal, now compare prerelease
        if (prerelease.empty() && !other.prerelease.empty()) return false; // release > prerelease
        if (!prerelease.empty() && other.prerelease.empty()) return true;
        return prerelease < other.prerelease;
    }

    bool operator!=(const Version& other) const { return !(*this == other); }
    bool operator>(const Version& other) const { return other < *this; }
    bool operator<=(const Version& other) const { return !(*this > other); }
    bool operator>=(const Version& other) const { return !(*this < other); }

    friend std::ostream& operator<<(std::ostream& os, const Version& obj) {
        return os << "major: " << obj.major << " minor: " << obj.minor
                  << " patch: " << obj.patch << " prerelease: " << obj.prerelease;
    }
};

}

#endif //VERSION_H
