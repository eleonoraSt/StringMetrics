#ifndef EDITDISTANCEMATRIX_H
#define EDITDISTANCEMATRIX_H

#include <string>
#include <stdexcept>

#include "Matrix.h"

// For Levenstein and Damerau-Levenstein distance calculation

template <class charT>
class EditDistanceMatrix: public Matrix<size_t> {
public:
    EditDistanceMatrix(size_t size1, size_t size2) {
        size1++;
        size2++;
        Matrix<size_t>(size1, size2);
        // Set initial values before calculating distance
        for (size_t index = 1; index < size1; index++) {
            Set(index, 0, index);
        }
        for (size_t index = 1; index < size2; index++) {
            Set(index, index, 0);
        }
    }

    size_t InsertDistance(size_t row, size_t column) {
        return Get(--row, column) + 1;
    }

    size_t DeleteDistance(size_t row, size_t column) {
        return Get(row, --column) + 1;
    }

    size_t SubstituteDistance(size_t row, size_t column, const std::basic_string<charT>& str1, \
                              const std::basic_string<charT>& str2) {
        return Get(row - 1, column - 1) + (str1.at(column) == str2.at(row));
    }

    size_t TransposeDistance(size_t row, size_t column, const std::basic_string<charT>& str1, \
                             const std::basic_string<charT>& str2) {
        if (str1.at(column - 1) != str2.at(row) || str1.at(column) != str2.at(row - 1)) {
            throw std::invalid_argument("Transposition not applicable");
        }
        return Get(row - 2, column - 2) + (str1.at(row) == str2.at(column));
    }
};

#endif // EDITDISTANCEMATRIX_H
