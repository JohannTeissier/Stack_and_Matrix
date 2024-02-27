#include "stack_imp.hpp"

int main()
{
    Stack<Stack<int>> st{Stack<int>{{1,2,3}},Stack<int>{{4,5,6}},Stack<int>{{7,8,9}}};

    st.print();

    return 0;
}