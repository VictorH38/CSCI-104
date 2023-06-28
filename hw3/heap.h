#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
	std::vector<T> heap_;
	int ary;
	PComparator comp;
};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c) {
	ary = m;
	comp = c;
}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap() {

}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item) {
	heap_.push_back(item);
	unsigned int pos = heap_.size() - 1;
	unsigned int parentPos;
	if (pos == 0) {
		parentPos = 0;
	}
	else {
		parentPos = (pos - 1) / ary;
	}

	while (parentPos >= 0 && comp(heap_[pos], heap_[parentPos])) {
		std::swap(heap_[parentPos], heap_[pos]);
		pos = parentPos;
		if (pos == 0) {
			parentPos = 0;
		}
		else {
			parentPos = (pos - 1) / ary;
		}
	}
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const {
	return (heap_.size() == 0);
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const {
	return heap_.size();
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
		throw std::underflow_error("Heap is empty");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
	return heap_[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
		throw std::underflow_error("Heap is empty");
  }
	std::swap(heap_[0], heap_[heap_.size() - 1]);
	heap_.pop_back();

	unsigned int pos = 0;
	bool cont = true;
	while (cont) {
		unsigned int bestChild = (ary * pos) + 1;
		if (bestChild < heap_.size()) {
			for (int i = 2; i <= ary; i++) {
				unsigned int nextChild = (ary * pos) + i;
				if (nextChild < heap_.size()) {
					if (comp(heap_[nextChild], heap_[bestChild])) {
						bestChild = nextChild;
					}
				}
			}

			if (comp(heap_[bestChild], heap_[pos])) {
				std::swap(heap_[pos], heap_[bestChild]);
				pos = bestChild;
			}
			else {
				cont = false;
			}
		}
		else {
			cont = false;
		}
	}
}

#endif
