#include "..\include\editDistance_utils.h"

#include <stdexcept>

short multibyteCharLenUTF8(char highByte) {
    // May throw: std::invalid_argument
    char mask = UPPER_BIT_MASK;
    short count = 0;
    bool equal = true;
    while (highByte & mask) {
        count++;
        mask >>= 1;
    }
    if (count == 1) {  // not the high byte
        throw std::invalid_argument("Position points at continuation byte");
    }
    if (count == 0) count++;  // 1 byte char
    return count;
}

bool equalCharsUTF8(const std::string& str1, size_t pos1, const std::string& str2, size_t pos2) {
    // May throw:
    // std::invalid_argument - if the pos points at a continuation byte
    // std::out_of_range - if the pos if out of range

    short charLen1 = multibyteCharLenUTF8(str1.at(pos1));
    short charLen2 = multibyteCharLenUTF8(str2.at(pos2));
    // std::invalid_argument or std::out_of_range may be thrown
    if (charLen1 != charLen2) return false;

    bool equal = true;
    for (int pos = 0; equal && pos < charLen1; pos++) {
        equal = str1.at(pos1) == str2.at(pos2);
    }
    return equal;
}

short multibyteCharLenUTF16(char16_t highBytes) {
    // May throw: std::invalid_argument
    if (highBytes >= MIN_CONTINUATION_2_BYTES) {  // not the high byte
        throw std::invalid_argument("Position points at continuation byte");
    }
    return highBytes < MIN_INITIAL_2_BYTES ? 1 : 2;
}

bool equalCharsUTF16(const std::u16string& str1, size_t pos1, const std::u16string& str2, size_t pos2) {
    // May throw:
    // std::invalid_argument - if the pos points at a continuation byte
    // std::out_of_range - if the pos if out of range

    short charLen1 = multibyteCharLenUTF16(str1.at(pos1));
    short charLen2 = multibyteCharLenUTF16(str2.at(pos2));
    // std::invalid_argument or std::out_of_range may be thrown
    if (charLen1 != charLen2) return false;

    bool equal = true;
    for (int pos = 0; equal && pos < charLen1; pos++) {
        equal = str1.at(pos1) == str2.at(pos2);
    }
    return equal;
}