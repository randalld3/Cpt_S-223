/*
* Author:     Randall Dickinson
* Class:      Cpt_S 223
* Date:       9.30.22
* Assignment: MA1
*/
/*
* Attributes:
* 1. Originally, all of queue.h was in a main file instead of its own file. That would be a poor design 
*    feature. It does not make the code easily portable, as shown by the need to create a separate file
*    for this assignment.
* 2. Class functions that call queue::size() could save time by instead comparing with the count variable.
*    This would save time by directly accessing the variable, which is available to member functions.
* 3. More commenting could be used within some of the class functions. For example, in queue::enqueue(), 
*    the line rear = (rear + 1) % capacity is pretty confusing to a reader trying to understand their logic.
* 4. Instead of using namespace std, queue.h should state which specific std's to use so that the file
*    does not need to access more data than what is needed.
* 5. Finally, although the instructions say to put all queue class code in the queue.h file, this too is a 
*    poor design feature. Ideally, all queue member function code should be placed in a cpp file, with just 
*    the class definition with variables and function prototypes placed in the header file.
*/

#include "testQueue.h"

int main(void)
{
    testSize();
    testIsEmpty();
    testIsFull();
    testDequeue();
    testEnqueue();
    testPeek();

    return 0;
}
