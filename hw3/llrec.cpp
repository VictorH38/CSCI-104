#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************
void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot) {
	if (head != NULL) {
		if (head->val <= pivot) {
			smaller = head;
			head = head->next;
			llpivot(head, smaller->next, larger, pivot);
		}
		else {
			larger = head;
			head = head->next;
			llpivot(head, smaller, larger->next, pivot);
		}
	}
	else {
		smaller = head;
		larger = head;
	}
}
