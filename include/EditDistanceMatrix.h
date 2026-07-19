#ifndef EDITDISTANCEMATRIX_H
#define EDITDISTANCEMATRIX_H

#include <string>
#include <stdexcept>

#include "Matrix.h"

// For Levenstein and Damerau-Levenstein distance calculation

template <class charT>
class EditDistanceMatrix: private Matrix<size_t> {
public:
    EditDistanceMatrix(size_t size1, size_t size2) {
        Matrix<size_t>(++size1, ++size2);
    }

    void Prepare() {
        // Set initial values before calculating distance
        size_t size1 = GetWidth(), size2 = GetHeight();
        for (size_t index = 1; index < size1; index++) {
            Set(index, 0, index);
        }
        for (size_t index = 1; index < size2; index++) {
            Set(index, index, 0);
        }
    }

    size_t InsertDistance(size_t pos1, size_t pos2) {
        return Get(--pos2, pos1) + 1;
    }

    size_t DeleteDistance(size_t pos1, size_t pos2) {
        return Get(pos2, --pos1) + 1;
    }

    size_t SubstituteDistance(size_t pos1, size_t pos2, const std::basic_string<charT>& str1, \
                              const std::basic_string<charT>& str2) {
        return Get(--pos2, --pos1) + (str1.at(pos1) == str2.at(pos2));
    }

    size_t TransposeDistance(size_t pos1, size_t pos2, const std::basic_string<charT>& str1, \
                             const std::basic_string<charT>& str2) {
        if (str1.at(pos1 - 1) != str2.at(pos2) || str1.at(pos1) != str2.at(pos2 - 1)) {
            throw std::invalid_argument("Transposition not applicable");
        }
        return Get(pos2 - 2, pos1 - 2) + (str1.at(pos1) == str2.at(pos2));
    }
};

#endif // EDITDISTANCEMATRIX_H
