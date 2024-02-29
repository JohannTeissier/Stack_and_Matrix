#pragma once

#include "matrix_imp.hpp"

template <class T>
inline Matrix<T>::Matrix()
{
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
inline void Matrix<T>::operator=(const Matrix<T> &_mat)
{   
    if(this->element.size() == 0)
        this->element = _mat.element;
    else
    {
        std::cout << "en cours de developpement" << std::endl;
        return;
    }

    this->elemLineToColumn();
}

template <class T>
inline Stack<T> &Matrix<T>::operator[](int index)
{
    return this->element_line[index];
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
    Stack<T> temp{};

    for(int i = 0; i < this->element.size(); i++)
    {
        this->element_column.push_back(temp);
        this->element_line.push_back(temp);
        for(int j = 0; j < this->element[i].size(); j++)
        {
            //this->element_column[i].clone_back(&(this->element[j][i]));
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
            //this->element_line[i].clone_back(&(this->element[i][j]));
        }
    }
}
