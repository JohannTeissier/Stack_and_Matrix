#pragma once

#include "stack_imp.hpp"

template <class T>
inline Element<T>::Element(const T &value, Element *pnext, Element* pback) : pnext_(pnext), pback_(pback)
{
    this->value_ = value;
    this->copy_value = nullptr;
}

template <class T>
inline Element<T>::Element(T *value, Element<T> *pnext, Element<T> *pback) : pnext_(pnext), pback_(pback)
{
    this->copy_value = value;
}

template <class T>
inline Element<T> *Element<T>::getNextElement()
{
    return this->pnext_;
}

template <class T>
inline Element<T> *Element<T>::getPreviousElement()
{
    return this->pback_;
}

template <class T>
inline void Element<T>::setNextElement(Element<T> *pnext)
{
    this->pnext_ = pnext;
}

template <class T>
inline void Element<T>::setPreviousElement(Element<T> *pback)
{
    this->pback_ = pback;
}

template <class T>
inline T &Element<T>::getValue()
{
    return this->value_;
}

template <class T>
inline T *Element<T>::getCopyValue()
{
    return this->copy_value;
}

template <class T>
inline void Element<T>::setCopyValue(T *value)
{
    this->copy_value = value;
}

template <class T>
inline Stack<T>::Stack()
{
    this->first = nullptr;
    this->last = nullptr;
    this->cardinal = 0;
}

template <class T>
inline Stack<T>::Stack(const Stack<T> &st)
{
    this->first = nullptr;
    this->last = nullptr;
    this->cardinal = 0;
    *this = st;
}

template <class T>
inline Stack<T>::Stack(std::initializer_list<T> liste)
{
    this->first = nullptr;
    this->last = nullptr;
    this->cardinal = 0;
    for (const auto& elem : liste) 
    {
        this->push_back(elem);
    }
}

template <class T>
inline Stack<T>::~Stack()
{
    this->clear();
}

template <class T>
inline void Stack<T>::push_front(const T &value)
{
    Element<T>* elem = nullptr;
    elem = new Element<T>{value, this->first, nullptr};

    if(elem == nullptr)
    {
        std::cerr << "Erreur allocation dynamique de memoire." << std::endl;
        exit(EXIT_FAILURE);
    }

    if(this->first == nullptr)
    {
        this->first = elem;
        this->last = elem;
    }
    else
    {
        this->first->setPreviousElement(elem);
        this->first = elem;
    }

    this->cardinal++;
}

template <class T>
inline void Stack<T>::push_back(const T &value)
{
    Element<T>* elem = nullptr;
    elem = new Element<T>{value, nullptr, this->last};

    if(elem == nullptr)
    {
        std::cerr << "Erreur allocation dynamique de memoire." << std::endl;
        exit(EXIT_FAILURE);
    }

    if(this->first == nullptr)
    {
        this->first = elem;
        this->last = elem;
    }
    else
    {
        this->last->setNextElement(elem);
        this->last = elem;
    }

    this->cardinal++;
}

template <class T>
inline void Stack<T>::push(const T &value, int index)
{
    if(index > this->cardinal || index < 0)
    {
        std::cout << "ERROR:: index is out of range." << std::endl;
        exit(EXIT_FAILURE);
    }

    if(this->first == nullptr)
    {
        this->push_front(value);
        return;
    }

    if(index == 0)
    {
        this->push_front(value);
        return;
    }

    if(index == this->cardinal)
    {
        this->push_back(value);
        return;
    }

    if(index < this->cardinal - index)
    {
        Element<T> *temp = this->first;
        Element<T>* elem = nullptr;

        for(int i = 0; i < index; i++)
            temp = temp->getNextElement();

        elem = new Element<T>{value, temp, temp->getPreviousElement()};

        if (elem == nullptr)
        {
            std::cerr << "Erreur allocation dynamique de memoire." << std::endl;
            exit(EXIT_FAILURE);
        }

        temp->getPreviousElement()->setNextElement(elem);
        temp->setPreviousElement(elem);
    }
    else
    {
        Element<T> *temp = this->last;
        Element<T> *elem = nullptr;

        for(int i = 0; i < this->cardinal - index - 1; i++)
            temp = temp->getPreviousElement();

        elem = new Element<T>{value, temp, temp->getPreviousElement()};

        if (elem == nullptr)
        {
            std::cerr << "Erreur allocation dynamique de memoire." << std::endl;
            exit(EXIT_FAILURE);
        }

        temp->getPreviousElement()->setNextElement(elem);
        temp->setPreviousElement(elem);
    }

    this->cardinal++;
}

template <class T>
inline void Stack<T>::clone_back(T *value)
{
    Element<T>* elem = nullptr;
    elem = new Element<T>{value, nullptr, this->last};

    if(elem == nullptr)
    {
        std::cerr << "Erreur allocation dynamique de memoire." << std::endl;
        exit(EXIT_FAILURE);
    }

    if(this->first == nullptr)
    {
        this->first = elem;
        this->last = elem;
    }
    else
    {
        this->last->setNextElement(elem);
        this->last = elem;
    }

    this->cardinal++;
}

template <class T>
inline void Stack<T>::clone_front(T *value)
{
    Element<T>* elem = nullptr;
    elem = new Element<T>{value, this->first, nullptr};

    if(elem == nullptr)
    {
        std::cerr << "Erreur allocation dynamique de memoire." << std::endl;
        exit(EXIT_FAILURE);
    }

    if(this->first == nullptr)
    {
        this->first = elem;
        this->last = elem;
    }
    else
    {
        this->first->setPreviousElement(elem);
        this->first = elem;
    }

    this->cardinal++;
}

template <class T>
inline void Stack<T>::pop_front()
{
    if(this->first == nullptr)
        return;

    Element<T>* temp = this->first;
    this->first = this->first->getNextElement();

    if(this->first != nullptr)
        this->first->setPreviousElement(nullptr);
    else
        this->last = nullptr;

    delete temp;

    this->cardinal--;
}

template <class T>
inline void Stack<T>::pop_back()
{
    if(this->last == nullptr)
        return;

    Element<T>* temp = this->last;
    this->last = this->last->getPreviousElement();
    if(this->last != nullptr)
        this->last->setNextElement(nullptr);
    else
        this->first = nullptr;

    delete temp;

    this->cardinal--;
}

template <class T>
inline void Stack<T>::erase(int index)
{
    if(index >= this->cardinal || index < 0)
    {
        std::cout << "ERROR:: index is out of range." << std::endl;
        exit(EXIT_FAILURE);
    }

    if(this->first == nullptr && this->last == nullptr)
        return;

    if(this->first == this->last)
    {
        this->clear();
        return;
    }

    if(index == 0)
    {
        this->pop_front();
        return;
    }

    if(index == this->cardinal - 1)
    {
        this->pop_back();
        return;
    }

    if(index < this->cardinal - index)
    {
        Element<T> *temp = this->first;

        for(int i = 0; i < index; i++)
            temp = temp->getNextElement();

        if(temp->getPreviousElement() != nullptr)
            temp->getPreviousElement()->setNextElement(temp->getNextElement());
        if(temp->getNextElement() != nullptr)
            temp->getNextElement()->setPreviousElement(temp->getPreviousElement());

        delete temp;
    }
    else
    {
        Element<T> *temp = this->last;

        for(int i = 0; i < this->cardinal - index - 1; i++)
            temp = temp->getPreviousElement();

        if(temp->getPreviousElement() != nullptr)
            temp->getPreviousElement()->setNextElement(temp->getNextElement());
        if(temp->getNextElement() != nullptr)
            temp->getNextElement()->setPreviousElement(temp->getPreviousElement());

        delete temp;
    }

    this->cardinal--;
}

template <class T>
inline void Stack<T>::erase(std::initializer_list<int> index)
{
    int value, place;
    Stack<int> tab{index};
    for(int i = 0; i < tab.size()-1; i++)
    {
        if (tab[i] >= this->cardinal || tab[i] < 0)
        {
            std::cout << "ERROR:: Index is out of range." << std::endl;
            exit(EXIT_FAILURE);
        }

        for(int j = i+1; j < tab.size(); j++)
        {
            if(tab[i] == tab[j])
            {
                std::cerr << "ERROR:: Index already erase from the stack." << std::endl;
                exit(EXIT_FAILURE);
            }
        }
    }

    for (int i = 0; i < tab.size() - 1; i++)
    {
        value = tab[i];
        for (int j = i + 1; j < tab.size(); j++)
        {
            if (value < tab[j])
            {
                value = tab[j];
                place = j;
            }
        }

        if (value != tab[i])
        {
            tab.push(tab[i], place);
            tab.erase(place + 1);
            tab.erase(i);
            tab.push(value, i);
        }

        this->erase(tab[i]);
    }

    this->erase(tab[tab.size()-1]);
    tab.clear();
}

template <class T>
inline void Stack<T>::clear()
{
    while(this->first != nullptr)
        this->pop_front();
}

template <class T>
inline void Stack<T>::print()
{
    std::cout << std::endl;

    Element<T>* temp = this->first;
    while(temp != nullptr)
    {
        if(temp->getCopyValue() == nullptr)
            std::cout << "[" << temp->getValue() << "]" << std::flush;
        else
            std::cout << "[" << *(temp->getCopyValue()) << "]" << std::flush;
        
        temp = temp->getNextElement();
    }

    std::cout << std::endl;
}

template <class T>
inline int Stack<T>::size()
{
    return this->cardinal;
}

template <class T>
inline void Stack<T>::set(std::initializer_list<T> values)
{
    this->clear();

    for (const auto& elem : values) 
    {
        this->push_back(elem);
    }
}

template <class T>
inline void Stack<T>::operator=(const Stack<T> &_st)
{
    Element<T>* temp = _st.last;
    int i = 0;
    
    if(this->cardinal == 0)
        i = -1;
    else if(this->cardinal != _st.cardinal)
    {
        std::cout << "ERROR:: Dimension are not compatible" << std::endl;
        return;
    }

    while(temp != nullptr)
    {   
        if(i == -1)
        {
            this->push_front(temp->getValue());
        }
        else
        {
            if(this->first->getCopyValue() != nullptr)
            {
                if(temp->getCopyValue() != nullptr)
                    (*this)[i] = *(temp->getCopyValue());
                else
                    (*this)[i] = temp->getValue();
            }
            else
            {
                this->erase(i);
                this->push_front(temp->getValue());
            }
        }

        temp = temp->getPreviousElement();
        if(i != -1)
            i++;
    }
}

template <class T>
inline T &Stack<T>::operator[](int index)
{
    if(index >= this->cardinal || index < 0)
    {
        std::cerr << "ERROR:: index is out of range." << std::endl;
        exit(EXIT_FAILURE);
    }

    if(index < this->cardinal - index)
    {
        Element<T> *temp = this->first;

        for (int i = 0; i < index; i++)
            temp = temp->getNextElement();

        if(temp->getCopyValue() == nullptr)
            return (temp->getValue());
        else
            return *(temp->getCopyValue());
    }
    else
    {
        Element<T> *temp = this->last;

        for(int i = 0; i < this->cardinal - index - 1; i++)
            temp = temp->getPreviousElement();

        if(temp->getCopyValue() == nullptr)
            return (temp->getValue());
        else
            return *(temp->getCopyValue());
    }
}
