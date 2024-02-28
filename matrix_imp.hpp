#pragma once

#include <initializer_list>

#include "stack.hpp"

template <class T>
class Matrix
{
    public :

        Matrix();
        Matrix(std::initializer_list<std::initializer_list<T>> values);

        void print();

        void operator=(const Matrix<T> &_mat);
        Stack<T> &operator[](int index);
        Stack<Stack<T>> &operator[](char index);

    private :

    void elemLineToColumn();

    Stack<Stack<T>> element{};
    Stack<Stack<T>> element_column{};
    Stack<Stack<T>> element_line{};
};
