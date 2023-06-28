#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

// Use inheritance from std::vector (choose public/private) as appropriate
template <typename T>
class Stack 
{
public:
    Stack();
    ~Stack();
    bool empty() const;
    size_t size() const;
    void push(const T& item);
    void pop();  // throws std::underflow_error if empty
    const T& top() const; // throws std::underflow_error if empty
    // Add other members only if necessary

private:
    std::vector<T> stack_;
    int topIndex;
};

template <typename T>
Stack<T>::Stack() {
    topIndex = -1;
}

template <typename T>
Stack<T>::~Stack() {

}

template <typename T>
bool Stack<T>::empty() const {
    return (stack_.size() == 0);
}

template <typename T>
size_t Stack<T>::size() const {
    return stack_.size();
}

template <typename T>
void Stack<T>::push(const T& item) {
    stack_.push_back(item);
    topIndex += 1;
}

template <typename T>
void Stack<T>::pop() {
    if (Stack<T>::size() == 0) {
        throw std::underflow_error("Stack is empty");
    }
    else {
        stack_.pop_back();
        topIndex -= 1;
    }
}

template <typename T>
const T& Stack<T>::top() const {
    if (Stack<T>::size() == 0) {
        throw std::underflow_error("Stack is empty");
    }
    else {
        return stack_[topIndex];
    }
}

#endif
