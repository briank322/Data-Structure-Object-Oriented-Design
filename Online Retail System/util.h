#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2).
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
	std::set<T> inter_set;
	typename std::set<T>::iterator it = s1.begin();
	//Iterate through set1 n elements.
	//Total: O(nlogn)
	//O(n)
	while(it != s1.end())
	{
		if(s2.find(*it) != s2.end())
		{
			//O(logn)
			inter_set.insert(*it);
		}
		++it;
	}
	return inter_set;

}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
	std::set<T> union_set = s2;
	typename std::set<T>::iterator it = s1.begin();
	//Iterate through set1 n elements.
	//Total: O(nlogn)
	//O(n)
	while(it != s1.end())
	{
		if(union_set.end() == union_set.find(*it))
		{
			//O(logn)
			union_set.insert(*it);
		}
		++it;
	}
	return union_set;

}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions
//216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
