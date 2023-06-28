#include <iostream>
#include <fstream>
#include <functional>
#include "llrec.h"
using namespace std;

/**
 * Reads integers (separated by whitespace) from a file
 * into a linked list.
 *
 * @param[in] filename
 *  The name of the file containing the data to read
 * @return
 *  Pointer to the linked list (or NULL if empty or the
 *  file is invalid)
 */
Node* readList(const char* filename);

/**
 * Prints the integers in a linked list pointed to
 * by head.
 */
void print(Node* head);

/**
 * Deallocates the linked list nodes
 */
void dealloc(Node* head);


Node* readList(const char* filename)
{
    Node* h = NULL;
    ifstream ifile(filename);
    int v;
    if( ! (ifile >> v) ) return h;
    h = new Node(v, NULL);
    Node *t = h;
    while ( ifile >> v ) {
        t->next = new Node(v, NULL);
        t = t->next;
    }
    return h;
}

void print(Node* head)
{
    while(head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void dealloc(Node* head)
{
    Node* temp;
    while(head) {
        temp = head->next;
        delete head;
        head = temp;
    }
}

// -----------------------------------------------
//   Add any helper functions or
//   function object struct declarations
// -----------------------------------------------
struct isEven {
	bool operator()(int x) {
		return x % 2 == 0;
	} 
};

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cout << "Please provide an input file" << endl;
        return 1;
    }

    // -----------------------------------------------
    // Feel free to update any code below this point
    // -----------------------------------------------
    Node* head = readList(argv[1]);
    cout << "Original list: ";
    print(head);
    cout << endl;

    // Test out your linked list code
    cout << "Test 1" << endl;
    cout << "Original List Before: ";
    print(head);
    Node* smallerList;
    Node* largerList;
    llpivot(head, smallerList, largerList, 10);
    cout << "Smaller List: ";
    print(smallerList);
    cout << "Larger List: ";
    print(largerList);
    cout << "Original List After: ";
    if (head == NULL) {
        cout << "empty" << endl;
    }
    cout << endl;
    
    cout << "Test 2" << endl;
    head = readList(argv[1]);
    cout << "Original List Before: ";
    print(head);
		isEven c1;
    Node* filteredList = llfilter(head, c1);
    cout << "Filtered List: ";
    print(filteredList);

    return 0;
}
