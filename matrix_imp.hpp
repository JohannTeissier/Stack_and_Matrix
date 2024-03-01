#pragma once

#include <initializer_list>

#include "stack.hpp"

struct dim_s
{
    int x;
    int y;
};

template <class T>
class Matrix
{
    public :

        Matrix();
        Matrix(std::initializer_list<std::initializer_list<T>> values);

        void print();
        dim_s getDim();
        void transpose();

        void operator=(Matrix<T> &_mat);
        void operator=(const std::initializer_list<std::initializer_list<T>> &_mat);
        Stack<T> &operator[](int index);
        Stack<Stack<T>> &operator[](char index);

    private :

    void elemLineToColumn();
    void setDimension();

    dim_s dim;
    
    Stack<Stack<T>> element{};
    Stack<Stack<T>> element_column{};
    Stack<Stack<T>> element_line{};
};
