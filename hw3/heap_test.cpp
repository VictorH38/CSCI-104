#include <iostream>
#include <fstream>
#include "heap.h"

using namespace std;

int main() {
	Heap<int> myHeap;

	myHeap.push(3);
	myHeap.push(2);
	myHeap.push(1);
	cout << "Heap size: " << myHeap.size() << endl;
	cout << "Top item: " << myHeap.top() << endl;

	myHeap.pop();
	myHeap.pop();
	cout << "Heap size: " << myHeap.size() << endl;
	cout << "Top item: " << myHeap.top() << endl;

	return 0;
}
