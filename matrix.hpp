#pragma once

#include "matrix_imp.hpp"

template <class T>
inline Matrix<T>::Matrix()
{
    this->dim.x = 0;
    this->dim.y = 0;
}

template <class T>
inline Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> values)
{
    Stack<T> temp{};
    int size = -1;
    for(const auto &_element : values)
    {
        temp.set(_element);

        if(size != -1 && size != temp.size())
        {
            std::cerr << "ERROR:: Matrix dimension is incorrect." << std::endl;
            temp.clear();
            this->element.clear();
            exit(EXIT_FAILURE);
        }

        size = temp.size();
        this->element.push_back(temp);
    }

    this->elemLineToColumn();
    this->setDimension();
}

template <class T>
inline void Matrix<T>::print()
{
    for(int i = 0; i < this->element.size(); i++){std::cout << "------";}

    std::cout << std::endl;

    for(int i = 0; i < this->element.size(); i++)
    {
        for(int j = 0; j < this->element[i].size(); j++)
        {
            std::cout << "[" << this->element[i][j] << "]";
        }

        std::cout << std::endl;
    }

    for(int i = 0; i < this->element.size(); i++){std::cout << "------";}
    std::cout << std::endl;
}

template <class T>
inline dim_s Matrix<T>::getDim()
{
    return this->dim;
}

template <class T>
inline void Matrix<T>::transpose()
{
    if(this->dim.x == 0 && this->dim.y == 0)
    {
        std::cerr << "ERROR:: Can't transpose a void matrix." << std::endl;
        exit(EXIT_FAILURE);
    }

    int x = this->dim.x;
    int y = this->dim.y;
    Matrix<T> temp{};
    Stack<T> st{};

    for(int i = 0; i < x; i++)
    {
        temp.element.push_back(st);

        /*
        for(int j = 0; j < y; j++)
        {
            temp.element[i].push_back(this->element[j][i]);
        }
        */
    }

    for(int i = 0; i < x; i++)
    {
        temp.element[i] = (*this)[':'][i];
    }

    temp.elemLineToColumn();
    temp.setDimension();

    *this = temp;
    
    temp.element.clear();
}

template <class T>
inline void Matrix<T>::operator=(Matrix<T> &_mat)
{   
    _mat.elemLineToColumn();
    _mat.setDimension();

    if(this->element.size() == 0)
        this->element = _mat.element;
    else
    {
        this->element.clear();
        this->element = _mat.element;
        return;
    }

    this->elemLineToColumn();
    this->setDimension();
}

template <class T>
inline void Matrix<T>::operator=(const std::initializer_list<std::initializer_list<T>> &_mat)
{
    Matrix<T> m{_mat};
    if(this->element.size() == 0)
        this->element = m;
    else
    {
        std::cout << "en cours de developpement" << std::endl;
        return;
    }

    this->elemLineToColumn();
    this->setDimension();
}

template <class T>
inline Stack<T> &Matrix<T>::operator[](int index)
{
    if(this->dim.x != 0)
        return this->element_line[index];
    else
        return this->element[index];
}

template <class T>
inline Stack<Stack<T>> &Matrix<T>::operator[](char index)
{
    if(index == ':')
        return this->element_column;
    else
        return this->element_column;
}

template <class T>
inline void Matrix<T>::elemLineToColumn()
{
    this->element_column.clear();
    this->element_line.clear();
    Stack<T> temp{};

    for(int i = 0; i < this->element.size(); i++)
    {
        this->element_column.push_back(temp);
        this->element_line.push_back(temp);
        for(int j = 0; j < this->element[i].size(); j++)
        {
            this->element_line[i].clone_back(&(this->element[i][j]));
        }
    }

    for(int i = 0; i < this->element[0].size(); i++)
    {
        this->element_column.push_back(temp);
        this->element_line.push_back(temp);
        for(int j = 0; j < this->element.size(); j++)
        {
            this->element_column[i].clone_back(&(this->element[j][i]));
        }
    }
}

template <class T>
inline void Matrix<T>::setDimension()
{
    if(this->element.size() != 0)
    {
        this->dim.y = this->element.size();
        this->dim.x = this->element[0].size();
    }
    else
    {
        this->dim.x = 0;
        this->dim.y = 0;
    }
}
