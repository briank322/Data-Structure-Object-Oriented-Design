#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment. **/
std::set<std::string> parseStringToWords(string rawWords)
{
    //return value which is a set of keywords.
    set<string> keywords;
    //Modify all incoming letters to lowercase.
    stringstream ss;
    ss<<(convToLower(rawWords));
    string sub;
    string temp;

    // Reading in individual words, stopping at whitespace
    while (ss >> sub)
    {   
        //Initialize the temp string.
        temp.clear();
        //Iterate through the entire elements of the string.
        for (unsigned int i = 0; i < sub.size(); i++)
        {
            // If there is at least one punctuation.
            if (ispunct(sub[i]))
            {
                keywords.insert(temp);
            }
            
            else 
            {
                //Append char to the temp.
                temp += sub[i];
            }
        }
        // Add temp to set(keywords) if there is still an element.
        if (temp.length() >= 2)
        {
            keywords.insert(temp);
        }
        
    }
    return keywords;

}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions
//216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
       std::find_if(s.begin(), 
        s.end(), 
        std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
       std::find_if(s.rbegin(), 
        s.rend(), 
        std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
       s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
