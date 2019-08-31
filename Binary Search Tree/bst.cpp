#include "bst.h"
#include <iostream>

using namespace std;

int main()
{
  BinarySearchTree<string, double> testnode;

  testnode.insert(make_pair("888", 3.5));
  testnode.insert(make_pair("999", 2.5));
  testnode.insert(make_pair("555", 6.5));
  testnode.insert(make_pair("333", 8.5));
  testnode.insert(make_pair("777", 7.5));
  testnode.insert(make_pair("790", 6.5));
    

  testnode.insert(make_pair("890", 6.5));
  testnode.insert(make_pair("1000", 6.5));
  cout<<testnode.isBalanced()<<endl;
  testnode.clear();


  testnode.insert(make_pair("FFF", 5));
  testnode.remove("BBB");
  testnode.remove("CCC");
  testnode.insert(make_pair("DDD", 5.5));

  testnode.print();

  
  return 0;


}
