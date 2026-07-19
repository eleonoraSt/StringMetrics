#ifndef EDITDISTANCE_UTILS_H
#define EDITDISTANCE_UTILS_H

#include <cstdint>  // SIZE_MAX
#include <bitset>
#include <algorithm>  // min

#include "EditDistanceMatrix.h"

template <class charT>
size_t editDistance(const std::basic_string<charT>& str1, const std::basic_string<charT>& str2, \
                    std::bitset<4> operations) {
    EditDistanceMatrix<charT> matrix(str1.size(), str2.size());
    matrix.Prepare();

    size_t size1 = str1.size(), size2 = str2.size();
    for (size_t row = 1; row <= size2; row++) {
        for (size_t column = 1; column <= size1; column++) {
            size_t insertDistance = operations[0] ? matrix.InsertDistance(row, column) : SIZE_MAX;
            size_t deleteDistance = operations[1] ? matrix.DeleteDistance(row, column) : SIZE_MAX;
            size_t substituteDistance = operations[2] ? matrix.SubstituteDistance(row, column) : SIZE_MAX;
            size_t transposeDistance = operations[3] ? matrix.TransposeDistance(row, column) : SIZE_MAX;
            size_t minDistance = std::min({insertDistance, deleteDistance, substituteDistance, \
                                           transposeDistance});
            matrix.Set(minDistance, row, column);
        }
    }

    return matrix.Get(size2, size1);
}

#endif // EDITDISTANCE_UTILS_H
