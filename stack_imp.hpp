#pragma once

#include <iostream>
#include <fstream>
#include <initializer_list>

template <class T>
class Element
{
    public :

    Element(const T &value, Element<T>* pnext, Element<T>* pback);
    Element(T *value, Element<T>* pnext, Element<T>* pback);
    Element<T> *getNextElement();
    Element<T> *getPreviousElement();
    void setNextElement(Element<T>* pnext);
    void setPreviousElement(Element<T>* pback);
    T &getValue();
    T *getCopyValue();
    void setCopyValue(T *value);

    private :

    T value_{};
    T *copy_value;
    Element<T> *pnext_;
    Element<T> *pback_;
};

template <class T>
class Stack
{
    public :

        Stack();
        Stack(const Stack<T> &st);
        Stack(std::initializer_list<T> liste);
        ~Stack();

        void push_front(const T &value);
        void push_back(const T &value);
        void push(const T &value, int index);
        void clone_back(T *value);
        void clone_front(T *value);
        void pop_front();
        void pop_back();
        void erase(int index);
        void erase(std::initializer_list<int> index);
        void clear();
        void print();
        int size();
        void set(std::initializer_list<T> values);

        void operator=(const Stack<T> &_st);
        T &operator[](int index);

    private :

        Element<T> *first;
        Element<T> *last;
        int cardinal;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Stack<U>& v);
};

template <typename U>
inline std::ostream &operator<<(std::ostream &os, const Stack<U> &v)
{
    Element<U>* temp = v.first;

    os << "";

    while(temp != nullptr)
    {
        if(temp->getCopyValue() == nullptr)
            os << "[" << temp->getValue() << "]";
        else
            os << "[" << *(temp->getCopyValue()) << "]";

        temp = temp->getNextElement();
    }

    os << "\n";

    return os;
}
