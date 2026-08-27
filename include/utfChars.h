#ifndef UTFCHARS_H
#define UTFCHARS_H

/*
 * This header provides tools for working with variable length characters in UTF encodings.
 * The given templates are meant to work with all C++ character types for which there are instatiations of std::basic_string
 * (char, char16_t, char32_t, wchar_t), except:
 * multibyteCharLenUTF8, equalCharsUTF8 - char (1 byte)
 * multibyteCharLenUTF16, equalCharsUTF16 - char16_t, wchar_t (2 bytes)
 */

#include <stdexcept>

#define UPPER_2_BITS_MASK 0xC0
#define UPPER_BIT_MASK 0x80
#define MIN_INITIAL_2_BYTES 0xD800
#define MIN_CONTINUATION_2_BYTES 0xDC00

// Determines the length of the variable length character in char
template <class charT>
short multibyteCharLenUTF8(charT highByte) {
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

// Compares characters that may be of variable length in UTF-8 strings (1-byte chars)
template <class charT>
bool equalCharsUTF8(const std::basic_string<charT>& str1, size_t pos1, const std::basic_string<charT>& str2, size_t pos2) {
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

// Determines the length of the variable length character in 2-byte char
template <class charT>
short multibyteCharLenUTF16(charT highBytes) {
    // May throw: std::invalid_argument
    if (highBytes >= MIN_CONTINUATION_2_BYTES) {  // not the high byte
        throw std::invalid_argument("Position points at continuation byte");
    }
    return highBytes < MIN_INITIAL_2_BYTES ? 1 : 2;
}

// Compares characters that may be of variable length in UTF-16 strings (2-byte chars)
template <class charT>
bool equalCharsUTF16(const std::basic_string<charT>& str1, size_t pos1, const std::basic_string<charT>& str2, size_t pos2) {
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

// Compares chars that may be multibyte
template <class charT>
bool equalChars(const std::basic_string<charT>& str1, size_t pos1, const std::basic_string<charT>& str2, \
                size_t pos2) {
    switch (sizeof(charT)) {
    case 1:
        return equalCharsUTF8(str1, pos1, str2, pos2);
    case 2:
        return equalCharsUTF16(str1, pos1, str2, pos2);
    default:  // 4-byte chars do not have variable length
        return str1.at(pos1) == str2.at(pos2);
    }
}

template <class charT>
bool isContinuation(charT character) {
    switch (sizeof(charT)) {
    case 1:
        return (character & UPPER_2_BITS_MASK) == UPPER_BIT_MASK;
    case 2:
        return character > MIN_CONTINUATION_2_BYTES;
    default:  // 4-byte chars do not have variable length
        return false;
    }
}

template <class charT>
size_t sizeInVarLengthChar(const std::basic_string<charT>& str) {
    size_t size = str.size();
    if (sizeof(charT) == 4) return size;  // 4-byte chars do not have variable length
    size_t chars = 0;
    for (size_t index = 0; index < size; index++) {
        if (!isContinuation(str[index])) chars++;
    }
    return chars;
}

#endif // UTFCHARS_H
