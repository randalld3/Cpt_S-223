#include "queue.h"

/* Test ID: testSize
 * Unit: queue::size()
 * Description: Test to determine if queue::size() returns correct size. This should
 *              return 3 if correct.
 * Test Steps:
 *     1. Construct a queue object of size 3
 *     2. Invoke queue::enqueue() three times, inserting new elements in queue
 *     3. Invoke queue::size()
 *     4. Conditionally evaluate the value returned by queue::size()
 * Test Data: size = 3
 * Precondition: queue object is size 0
 * Postcondition: queue object is size 3
 * Expected Result: queue is of size 3; Queue is of size 3 is printed
 * Actual Result: Queue is of size 4 is printed
 * Status: Failed
 */
void testSize(void)
{
#define PASS 3

    queue testQueue(3);
    testQueue.enqueue(1);
    testQueue.enqueue(2);
    testQueue.enqueue(3);

    cout << "Queue is of size " << testQueue.size() << endl;
}

/* Test ID: testIsEmpty
 * Unit: queue::isEmpty()
 * Description: Test to determine if queue::isEmpty() correctly identifies empty queue. queue::isEmpty() 
 *              is tested on an empty queue, and pass printed if function identifies empty queue correctly,
 *              fail otherwise.
 * Test Steps:
 *     1. Construct an empty queue
 *     2. Invoke queue::isEmpty()
 *     3. Result of queue::isEmpty() is printed
 * Test Data: size = 0
 * Precondition: queue object is size 0
 * Postcondition: queue object is still size 0
 * Expected Result: Queue is of size 0; queue::isEmpty() passed! is printed
 * Actual Result: Queue is not of size 0; queue::isEmpty() failed! is printed
 * Status: Failed
 */
void testIsEmpty(void)
{
    queue testQueue;

    if (testQueue.isEmpty())
        cout << "queue::isEmpty() passed!" << endl;
    else
        cout << "queue::isEmpty() failed!" << endl;
}

/* Test ID: testIsFull
 * Unit: queue::isFull()
 * Description: Test to determine if queue::isEmpty() correctly identifies empty queue. queue::isEmpty()
 *              is tested on an empty queue, and pass printed if function identifies empty queue correctly,
 *              fail otherwise.
 * Test Steps:
 *     1. Construct a queue of capacity 1
 *     2. Invoke queue::enqueue(int) to fill the queue to capacity
 *     3. Invoke queue::isFull() to see if function identifies full queue
 *     4. Result of funtion is printed
 * Test Data: size = 1
 * Precondition: queue object is size 1
 * Postcondition: queue object is still size 1
 * Expected Result: Queue is of size 1; queue::isFull() passed! is printed
 * Actual Result: Queue is correctly identified as full; queue::isFull() passed! is printed
 * Status: Passed
 */
void testIsFull(void)
{
    queue testQueue(1);
    testQueue.enqueue(42);
    if (testQueue.isFull())
        cout << "queue::isFull() passed!" << endl;
    else
        cout << "queue::isFull() failed!" << endl;
}

/* Test ID: testDequeue
 * Unit: queue::dequeue()
 * Description: Tests to determine if queue::dequeue() will corretly report an empty queue when
 *              invoked on an empty queue and if dequeue will dequeue a non-empty queue.
 * Test Steps:
 *     1. Construct a queue of capacity 1
 *     2. Invoke queue::dequeue()
 *     3. Underflow should be reported
 *     4. Invoke queue::enqueue(int)
 *     5. Invoke queue::dequeue()
 *     6. Element to be removed should be printed
 * Test Data: size = 1
 * Precondition: queue object is size 0 at first call, and size 1 at second
 * Postcondition: queue object is size 0 after both calls
 * Expected Result: First test should report underflow; Second test should print item dequeued
 * Actual Result: First test incorrectly reported 0 to be removed from queue; 
 *                Second test reported correct element removed from queue
 * Status: First test failed - dequeue did not identify empty queue; Second test passed
 */
void testDequeue(void)
{
    queue testQueue(1);

    cout << "Testing queue::dequeue() with empty queue" << endl;
    testQueue.dequeue();

    cout << "Testing queue::dequeue() with element in queue" << endl;
    testQueue.enqueue(42);
    testQueue.dequeue();
}

/* Test ID: testEequeue
 * Unit: queue::enqueue()
 * Description: Tests to determine if queue::enqueue() will allow elements to be added to a queue below
 *              capacity and whether it will allow elements to be added to a queue at capacity.
 * Test Steps:
 *     1. Construct a queue of capacity 1
 *     2. Invoke queue::enqueue(int)
 *     3. Specified int should be reported to be inserted
 *     4. Invoke queue::enqueue(int)
 *     5. Overflow should be reported
 * Test Data: size = 1
 * Precondition: queue object is size 0 at first call, size 1 at second call
 * Postcondition: queue object is size 1
 * Expected Result: First test should report item inserted. Second test should report overflow
 * Actual Result: First test reported correct item to be inserted, but inserted at wrong location; 
                  Second test correctly reported overflow
 * Status: First test failed due to wrong insertion location; Second test passed
 */
void testEnqueue(void)
{
    queue testQueue(1);

    cout << "Testing queue::enqueue() with room in queue" << endl;
    testQueue.enqueue(42);

    cout << "Testing queue::enqueue() with no room in queue" << endl;
    testQueue.enqueue(77);

}

/* Test ID: testPeek
 * Unit: queue::peek()
 * Description: Tests to determine if queue::peek() will corretly report underflow with an empty queue,
 *              otherwise report the next item in the queue.
 * Test Steps:
 *     1. Construct an empty queue of capacity 3
 *     2. Invoke queue::peek()
 *     3. Underflow should be reported
 *     4. Invoke queue::enqueue(int) three times
 *     5. Invoke queue::peek()
 *     6. First element to be inserted into queue should be printed
 * Test Data: size = 3
 * Precondition: queue object is size 0 on first call, size 3 on second call
 * Postcondition: queue object is the same size after each call as it was before each call
 * Expected Result: First test should report underflow; Second test should print next item in queue.
 * Actual Result: First test did not report underflow;
 *                Second test reported middle element in queue;
 * Status: First test failed - peek() did not identify empty queue; Second test failed - peek() did not
 *         show correct element in queue
 */
void testPeek(void)
{
    queue testQueue(3);

    cout << "Testing queue::peek() with empty queue" << endl;
    cout << testQueue.peek() << endl;

    testQueue.enqueue(77);
    testQueue.enqueue(3);
    testQueue.enqueue(42);

    cout << "Testing queue::peek() with elements in queue" << endl;
    cout << testQueue.peek() << endl;
}
