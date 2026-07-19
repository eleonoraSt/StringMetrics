#ifndef EDITDISTANCE_H
#define EDITDISTANCE_H

#include "editDistance_utils.h"

constexpr short LEVENSTEIN = 7;
constexpr short DAMERAU_LEVENSTEIN = 15;

template <class charT>
size_t Levenstein(const std::basic_string<charT>& str1, const std::basic_string<charT>& str2) {
    return editDistance(str1, str2, std::bitset<OPERATIONS_NUM>(LEVENSTEIN));
}

template <class charT>
size_t DamerauLevenstein(const std::basic_string<charT>& str1, const std::basic_string<charT>& str2) {
    return editDistance(str1, str2, std::bitset<OPERATIONS_NUM>(DAMERAU_LEVENSTEIN));
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
    Matrix<size_t> matrix(str1.size() + 1, str2.size() + 1);

    size_t size1 = str1.size(), size2 = str2.size();
    for (size_t row = 1; row <= size2; row++) {
        for (size_t column = 1; column <= size1; column++) {
            size_t subseq;
            if (str1.at(column) == str2.at(row)) {
                subseq = matrix.Get(row - 1, column - 1) + 1;
            } else {
                subseq = std::max(matrix.Get(row - 1, column), matrix.Get(row, column - 1));
            }
            matrix.Set(subseq, row, column);
        }
    }

    return matrix.Get(size2, size1);
}

#endif // EDITDISTANCE_H
