#include <iostream>

#include "cqueue.h"

using namespace std;

int main()
{
    cqueue_t *queue = newCQueue();
    int index[10] = { 70, 1, 23, 3, 4, 5, 6, 7, 8, 90 };
    for (int i = 0; i < 10; i++) {
        queue->push(queue, index + i);
    }
    cout << "队首节点值: " << *(int *) queue->top(queue) << endl;
    while (!queue->is_empty(queue)) {
        cout << *(int *) queue->pop(queue) << " ";
    }
    cout << endl;
    freeCQueue(queue);

    return 0;
}
