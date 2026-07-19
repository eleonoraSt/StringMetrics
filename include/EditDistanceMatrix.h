#ifndef EDITDISTANCEMATRIX_H
#define EDITDISTANCEMATRIX_H

#include <string>
#include <stdexcept>

#include "Matrix.h"

template <class charT>
class EditDistanceMatrix: private Matrix<size_t> {
public:
    EditDistanceMatrix(size_t width, size_t height) {
        Matrix<size_t>(width, height);
    }

    size_t InsertDistance(size_t oldPos, size_t newPos) {
        return Get(--oldPos, newPos);
    }

    size_t DeleteDistance(size_t oldPos, size_t newPos) {
        return Get(oldPos, --newPos);
    }

    size_t SubstituteDistance(size_t oldPos, size_t newPos, std::basic_string<charT>& oldStr, \
                              std::basic_string<charT>& newStr) {
        return Get(--oldPos, --newPos) + (oldStr.at(oldPos) == newStr.at(newPos));
    }

    size_t TransposeDistance(size_t oldPos, size_t newPos, std::basic_string<charT>& oldStr, \
                             std::basic_string<charT>& newStr) {
        if (oldStr.at(oldPos - 1) != newStr.at(newPos) || oldStr.at(oldPos) != newStr.at(newPos - 1)) {
            throw std::invalid_argument("Transposition not applicable");
        }
        return Get(oldPos - 2, newPos - 2) + (oldStr.at(oldPos) == newStr.at(newPos));
    }
};

#endif // EDITDISTANCEMATRIX_H
