#include <iostream>
# define MAX 100

class Robot {
    private:
        int top;
        int stack[MAX];
    public:
    Robot() { 
        top = -1; // Initialize stack as empty
    }
    bool push(int x) {
        if (top >= (MAX - 1)) {
            std::cout << "Stack Overflow! Cannot push " << x << "\n";
            return false;
        } else {
            stack[++top] = x;
            std::cout << x << " pushed into stack\n";
            return true;
        }
    }

    // Remove and return the top element
    int pop() {
        if (top < 0) {
            std::cout << "Stack Underflow! Nothing to pop.\n";
            return 0; // Returning 0 as a default error indicator
        } else {
            int x = stack[top--];
            return x;
        }
    }

    // Return the top element without removing it
    int peek() {
        if (top < 0) {
            std::cout << "Stack is Empty\n";
            return 0;
        } else {
            return stack[top];
        }
    }

    // Check if the stack is empty
    bool isEmpty() {
        return (top < 0);
    }
};