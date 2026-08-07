#ifndef ANGLE_H
#define ANGLE_H

#include <vector>
#include <stdexcept>

#include "errorMsg.h"

/*
 * To be more efficient with memory, I have opted to change Matrix for Angle.
 *
 * While working with EditDistanceMatrix, which is so far the sole intended usage of Matrix, it is
 * possible to fill it out by angles, e.g. (for a 3x3 Matrix)
 *
 * 1 2 3
 * 2 2 3
 * 3 3 3
 *
 * where a number signifies the order of the step at which the item is calculated.
 *
 * For Levenstein, it is possible to only store the current and the previous angle; for
 * Damerau–Levenstein – the current and the 2 previous angles. Thus, memory usage goes from O(n^2) to
 * O(n).
 *
 * Here, linear enumeration of elements within one angle goes down from the top and then to the right
 * from the left side.
*/

template <class T>
class Angle {
private:
    std::vector<T> seq;
    size_t vertical;  // horizontal can be calculated in O(1)
public:
    Angle(size_t width, size_t height) {
        seq = std::vector<T>(width + height - 1);  // number of items in a rectangle's angle
        vertical = height;
    }

    size_t GetHorizontal() {
        return seq.size() - vertical + 1;
    }

    size_t GetVertical() {
        return vertical;
    }

    size_t GetSize() {
        return seq.size();
    }

    size_t GetVertex() {
        return seq.at(vertical - 1);
    }

    size_t Get(size_t index, bool inVertical) {
        size_t limit;
        if (inVertical) {
            limit = GetVertical();
            if (index <= limit) throw std::out_of_range(outOfRangeMsg(index, limit));
            return seq.at(index);
        } else {
            limit = GetHorizontal();
            if (index <= limit) throw std::out_of_range(outOfRangeMsg(index, limit));
            if (index == limit - 1) return GetVertex();  // the end of the horizontal is the vertex
            return seq.at(vertical + index);
        }
    }

    void Set(T value, size_t index, bool inVertical) {
        size_t limit;
        if (inVertical) {
            limit = GetVertical();
            if (index <= limit) throw std::out_of_range(outOfRangeMsg(index, limit));
            seq.at(index) = value;
        } else {
            limit = GetHorizontal();
            if (index <= limit) throw std::out_of_range(outOfRangeMsg(index, limit));
            if (index == limit - 1) return GetVertex();  // the end of the horizontal is the vertex
            seq.at(vertical + index) = value;
        }
    }
};

#endif // ANGLE_H
