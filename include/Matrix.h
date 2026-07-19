#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

template <class T>
class Matrix {
private:
    std::vector<std::vector<T>> data;
public:
    Matrix(size_t width, size_t height, T fill = T()) {
        for (size_t index = 0; index < height; index++) {
            data.at(index) = std::vector<T>(width, fill);
        }
    }

    Matrix() {
        data = std::vector<T>(0);
    }

    size_t GetWidth() const {
        if (data.empty()) return 0;
        return data.at(0).size();
    }

    size_t GetHeight() const {
        return data.size();
    }

    T Get(size_t row, size_t column) const {
        return data.at(row).at(column);
    }

    void Set(T value, size_t row, size_t column) {
        data.at(row).at(column) = value;
    }

    void AddRow(T fill = T()) {
        std::vector<T> newRow(GetWidth(), fill);
        data.push_back(newRow);
    }

    void AddColumn(T fill = T()) {
        for (size_t row = 0; row < GetHeight(); row++) {
            data.at(row).push_back(fill);
        }
    }

    Matrix<T> operator=(const Matrix<T>& other) {
        if (this != &other) {
            data = other.data;
        }
    }
};

#endif // MATRIX_H
