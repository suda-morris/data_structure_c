#include <stddef.h>
#include <iostream>

#include "cstack.h"

using namespace std;

int main()
{
    cstack_t *stack = newCStack();
    int index[10] = { 70, 1, 23, 3, 4, 5, 6, 7, 8, 90 };
    for (int i = 0; i < 10; i++) {
        stack->push(stack, index + i);
    }
    cout << "栈顶节点值: " << *(int *) stack->top(stack) << endl;
    while (!stack->is_empty(stack)) {
        cout << *(int *) stack->pop(stack) << " ";
    }
    cout << endl;
    freeCStack(stack);

    return 0;
}
