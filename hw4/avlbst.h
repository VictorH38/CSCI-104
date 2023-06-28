#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void rotateLeft (AVLNode<Key, Value>* current);
    void rotateRight (AVLNode<Key, Value>* current);
    void insertFix (AVLNode<Key, Value>* parent, AVLNode<Key, Value>* child);
    void removeFix (AVLNode<Key, Value>* current, int8_t diff);
		AVLNode<Key, Value>* predecessor(AVLNode<Key, Value>* current);
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
    newNode->setBalance(0);

    if (this->root_ == NULL) {
        this->root_ = newNode;
    }
    else {
        AVLNode<Key, Value>* temp = static_cast<AVLNode<Key,Value>*>(this->root_);
				bool update = true;

        while (temp) {
            if (newNode->getKey() == temp->getKey()) {
                nodeSwap(newNode, temp);
                delete temp;
								update = false;
                break;
            }
            else if (newNode->getKey() < temp->getKey()) {
                if (temp->getLeft() == NULL) {
                    temp->setLeft(newNode);
                    newNode->setParent(temp);
                    break;
                }

                temp = temp->getLeft();
            }
            else if (newNode->getKey() > temp->getKey()) {
                if (temp->getRight() == NULL) {
                    temp->setRight(newNode);
                    newNode->setParent(temp);
                    break;
                }

                temp = temp->getRight();
            }
        }

				if (update){
						AVLNode<Key, Value>* parent = newNode->getParent();
						if (parent->getBalance() == -1 || parent->getBalance() == 1) {
								parent->setBalance(0);
						}
						else if (parent->getBalance() == 0) {
								if (parent->getLeft() == newNode) {
										parent->updateBalance(-1);
								}
								else if (parent->getRight() == newNode) {
										parent->updateBalance(1);
								}

								insertFix(parent, newNode);
						}
				}
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft (AVLNode<Key, Value>* current)
{
		AVLNode<Key, Value>* child = current->getRight();
		AVLNode<Key, Value>* parent = current->getParent();

    child->setParent(current->getParent());
    if (parent == NULL) {
				this->root_ = child;
		}
		else {
				if (parent->getLeft() == current) {
						parent->setLeft(child);
				}
				else {
						parent->setRight(child);
				}
		}

		current->setParent(child);
		current->setRight(child->getLeft());
		if (child->getLeft()) {
				child->getLeft()->setParent(current);
		}

		child->setLeft(current);
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight (AVLNode<Key, Value>* current)
{
    AVLNode<Key, Value>* child = current->getLeft();
		AVLNode<Key, Value>* parent = current->getParent();

    child->setParent(current->getParent());
    if (parent == NULL) {
				this->root_ = child;
		}
		else {
				if (parent->getLeft() == current) {
						parent->setLeft(child);
				}
				else {
						parent->setRight(child);
				}
		}

		current->setParent(child);
		current->setLeft(child->getRight());
		if (child->getRight()) {
				child->getRight()->setParent(current);
		}

		child->setRight(current);
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix (AVLNode<Key, Value>* parent, AVLNode<Key, Value>* child)
{
    AVLNode<Key, Value>* grand = parent->getParent();
    if (parent == NULL || grand == NULL) {
        return;
    }

    if (grand->getLeft() == parent) {
        grand->updateBalance(-1);

        if (grand->getBalance() == 0) {
            return;
        }
        else if (grand->getBalance() == -1) {
            insertFix(grand, parent);
        }
        else if (grand->getBalance() == -2) {
            if (parent->getLeft() == child) {
                rotateRight(grand);
                parent->setBalance(0);
                grand->setBalance(0);
            }
            else if (parent->getRight() == child) {
                rotateLeft(parent);
                rotateRight(grand);

                if (child->getBalance() == -1) {
                    parent->setBalance(0);
                    grand->setBalance(1);
                    child->setBalance(0);
                }
                else if (child->getBalance() == 0) {
                    parent->setBalance(0);
                    grand->setBalance(0);
                    child->setBalance(0);
                }
                else if (child->getBalance() == 1) {
                    parent->setBalance(-1);
                    grand->setBalance(0);
                    child->setBalance(0);
                }
            }
        }
    }
    else if (grand->getRight() == parent) {
        grand->updateBalance(1);

        if (grand->getBalance() == 0) {
            return;
        }
        else if (grand->getBalance() == 1) {
            insertFix(grand, parent);
        }
        else if (grand->getBalance() == 2) {
            if (parent->getRight() == child) {
                rotateLeft(grand);
                parent->setBalance(0);
                grand->setBalance(0);
            }
            else if (parent->getLeft() == child) {
                rotateRight(parent);
                rotateLeft(grand);

                if (child->getBalance() == 1) {
                    parent->setBalance(0);
                    grand->setBalance(-1);
                    child->setBalance(0);
                }
                else if (child->getBalance() == 0) {
                    parent->setBalance(0);
                    grand->setBalance(0);
                    child->setBalance(0);
                }
                else if (child->getBalance() == -1) {
                    parent->setBalance(1);
                    grand->setBalance(0);
                    child->setBalance(0);
                }
            }
        }
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    if (this->root_ == NULL) {
        return;
    }

    if (this->internalFind(key) != NULL) {
        AVLNode<Key, Value>* removeNode = static_cast<AVLNode<Key,Value>*>(this->internalFind(key));

        if (removeNode->getLeft() && removeNode->getRight()) {
            nodeSwap(removeNode, predecessor(removeNode));
        }

        AVLNode<Key, Value>* par = removeNode->getParent();
        int8_t diff = 0;
				if (par != NULL){
						if (par->getLeft() == removeNode) {
								diff = 1;
						}
						else {
								diff = -1;
						}
				}

        if (removeNode->getLeft()) {
            removeNode->getLeft()->setParent(par);

            if (removeNode == this->root_) {
                this->root_ = removeNode->getLeft();

                if (removeNode->getRight()) {
                    this->root_->setRight(removeNode->getRight());
                    removeNode->getRight()->setParent(this->root_);
                }
            }
            else {
                if (par->getLeft() == removeNode) {
                    par->setLeft(removeNode->getLeft());
                }
                else {
                    par->setRight(removeNode->getLeft());
                }
            }
        }
        else if (removeNode->getRight()) {
            removeNode->getRight()->setParent(par);

            if (removeNode == this->root_) {
                this->root_ = removeNode->getRight();

                if (removeNode->getLeft()) {
                    this->root_->setLeft(removeNode->getLeft());
                    removeNode->getLeft()->setParent(this->root_);
                }
            }
            else {
                if (par->getLeft() == removeNode) {
                    par->setLeft(removeNode->getRight());
                }
                else {
                    par->setRight(removeNode->getRight());
                }
            }
        }
        else {
            if (removeNode == this->root_) {
                this->root_ = NULL;
            }
            else {
                if (par->getLeft() == removeNode) {
                    par->setLeft(NULL);
                }
                else if (par->getRight() == removeNode) {
                    par->setRight(NULL);
                }
            }
        }
        
        delete removeNode;
        removeFix(par, diff);
    }
}

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::predecessor(AVLNode<Key, Value>* current)
{
		if (current == NULL) {
				return NULL;
		}
		
		if (current->getLeft()) {
				AVLNode<Key, Value>* pred = current->getLeft();

				while (pred->getRight() != NULL) {
						pred = pred->getRight();
				}

				return pred;
		}
		else {
				AVLNode<Key, Value>* pred = current;
				AVLNode<Key, Value>* par = pred->getParent();

				while (par != NULL) {
						if (par->getRight() == pred) {
								return par;
						}

						pred = par;
						par = pred->getParent();
				}
		}

		return NULL;
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix (AVLNode<Key, Value>* current, int8_t diff)
{
    if (current == NULL) {
        return;
    }

    AVLNode<Key, Value>* parent = current->getParent();
    int8_t ndiff = 0;
    if (parent != NULL) {
        if (parent->getLeft() == current) {
            ndiff = 1;
        }
        else if (parent->getRight() == current) {
            ndiff = -1;
        }
    }

    if (diff == -1) {
        if (current->getBalance() + diff == -2) {
            AVLNode<Key, Value>* child = current->getLeft();

            if (child->getBalance() == -1) {
                rotateRight(current);
                current->setBalance(0);
                child->setBalance(0);
                removeFix(parent, ndiff);
            }
            else if (child->getBalance() == 0) {
                rotateRight(current);
                current->setBalance(-1);
                child->setBalance(1);
            }
            else if (child->getBalance() == 1) {
                AVLNode<Key, Value>* grandchild = child->getRight();
                rotateLeft(child);
                rotateRight(current);

                if (grandchild->getBalance() == 1) {
                    current->setBalance(0);
                    child->setBalance(-1);
                    grandchild->setBalance(0);
                }
                else if (grandchild->getBalance() == 0) {
                    current->setBalance(0);
                    child->setBalance(0);
                    grandchild->setBalance(0);
                }
                else if (grandchild->getBalance() == -1) {
                    current->setBalance(1);
                    child->setBalance(0);
                    grandchild->setBalance(0);
                }

                removeFix(parent, ndiff);
            }
        }
        else if (current->getBalance() + diff == -1) {
            current->setBalance(-1);
        }
        else if (current->getBalance() + diff == 0) {
            current->setBalance(0);
            removeFix(parent, ndiff);
        }
    }
    else if (diff == 1) {
        if (current->getBalance() + diff == 2) {
            AVLNode<Key, Value>* child = current->getRight();

            if (child->getBalance() == 1) {
                rotateLeft(current);
                current->setBalance(0);
                child->setBalance(0);
                removeFix(parent, ndiff);
            }
            else if (child->getBalance() == 0) {
                rotateLeft(current);
                current->setBalance(1);
                child->setBalance(-1);
            }
            else if (child->getBalance() == -1) {
                AVLNode<Key, Value>* grandchild = child->getLeft();
                rotateRight(child);
                rotateLeft(current);

                if (grandchild->getBalance() == -1) {
                    current->setBalance(0);
                    child->setBalance(1);
                    grandchild->setBalance(0);
                }
                else if (grandchild->getBalance() == 0) {
                    current->setBalance(0);
                    child->setBalance(0);
                    grandchild->setBalance(0);
                }
                else if (grandchild->getBalance() == 1) {
                    current->setBalance(-1);
                    child->setBalance(0);
                    grandchild->setBalance(0);
                }

                removeFix(parent, ndiff);
            }
        }
        else if (current->getBalance() + diff == 1) {
            current->setBalance(1);
        }
        else if (current->getBalance() + diff == 0) {
            current->setBalance(0);
            removeFix(parent, ndiff);
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
