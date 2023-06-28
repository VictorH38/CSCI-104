#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

#include <iostream>

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
void ULListStr::push_back(const std::string& val){
  if(tail_ == NULL) {
    Item* newItem = new Item;
    newItem->val[0] = val;
    newItem->last = 1;
    head_ = newItem;
    tail_ = newItem;
  }
  else {
    if (tail_->last == ARRSIZE) {
      Item* newItem = new Item;
      newItem->val[0] = val;
      newItem->last = 1;
      newItem->prev = tail_;
      tail_->next = newItem;
      tail_ = newItem;
    }
    else {
      tail_->val[tail_->last] = val;
      tail_->last += 1;
    }
  }

  size_ += 1;
}

void ULListStr::pop_back() {
  if (tail_->last - tail_->first == 1) {
    if (head_ == tail_) {
      Item* temp = tail_;
      head_ = tail_ = NULL;
      delete temp;
    }
    else {
      Item* temp = tail_;
      tail_ = tail_->prev;
      tail_->next = NULL;
      delete temp;
    }
  }
  else {
    tail_->last -= 1;
  }

  size_ -= 1;
}

void ULListStr::push_front(const std::string& val) {
  if(head_ == NULL) {
    Item* newItem = new Item;
    newItem->val[0] = val;
    newItem->last = 1;
    head_ = newItem;
    tail_ = newItem;
  }
  else {
    if (head_->first == 0) {
      Item* newItem = new Item;
      newItem->val[ARRSIZE - 1] = val;
      newItem->first = ARRSIZE - 1;
      newItem->last = ARRSIZE;
      newItem->next = head_;
      head_->prev = newItem;
      head_ = newItem;
    }
    else {
      head_->val[head_->first - 1] = val;
      head_->first -= 1;
    }
  }

  size_ += 1;
}

void ULListStr::pop_front() {
  if (head_->last - head_->first == 1) {
    if (head_ == tail_) {
      Item* temp = head_;
      head_ = tail_ = NULL;
      delete temp;
    }
    else {
      Item* temp = head_;
      head_ = head_->next;
      head_->prev = NULL;
      delete temp;
    }
  }
  else {
    head_->first += 1;
  }

  size_ -= 1;
}

std::string const & ULListStr::back() const {
  return tail_->val[tail_->last - 1];
}

std::string const & ULListStr::front() const {
  return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const {
  std::string* ptr;
  if (loc >= 0 && loc < size_) {
    Item* temp = head_;
    while (loc >= (temp->last - temp->first)) {
      loc -= temp->last - temp->first;
      temp = temp->next;
    }

    ptr = &temp->val[temp->first + loc];
    return ptr;
  }
  else {
    return NULL;
  }
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}