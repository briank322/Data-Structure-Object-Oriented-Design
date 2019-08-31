#ifndef MSORT_H
#define MSORT_H
#include <vector>
#include <iostream>
#include <string>

//Prototype
template <class T, class Comparator>
void mergeSort(std::vector<T>& myArray, Comparator comp);

template<class T, class Comparator>
void msort_helper(unsigned int index1, unsigned int index2,
 std::vector<T> left, std::vector<T>right,
 std::vector<T>& finalArray,Comparator comp);


//MUST RUN on O(nlogn)
template <class T, class Comparator>
void mergeSort(std::vector<T>& myArray, Comparator comp)
{
	unsigned int i = 0;
	unsigned int index1 = 0;
	unsigned int index2 = 0;

	std::vector<T> temp1;
	std::vector<T> temp2;
	//if the array has size 1, it's already sorted.
	if (myArray.size() <= 1)
	{
		return;
	}
	//divide myarray into half and pushback into two temp vector.
	while(i < myArray.size())
	{
		if(i<myArray.size()/2)
		{
			temp1.push_back(myArray[i]);
		}

		else if(i>=myArray.size()/2)
		{
			temp2.push_back(myArray[i]);
		}

		i++;
	}
	//use msorthelper function to actually merge 
	mergeSort(temp1, comp);
	mergeSort(temp2, comp);
	msort_helper(index1, index2, temp1, temp2, myArray, comp);
}


//helper function.
template<class T, class Comparator>
void msort_helper(unsigned int index1, unsigned int index2,
	std::vector<T> first, std::vector<T> second,
std::vector<T>& sorted_array, Comparator comp)
{
	//initialize the index1 and index2
	index1 = 0;
	index2 = 0;
	//this traverse index will find the right position for sortedarray.
	unsigned int traverse_idx = 0;

	while(index1 < first.size() && index2 < second.size())
	{
		// first < second then update
		if(comp(first[index1], second[index2]) == true)
		{
			sorted_array[traverse_idx] = first[index1];
			traverse_idx++;
			index1++;
		}

		// second < first then update
		else if(comp(first[index1], second[index2]) == false)
		{
			sorted_array[traverse_idx] = second[index2];
			traverse_idx++;
			index2++;
		}
		
	}

	//After reading it, update the final array
	while(index1 < first.size())
	{
		sorted_array[traverse_idx] = first[index1];
		traverse_idx++;
		index1++;
	}

	while( index2 < second.size())
	{
		sorted_array[traverse_idx] = second[index2];
		traverse_idx++;
		index2++;
	}
}

#endif
