#ifndef EDITDISTANCE_UTILS_H
#define EDITDISTANCE_UTILS_H

#include <vector>
#include <string>
#include <cstdint>  // SIZE_MAX
#include <algorithm>  // min
#include <utility>  // swap

template <class charT>
size_t editDistance(const std::basic_string<charT>& str1, const std::basic_string<charT>& str2, \
                    bool transposition) {
    // O(n) memory instead of the matrix solution with O(n*m) memory
    size_t size1 = str1.size(), size2 = str2.size();
    std::vector<size_t> prevPrevRow, prevRow(size1 + 1), currentRow(size1 + 1);
    if (transposition) prevPrevRow = std::vector<size_t>(size1 + 1);
    for (size_t index = 1; index <= size1; index++) prevRow[index] = index;

    size_t insertDistance, deleteDistance, substituteDistance, transposeDistance = SIZE_MAX;
    bool transposed;
    for (size_t row = 1; row <= size2; row++) {
        currentRow[0] = row;
        for (size_t column = 1; column <= size1; column++) {
            insertDistance = prevRow[column] + 1;
            deleteDistance = currentRow[column - 1] + 1;
            substituteDistance = prevRow[column - 1] + (str1[row - 1] != str2[column - 1]);
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
    size_t size = perm.size();
    std::vector<bool> visited(size, false);
    size_t transpos = 0;
    size_t cycle = 0;
    size_t current = 0;

    for (size_t index = 0; index < size; index++) {
        if (visited.at(index) || perm.at(index) == index + 1) continue;
        while (!visited.at(current)) {
            visited.at(current) = true;
            current = perm.at(current) - 1;
            cycle++;
        }
        transpos += cycle - 1;
    }

    return transpos;
}

#endif // EDITDISTANCE_UTILS_H
