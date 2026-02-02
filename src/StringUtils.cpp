#include "StringUtils.h"
#include <cctype>
#include <algorithm>
#include <sstream>
#include <vector>
#include <string>

namespace StringUtils {

std::string Slice(const std::string &str, ssize_t start, ssize_t end) noexcept {
    ssize_t len = str.size();
    if (start < 0) start += len;
    if (end <= 0) end += len;
    if (start < 0) start = 0;
    if (end > len) end = len;
    if (start >= end) return "";
    return str.substr(start, end - start);
}

std::string Capitalize(const std::string &str) noexcept {
    if (str.empty()) return "";
    std::string result = str;
    result[0] = std::toupper(result[0]);
    std::transform(result.begin() + 1, result.end(), result.begin() + 1, ::tolower);
    return result;
}

std::string Upper(const std::string &str) noexcept {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

std::string Lower(const std::string &str) noexcept {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::string LStrip(const std::string &str) noexcept {
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    if (start == std::string::npos) return "";
    return str.substr(start);
}

std::string RStrip(const std::string &str) noexcept {
    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    if (end == std::string::npos) return "";
    return str.substr(0, end + 1);
}

std::string Strip(const std::string &str) noexcept {
    return LStrip(RStrip(str));
}

std::string Center(const std::string &str, int width, char fill) noexcept {
    int diff = width - str.size();

    if (diff <= 0) {
        return str;
    }

    if (diff == 1) {
        return str + fill;
    }

    // diff >= 2
    return std::string(1, fill) + str + std::string(1, fill);
}

std::string LJust(const std::string &str, int width, char fill) noexcept {
    int pad = width - str.size() - 1;
    if (pad <= 0) return str;
    return str + std::string(pad, fill);
}

std::string RJust(const std::string &str, int width, char fill) noexcept {
    int pad = width - str.size() - 1;
    if (pad <= 0) return str;
    return std::string(pad, fill) + str;
}

std::string Replace(const std::string &str, const std::string &old, const std::string &rep) noexcept {
    std::string result = str;
    size_t pos = 0;
    while ((pos = result.find(old, pos)) != std::string::npos) {
        result.replace(pos, old.length(), rep);
        pos += rep.length();
    }
    return result;
}

std::vector<std::string> Split(const std::string &str, const std::string &splt) noexcept {
    std::vector<std::string> result;
    if (splt.empty()) {
        std::istringstream iss(str);
        std::string token;
        while (iss >> token) result.push_back(token);
    } else {
        size_t start = 0, end;
        while ((end = str.find(splt, start)) != std::string::npos) {
            result.push_back(str.substr(start, end - start));
            start = end + splt.size();
        }
        result.push_back(str.substr(start));
    }
    return result;
}

std::string Join(const std::string &sep, const std::vector<std::string> &vect) noexcept {
    std::string result;
    for (size_t i = 0; i < vect.size(); ++i) {
        result += vect[i];
        if (i != vect.size() - 1) result += sep;
    }
    return result;
}

std::string ExpandTabs(const std::string &str, int tabsize) noexcept {
    std::string result;
    bool at_line_start = true;

    for (char c : str) {
        if (c == '\t') {
            result.append(at_line_start ? tabsize : tabsize - 1, ' ');
            at_line_start = false;
        } else {
            result.push_back(c);
            at_line_start = (c == '\n');
        }
    }
    return result;
}

int EditDistance(const std::string &left, const std::string &right, bool ignorecase) {
    std::string s1 = left;
    std::string s2 = right;

    if (ignorecase) {
        for (size_t i = 0; i < s1.size(); ++i) s1[i] = std::tolower(s1[i]);
        for (size_t i = 0; i < s2.size(); ++i) s2[i] = std::tolower(s2[i]);
    }

    int m = s1.size();
    int n = s2.size();

    if (m == 0) return n;
    if (n == 0) return m;

    if (s1[m - 1] == s2[n - 1])
        return EditDistance(s1.substr(0, m - 1), s2.substr(0, n - 1), false);

    int insertOp = EditDistance(s1, s2.substr(0, n - 1), false);
    int deleteOp = EditDistance(s1.substr(0, m - 1), s2, false);
    int replaceOp = EditDistance(s1.substr(0, m - 1), s2.substr(0, n - 1), false);

    return 1 + std::min(insertOp, std::min(deleteOp, replaceOp));
}

}
