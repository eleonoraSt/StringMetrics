#ifndef EDITDISTANCE_UTILS_H
#define EDITDISTANCE_UTILS_H

#include <vector>
#include <string>
#include <cstdint>  // SIZE_MAX
#include <algorithm>  // min
#include <utility>  // swap

// Determines the length of the variable length character in char
short multibyteCharLenUTF8(char highByte);

// Compares characters that may be of variable length in UTF-8 strings (1-byte chars)
bool equalCharsUTF8(const std::string& str1, size_t pos1, const std::string& str2, size_t pos2);

// Determines the length of the variable length character in char16_t
short multibyteCharLenUTF16(char16_t highBytes);

// Compares characters that may be of variable length in UTF-16 strings (2-byte chars)
bool equalCharsUTF16(const std::u16string& str1, size_t pos1, const std::u16string& str2, size_t pos2);

// Compares chars that may be multibyte
template <class charT>
bool equalChars(const std::basic_string<charT>& str1, size_t pos1, const std::basic_string<charT>& str2, \
                size_t pos2) {
    short size = sizeof(charT);
    switch (size) {
    case 1:
        return equalCharsUTF8(str1, pos1, str2, pos2);
    case 2:
        return equalCharsUTF16(str1, pos1, str2, pos2);
    default:  // 4-byte chars do not have variable length
        return str1.at(pos1) == str2.at(pos2);
    }
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
