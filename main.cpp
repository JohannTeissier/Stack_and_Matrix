#include "matrix.hpp"
#include "stack.hpp"

int main()
{
    Matrix<int> m1 = {{1,2,3},{4,5,6}};
    Matrix<int> m2 = {{},{},{}};
    m1.print();
    
    m2[0] = m1[':'][0];
    m2[1] = m1[':'][1];
    m2[2] = m1[':'][2];

    m1 = m2;

    m2.print();
    m1.print();

    return 0;
}