#include "matrix.hpp"
#include "stack.hpp"

int main()
{
    Matrix<char> m1{{{'j','o','h'},{'n','a','d'},{'j','o','h'},{'n','a','d'},{'j','o','h'},{'n','a','d'}}};
    Matrix<char> m2{{{'H','H','H','H','H','H'}}};

    m1[':'][1] = m2[0];
    m1.print();

    return 0;
}