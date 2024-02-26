#include "stack_imp.hpp"

int main()
{
    Stack<Stack<float>> matrix{};
    Stack<float> sub_matrix{};

    sub_matrix.push_back(5);
    sub_matrix.push_back(5);
    sub_matrix.push_back(5);
    sub_matrix.push_back(5);

    matrix.push_back(sub_matrix);
    matrix.push_back(sub_matrix);
    matrix.push_back(sub_matrix);
    matrix.push_back(sub_matrix);

    matrix.print();
}