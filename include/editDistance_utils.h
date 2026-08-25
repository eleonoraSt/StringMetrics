#ifndef EDITDISTANCE_UTILS_H
#define EDITDISTANCE_UTILS_H

#include <vector>
#include <string>
#include <stdexcept>
#include <cstdint>  // SIZE_MAX
#include <algorithm>  // min
#include <utility>  // swap

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

// Levenstein or Damerau-Levenstein
template <class charT>
size_t editDistance(const std::basic_string<charT>& str1, const std::basic_string<charT>& str2, \
                    bool transposition) {
    // O(n) memory instead of the matrix solution with O(n*m) memory
    size_t size1 = str1.size(), size2 = str2.size();
    std::vector<size_t> prevPrevRow, prevRow(size1 + 1), currentRow(size1 + 1);
    if (transposition) prevPrevRow = std::vector<size_t>(size1 + 1);
    for (size_t index = 1; index <= size1; index++) prevRow[index] = index;

    size_t insertDistance, deleteDistance, substituteDistance, transposeDistance;
    bool transposed;
    for (size_t row = 1; row <= size2; row++) {
        currentRow[0] = row;
        for (size_t column = 1; column <= size1; column++) {
            insertDistance = prevRow[column] + 1;
            deleteDistance = currentRow[column - 1] + 1;
            substituteDistance = prevRow[column - 1] + (str1[column - 1] != str2[row - 1]);
            transposeDistance = SIZE_MAX;
            if (transposition && row > 1 && column > 1) {
                transposed = str1[column - 1] == str2[row - 2] && str1[column - 2] == str2[row - 1];
                if (transposed) transposeDistance = prevPrevRow[column - 2] + \
                                        (str1[column - 1] != str2[row - 1]);
            }
            currentRow[column] = std::min({insertDistance, deleteDistance, substituteDistance, \
                                           transposeDistance});
        }

        if (transposition) {
            std::swap(prevPrevRow, prevRow);
        }
        std::swap(prevRow, currentRow);
    }

    return prevRow[size1];
}

// May be needed later for Jaro
template <class T>
size_t transpositions(const std::vector<T>& perm) {
    // perm contains numbers from 1 to perm.size() + 1
    size_t size = perm.size();
    std::vector<bool> visited(size, false);
    size_t transpos = 0;
    size_t current = 0;

    for (size_t index = 0; index < size; index++) {
        if (visited.at(index) || perm.at(index) == index + 1) continue;
        transpos--;
        while (!visited.at(current)) {
            visited.at(current) = true;
            current = perm.at(current) - 1;
            transpos++;
        }
    }

    return transpos;
}

#endif // EDITDISTANCE_UTILS_H
