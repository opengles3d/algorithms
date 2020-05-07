#include <iostream>
#include <stack>

class MinStack {
public:
    void push(int a) {
        main_stack.push(a);
        if(min_stack.empty() || a <= min_stack.top()) {
            min_stack.push(a);
        }
    }

    int pop() {
        if(!main_stack.empty()) {
            int at = main_stack.top();
            int min = min_stack.top();
            if(at == min) {
                min_stack.pop();
            }
            main_stack.pop();
            return at;
        } else {
            return 0;
        }
    }

    bool empty() {
        return main_stack.empty();
    }

    int getMin() {
        if(!min_stack.empty()) {
            return min_stack.top();
        } else {
            return 0;
        }
        
    }
private:
    std::stack<int> main_stack;
    std::stack<int> min_stack;
};

int main(int argc, char* argv[]) {
    MinStack ms;
    ms.push(4);
    ms.push(5);
    ms.push(6);
    ms.push(3);
    ms.push(7);

    std::cout << "min is: " << ms.getMin() << std::endl;
    std::cout << "Pop :" << ms.pop() << std::endl;

    std::cout << "min is: " << ms.getMin() << std::endl;
    std::cout << "Pop :" << ms.pop() << std::endl;

    std::cout << "min is: " << ms.getMin() << std::endl;
    std::cout << "Pop :" << ms.pop() << std::endl;

    std::cout << "min is: " << ms.getMin() << std::endl;
    std::cout << "Pop :" << ms.pop() << std::endl;

    std::cout << "min is: " << ms.getMin() << std::endl;
    std::cout << "Pop :" << ms.pop() << std::endl;

    return 0;
}