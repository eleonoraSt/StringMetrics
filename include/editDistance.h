#ifndef EDITDISTANCE_H
#define EDITDISTANCE_H

#include <stdexcept>

#include "editDistance_utils.h"

template <class charT>
size_t Levenstein(const std::basic_string<charT>& str1, const std::basic_string<charT>& str2) {
    return editDistance(str1, str2, false);
}

template <class charT>
size_t DamerauLevenstein(const std::basic_string<charT>& str1, const std::basic_string<charT>& str2) {
    return editDistance(str1, str2, true);
}

template <class charT>
size_t Hamming(const std::basic_string<charT>& str1, const std::basic_string<charT>& str2) {
    size_t size1 = sizeInVarLengthChar(str1), size2 = sizeInVarLengthChar(str2);
    if (size1 != size2) throw std::invalid_argument("Hamming distance not applicable");
    size_t distance = 0;
    size_t pos1 = 0, pos2 = 0;
    while (pos1 < size1 && pos2 < size2) {
        if (isContinuation(str1[pos1])) {
            pos1++;
            continue;
        }
        if (isContinuation(str2[pos2])) {
            pos2++;
            continue;
        }
        if (!equalChars(str1, pos1, str2, pos2)) distance++;
        pos1++;
        pos2++;
    }
    return distance;
}

template <class charT>
size_t Lcs(const std::basic_string<charT>& str1, const std::basic_string<charT>& str2) {
    size_t size1 = sizeInVarLengthChar(str1), size2 = sizeInVarLengthChar(str2);
    std::vector<size_t> prevRow(size1 + 1), currentRow(size1 + 1);

    for (size_t row = 1; row <= size2; row++) {
        if (isContinuation(str2[row])) continue;
        for (size_t column = 1; column <= size1; column++) {
            if (isContinuation(str1[column])) continue;
            if (equalChars(str1, column - 1, str2, row - 1)) {
                currentRow[column] = prevRow[column - 1] + 1;
            } else {
                currentRow[column] = std::max(prevRow[column], currentRow[column - 1]);
            }
        }
        std::swap(prevRow, currentRow);
    }

    return prevRow[size1];
}

#endif // EDITDISTANCE_H
