#include "stack.hpp"

template <class T>
inline Element<T>::Element(const T &value, Element *pnext, Element* pback) : pnext_(pnext), pback_(pback)
{
    this->value_ = value;
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
    if(index > this->cardinal || index < 0)
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
        std::cout << "[" << temp->getValue() << "]" << std::flush;
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
inline void Stack<T>::operator=(const Stack<T> &_st)
{
    Element<T>* temp = _st.last;

    while(temp != nullptr)
    {
        this->push_front(temp->getValue());
        temp = temp->getPreviousElement();
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

        return (temp->getValue());
    }
    else
    {
        Element<T> *temp = this->last;

        for(int i = 0; i < this->cardinal - index - 1; i++)
            temp = temp->getPreviousElement();

        return (temp->getValue());
    }
}
