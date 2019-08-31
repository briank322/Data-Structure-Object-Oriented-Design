#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
template <
         typename T,
         typename TComparator = std::equal_to<T>,
         typename PComparator = std::less<double>,
         typename Hasher = std::hash<T> >
class Heap
{
public:
    /// Constructs an m-ary heap. M should be >= 2
    Heap(int m = 2,
         const PComparator& c = PComparator(),
         const Hasher& hash = Hasher(),
         const TComparator& tcomp = TComparator()  );

    /// Destructor as needed
    ~Heap();

    /// Adds an item with the provided priority
    void push(double pri, const T& item);

    /// returns the element at the top of the heap
    ///  max (if max-heap) or min (if min-heap)
    T const & top() const;

    /// Removes the top element
    void pop();

    /// returns true if the heap is empty
    bool empty() const;

    /// decreaseKey reduces the current priority of
    /// item to newpri, moving it up in the heap
    /// as appropriate.
    void decreaseKey(double newpri, const T& item);
    

private:
    /// Add whatever helper functions you need below
	void trickleUp(int idx);
 	void heapify(unsigned int idx);

    // These should be all the data members you need.
    std::vector< std::pair<double, T> > store_;
    int m_;
    PComparator c_;
    std::unordered_map<T, size_t, Hasher, TComparator> keyToLocation_;

};

// Complete
template<typename T,typename TComparator,typename PComparator,typename Hasher>
Heap<T,TComparator,PComparator,Hasher>::Heap(
    int m,
    const PComparator& c,
    const Hasher& hash,
    const TComparator& tcomp ) :

    store_(),
    m_(m),
    c_(c),
    keyToLocation_(100, hash, tcomp)

{

}

// Complete
template<typename T,typename TComparator,typename PComparator,typename Hasher>
Heap<T,TComparator,PComparator,Hasher>::~Heap()
{

}

template<typename T,typename TComparator,typename PComparator,typename Hasher>
void Heap<T,TComparator,PComparator,Hasher>::push(double priority
	,const T& item)
{
    // You complete.
	store_.push_back(std::make_pair(priority, item));
	keyToLocation_[item] = store_.size()-1;
	trickleUp(store_.size()-1);

}

template<typename T,typename TComparator,typename PComparator,typename Hasher>
void Heap<T,TComparator,PComparator,Hasher>::decreaseKey(double priority
	, const T& item)
{
    // You complete
    typename std::unordered_map<T, size_t, Hasher, TComparator>::iterator val
    = keyToLocation_.find(item);
    store_[val->second].first = priority;
    trickleUp(val->second);

}

template<typename T,typename TComparator,typename PComparator,typename Hasher>
T const & Heap<T,TComparator,PComparator,Hasher>::top() const
{
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if(empty()) {
        throw std::logic_error("can't top an empty heap");
    }

    // You complete
    else
    {
    	return store_[0].second;
    }

}

/// Removes the top element
template<typename T,typename TComparator,typename PComparator,typename Hasher>
void Heap<T,TComparator,PComparator,Hasher>::pop()
{
    if(empty()) {
        throw std::logic_error("can't pop an empty heap");
    }
    // You complete
    else 
    {
        keyToLocation_.erase(store_[0].second);
        store_[0] = store_[store_.size() - 1];
        store_.pop_back();
        heapify(0);
    }


}

/// returns true if the heap is empty
template<typename T,typename TComparator,typename PComparator,typename Hasher>
bool Heap<T,TComparator,PComparator,Hasher>::empty() const
{
    return store_.empty();
}


//Add item to first free location at bottom of tree;
//Recursively promote it up while it is less than its parent
//Referenced from the lecture slide(Trees&Heaps pg.23) psudocode
template<typename T,typename TComparator,typename PComparator,typename Hasher>
void Heap<T,TComparator,PComparator,Hasher>::trickleUp(int idx)
{
	//if it's a root node, just return
	if(idx == 0)
	{
		return;
	}
	//Initialize the parent using parent*2+1 = idx.
	else
	{
		int parent = (idx-1)/m_;

		while( idx >0 && c_(store_[idx].first,store_[parent].first))
		{
			std::pair<double, T> temp = store_[parent];
			store_[parent] = store_[idx];
			keyToLocation_[store_[idx].second] = parent;
			store_[idx] = temp;
			keyToLocation_[store_[idx].second] = idx;
			idx = parent;
			parent = (idx-1)/m_;
		}
	}
}

//Heapify:Takes last (greatest) node puts it in the top location and then
//recursively swaps it for the best child until it's in its right place
//Referenced from the lecture slide(Trees&Heaps pg.25) psudocode
template<typename T,typename TComparator,typename PComparator,typename Hasher>
void Heap<T,TComparator,PComparator,Hasher>::heapify(unsigned int idx)
{
	//if tree has a single node, just return.
	if(store_.size()<2)
	{
		return;
	}
	//if it is a leaf just return.
	if(idx*m_ + 1  >= store_.size())
	{
		return;
	}
	else
	{
		  //update the bestchild, start w/ left
		  unsigned int bestchild = m_*idx + 1;
		  unsigned firstChild = bestchild;

		  //iterate through until the right most leaf.
		  //find the best child
		  for(unsigned i=firstChild; i < firstChild+m_ 
		    && i < store_.size(); i++)
		  {
		      //if right child exists, moving one by one.
		      if(c_(store_[i].first,store_[bestchild].first))
		      {
		          bestchild = i;
		      }
		    
		  }
		  //Overwrite
		  if(c_(store_[bestchild].first, store_[idx].first))
		  {
			   std::pair<double, T> tempx = store_[idx];
			   store_[idx] = store_[bestchild];
			   keyToLocation_[store_[idx].second] = idx;
			   store_[bestchild] = tempx;
			   keyToLocation_[store_[bestchild].second] = bestchild;
			   heapify(bestchild);
		  }
	}
  
}


#endif
