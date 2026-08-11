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
    if (str1.size() != str2.size()) throw std::invalid_argument("Hamming distance not applicable");
    size_t distance = 0;
    auto it1 = str1.begin();
    auto it2 = str2.begin();
    auto finish1 = str1.end();
    while (it1 != finish1) {
        if (*it1 != *it2) distance++;
        it1++;
        it2++;
    }
    return distance;
}

template <class charT>
size_t Lcs(const std::basic_string<charT>& str1, const std::basic_string<charT>& str2) {
    size_t size1 = str1.size(), size2 = str2.size();
    std::vector<size_t> prevRow(size1 + 1), currentRow(size1 + 1);

    for (size_t row = 1; row <= size2; row++) {
        for (size_t column = 1; column <= size1; column++) {
            size_t subseq;
            if (str1.at(column - 1) == str2.at(row - 1)) {
                subseq = prevRow[column - 1] + 1;
            } else {
                subseq = std::max(prevRow[column], currentRow[column - 1]);
            }
            currentRow[column] = subseq;
        }
        std::swap(prevRow, currentRow);
    }

    return currentRow[size1];
}

#endif // EDITDISTANCE_H
