#include "rule.h"

#include <stdexcept>
#include <cctype>
#include <array>

static int digit_0_8(char c) {
    if (c < '0' || c > '8') return -1;
    return c - '0';
}

uint8_t Rule::decide(int n, uint8_t alive) const noexcept {
    return alive ? ((surviveMask >> n) & 1u) : ((birthMask >> n) & 1u);
}

static bool isSpace(char c) noexcept {
    return std::isspace(c) != 0;
}

Rule::Rule(const std::string& s) {
    enum class Sec { None, B, S };
    Sec sec = Sec::None;

    std::array<bool,9> seenB{};
    std::array<bool,9> seenS{};

    std::size_t i = 0, n = s.size();

    while (i < n && isSpace(s[i])) {++i;}

    if (i < n && s[i] == '#') {
        ++i;
        while (i < n && isSpace(s[i])) {++i;}
        if (i < n && (s[i] == 'R' || s[i] == 'r')) ++i;
        while (i < n && isSpace(s[i])) {++i;}
    }

    bool hasB = false, hasS = false;

    while (i < n) {
        while (i < n && isSpace(s[i])) {++i;}
        if (i >= n) break;
        char c = s[i];
        if (c == 'B' || c == 'b') { sec = Sec::B; hasB = true; ++i; continue; }
        if (c == 'S' || c == 's') { sec = Sec::S; hasS = true; ++i; continue; }
        if (c == '/') { ++i; continue; }

        int d = digit_0_8(c);
        if (d >= 0) {
            if (sec == Sec::B) {
                if (seenB[d]) throw std::invalid_argument("duplicate digit in B");
                seenB[d] = true;
                birthMask |= (1u << d);
            } else if (sec == Sec::S) {
                if (seenS[d]) throw std::invalid_argument("duplicate digit in S");
                seenS[d] = true;
                surviveMask |= (1u << d);
            } else {
                throw std::invalid_argument("digit before B/S section");
            }
            ++i;
            continue;
        }

        throw std::invalid_argument("unexpected character in rule");
    }

    if (!hasB || !hasS) {
        throw std::invalid_argument("both B and S sections are required");
    }
}

void Rule::loadRule(const std::string &s) {
    enum class Sec { None, B, S };
    Sec sec = Sec::None;

    std::array<bool,9> seenB{};
    std::array<bool,9> seenS{};

    std::size_t i = 0, n = s.size();

    while (i < n && isSpace(s[i])) {++i;}

    if (i < n && s[i] == '#') {
        ++i;
        while (i < n && isSpace(s[i])) {++i;}
        if (i < n && (s[i] == 'R' || s[i] == 'r')) ++i;
        while (i < n && isSpace(s[i])) {++i;}
    }

    bool hasB = false, hasS = false;

    while (i < n) {
        while (i < n && isSpace(s[i])) {++i;}
        if (i >= n) break;
        char c = s[i];
        if (c == 'B' || c == 'b') { sec = Sec::B; hasB = true; ++i; continue; }
        if (c == 'S' || c == 's') { sec = Sec::S; hasS = true; ++i; continue; }
        if (c == '/') { ++i; continue; }

        int d = digit_0_8(c);
        if (d >= 0) {
            if (sec == Sec::B) {
                if (seenB[d]) throw std::invalid_argument("duplicate digit in B");
                seenB[d] = true;
                birthMask |= (1u << d);
            } else if (sec == Sec::S) {
                if (seenS[d]) throw std::invalid_argument("duplicate digit in S");
                seenS[d] = true;
                surviveMask |= (1u << d);
            } else {
                throw std::invalid_argument("digit before B/S section");
            }
            ++i;
            continue;
        }

        throw std::invalid_argument("unexpected character in rule");
    }

    if (!hasB || !hasS) {
        throw std::invalid_argument("both B and S sections are required");
    }
}

std::string Rule::getRule() const noexcept {
    std::string rule = "#R B";
    for(int i = 0; i < 9; ++i){
        if(birthMask & (1u << i)){
            rule += std::to_string(i);
        }
    }
    rule += "/S";
    for(int i = 0; i < 9; ++i){
        if(surviveMask & (1u << i)){
            rule += std::to_string(i);
        }
    }
    return rule;
}
