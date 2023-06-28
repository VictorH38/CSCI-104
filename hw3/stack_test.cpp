#include <iostream>
#include <fstream>
#include <functional>
#include "stack.h"

using namespace std;

int main() {
	Stack<int> myStack;

	myStack.push(1);
	myStack.push(2);
	myStack.push(3);
	cout << "Stack size: " << myStack.size() << endl;
	cout << "Top item: " << myStack.top() << endl;

	myStack.pop();
	myStack.pop();
	cout << "Stack size: " << myStack.size() << endl;
	cout << "Top item: " << myStack.top() << endl;

	return 0;
}
