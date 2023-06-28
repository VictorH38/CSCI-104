/*
CSCI 104: Homework 1 Problem 1

Use this file to test your split.cpp file.

Create linked lists and split them with your split() function.

You can compile this file like this:
g++ split.cpp test_split.cpp -o test_split
*/

#include "split.h"
#include <cstddef>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
  Node* newNode = new Node(1, NULL);
  Node* head = newNode;
  Node* temp = head;
  for (int i = 2; i < 11; i++) {
    Node* newNode = new Node(i, NULL);
    temp->next = newNode;
    temp = temp->next;
  }

  cout << "List before: ";
  Node* temp2 = head;
  while (temp2 != NULL) {
    cout << temp2->value << " ";
    temp2 = temp2->next;
  }
  cout << endl;

  Node* odds = NULL;
  Node* evens = NULL;
  split(head, odds, evens);

  cout << "List after: ";
  Node* temp3 = head;
  while (temp3 != NULL) {
    cout << temp3->value << " ";
    temp3 = temp3->next;
  }
  cout << endl;

  cout << "Odds: ";
  Node* temp4 = odds;
  while (temp4 != NULL) {
    cout << temp4->value << " ";
    Node* dlt = temp4;
    temp4 = temp4->next;
    delete dlt;
  }
  cout << endl;

  cout << "Evens: ";
  Node* temp5 = evens;
  while (temp5 != NULL) {
    cout << temp5->value << " ";
    Node* dlt = temp5;
    temp5 = temp5->next;
    delete dlt;
  }
  cout << endl;
}