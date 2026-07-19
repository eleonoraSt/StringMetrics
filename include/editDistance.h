#ifndef EDITDISTANCE_H
#define EDITDISTANCE_H

#include "editDistance_utils.h"

constexpr short LEVENSTEIN = 7;
constexpr short DAMERAU_LEVENSTEIN = 15;
constexpr short LCS = 3;
constexpr short HAMMING = 4;
constexpr short JARO = 8;

template <class charT>
size_t Levenstein(const std::basic_string<charT>& str1, const std::basic_string<charT>& str2) {
    return editDistance(str1, str2, std::bitset<OPERATIONS_NUM>(LEVENSTEIN));
}

template <class charT>
size_t DamerauLevenstein(const std::basic_string<charT>& str1, const std::basic_string<charT>& str2) {
    return editDistance(str1, str2, std::bitset<OPERATIONS_NUM>(DAMERAU_LEVENSTEIN));
}

#endif // EDITDISTANCE_H
