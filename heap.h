#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>


template <typename T, typename PComparator = std::less<T> >
class Heap
{
 public:
  /// Constructs an m-ary heap for any m >= 2
  Heap(int m, PComparator c = PComparator());

  /// Destructor as needed
  ~Heap();

  /// Adds an item
  void push(const T& item);

  /// returns the element at the top of the heap 
  ///  max (if max-heap) or min (if min-heap)
  T const & top() const;

  /// Removes the top element
  void pop();

  /// returns true if the heap is empty
  bool empty() const;

 private:
  /// Add whatever helper functions and data members you need below
  void trickleUp(int idx);
  void heapify(unsigned int idx);
  //swaping the elements of the vector, not the entire vector.
  std::vector<T> vec_swap(int idx1, int idx2, std::vector<T>& vec);
  std::vector<T> items_;
  unsigned int m_array;
  PComparator Comp;

};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c)
{
  m_array = m;
  Comp = c;
}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{

}

//Referenced from the lecture slide(Trees&Heaps pg.23) psudocode
template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  items_.push_back(item);
  trickleUp(items_.size()-1);
}


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  else
  {
    return items_.front();
  }
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
// Referenced from the lecture slide(Trees&Heaps pg.25) psudocode
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }
  else
  {
    items_.front() = items_.back();
    items_.pop_back();
    heapify(0);
  }
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  if(items_.empty())
  {
    return true;
  }
  else
  {
    return false;
  }
}

//swaping the elements of the vector, not the entire vector.
template<typename T, typename PComparator>
std::vector<T> Heap<T, PComparator>::vec_swap(int idx1, 
  int idx2, std::vector<T>& vec)
{
  T buf = vec[idx1];
  vec[idx1] = vec[idx2];
  vec[idx2] = buf;
  return vec;
}

//Add item to first free location at bottom of tree;
//Recursively promote it up while it is less than its parent
//Referenced from the lecture slide(Trees&Heaps pg.23) psudocode
template<typename T, typename PComparator>
void Heap<T, PComparator>::trickleUp(int idx)
{
  //if it's a root node, just return
  if(idx == 0)
  {
    return;
  }
  //Initialize the parent using parent*m_array+1 = idx.
  else
  {
    int parent = (idx-1)/m_array;

    while( idx >0 && Comp(items_[idx],items_[parent]))
    {
      vec_swap(idx, parent, items_);
      idx = parent;
      parent = (idx-1)/m_array;
    }
  }
}

//Heapify:Takes last (greatest) node puts it in the top location and then
//recursively swaps it for the best child until it's in its right place
//Referenced from the lecture slide(Trees&Heaps pg.25) psudocode
template<typename T, typename PComparator>
void Heap<T, PComparator>::heapify(unsigned int idx)
{
  //if tree has a single node, just return.
  if(items_.size()<2)
  {
    return;
  }
  //if it is a leaf just return.
  if(idx*m_array + 1  >= items_.size())
  {
    return;
  }
  else
  {
      //update the bestchild, start w/ left
      unsigned int bestchild = m_array*idx + 1;
      unsigned firstChild = bestchild;
    
      //iterate through until the right most leaf.
      //find the best child
      for(unsigned i=firstChild; i < firstChild+m_array 
        && i < items_.size(); i++)
      {
          //if right child exists, moving one by one.
          if(Comp(items_[i],items_[bestchild]))
          {
              bestchild = i;
          }
        
      }
      //Overwrite
      if(Comp(items_[bestchild], items_[idx]))
      {
          vec_swap(idx, bestchild, items_);
          heapify(bestchild);
      }
  }
  
}

#endif
