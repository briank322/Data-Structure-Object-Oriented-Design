#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a
 data member, plus other additional helper functions. 
 You do NOT need to implement any functionality or
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
    char getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);

    // Getters for parent, left, and right. 
    //These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. 
    //See the Node class in bst for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    char balance_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements 
by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, 
    const Value& value, AVLNode<Key, Value> *parent) :
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
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent 
since a static_cast is necessary to make sure
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
    void rotateLeft (AVLNode<Key, Value> *node);
    void rotateRight (AVLNode<Key, Value> *node);
    void insertfix(AVLNode<Key, Value>* g, AVLNode<Key, Value>* p);
    void removeFix(AVLNode<Key, Value>* p, int diff);


};

//rotate right, doesn't guarantee it is balanced after the rotation.
template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateRight (AVLNode<Key, Value> *node)
{
    if(node == NULL)
    {
        return;
    }
    if(node->getLeft() == NULL)
    {
        return;
    }
    //set the variable before you rotate.
    AVLNode<Key,Value>* left = node->getLeft();
    AVLNode<Key,Value>* parent = node->getParent();
    AVLNode<Key,Value>* LRchild = node->getLeft()->getRight();

    //if parent is null
    if(parent == NULL)
    {
        this->root_ = left;
        node->setLeft(LRchild);
        if(LRchild != NULL)
        {
            LRchild->setParent(node);
        }

        node->setParent(left);
        left->setParent(parent);
        left->setRight(node);
        return;
    }
    
    //if node was the left child of the ancestor 
    else if(parent!=NULL && parent->getLeft() == node)
    {
        node->setLeft(LRchild);
        if(LRchild != NULL)
        {
            LRchild->setParent(node);
        }
        node->setParent(left);
        left->setParent(parent);
        parent->setLeft(left);
        left->setRight(node);
        return;
    }

    //if node was the right child of the ancestor
    else if(parent!=NULL && parent->getRight() == node);
    {
        node->setLeft(LRchild);
        if(LRchild != NULL)
        {
            LRchild->setParent(node);
        }
        node->setParent(left);
        left->setParent(parent);
        parent->setRight(left);
        left->setRight(node);
        return;
    }

}

//rotate left, doesn't guarantee it is balanced after the rotation.
template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateLeft (AVLNode<Key, Value> *node)
{
    if(node == NULL)
    {
        return;
    }
    if(node->getRight() == NULL)
    {
        return;
    }

    //set variables before rotating it.
    AVLNode<Key,Value>* right = node->getRight();
    AVLNode<Key,Value>* parent = node->getParent();
    AVLNode<Key,Value>* RLchild = node->getRight()->getLeft();

    //if parent is null, update root to right.
    if(parent == NULL)
    {
        this->root_ = right;
        node->setRight(RLchild);
        //if right->left child is not null set parent.
        if(RLchild != NULL)
        {
            RLchild->setParent(node);
        }

        node->setParent(right);
        right->setParent(parent);
        right->setLeft(node);
        return;
    }
    
    //if node was the left child of the ancestor 
    else if(parent != NULL && parent->getLeft() == node)
    {
        node->setRight(RLchild);
        if(RLchild != NULL)
        {
            RLchild->setParent(node);
        }
        node->setParent(right);
        right->setParent(parent);
        parent->setLeft(right);
        right->setLeft(node);
        return;
    }

    //if node was the right child of the ancestor
    else if(parent != NULL && parent->getRight() == node);
    {
        node->setRight(RLchild);
        if(RLchild != NULL)
        {
            RLchild->setParent(node);
        }
        node->setParent(right);
        right->setParent(parent);
        parent->setRight(right);
        right->setLeft(node);
        return;
    }
}


//Followed the psudocode in Lecture 19 page40
template<typename Key, typename Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value> *n, int diff)
{
    if(n == NULL)
    {
        return;
    }

    int ndiff = -1;
    AVLNode<Key, Value>* p = n->getParent();

    if(p != NULL)
    {
        if(n == p->getLeft())
        {
            ndiff = 1;
        }
    }

    if(diff == -1)
    {
        if(n->getBalance() + diff == -2)
        {
            AVLNode<Key, Value>* c = n->getLeft();
            //zig-zig
            if(c->getBalance() == -1 || c->getBalance() == 0)
            {
                rotateRight(n);
                if(c->getBalance() == -1)
                {
                    n->setBalance(0);
                    c->setBalance(0);
                    removeFix(p, ndiff);
                }
                else if (c->getBalance() == 0)
                {
                    n->setBalance(-1);
                    c->setBalance(1);
                    return;
                }
            }
            //zig-zag
            else if(c->getBalance() == 1)
            {
                AVLNode<Key, Value>* g = c->getRight();
                rotateLeft(c);
                rotateRight(n);

                if(g->getBalance() == 1)
                {
                    n->setBalance(0);
                    c->setBalance(-1);
                }
                else if (g->getBalance() == 0)
                {
                    n->setBalance(0);
                    c->setBalance(0);
                }
                else if (g->getBalance() == -1)
                {
                    n->setBalance(1);
                    c->setBalance(0);
                }
                g->setBalance(0);
                removeFix(p, ndiff);
            }
        } 
        else if(n->getBalance() + diff == -1)
        {
            n->setBalance(-1);
            return;
        }
        else if(n->getBalance() + diff == 0)
        {
            n->setBalance(0);
            removeFix(p, ndiff);
        }
    }
    //same method just flip left to right and - to +
    else 
    {
        
        if(n->getBalance() + diff == 2)
        {
            AVLNode<Key, Value>* c = n->getRight();
            //zig-zig
            if(c->getBalance() == 1 || c->getBalance() == 0)
            {
                rotateLeft(n);
                if(c->getBalance() == 1)
                {
                    n->setBalance(0);
                    c->setBalance(0);
                    removeFix(p, ndiff);
                }
                else if (c->getBalance() == 0)
                {
                    n->setBalance(1);
                    c->setBalance(-1);
                    return;
                }
            }
            //zig-zag
            else if(c->getBalance() == -1)
            {
                AVLNode<Key, Value>* g = c->getLeft();
                rotateRight(c);
                rotateLeft(n);

                if(g->getBalance() == -1)
                {
                    n->setBalance(0);
                    c->setBalance(1);
                    
                }
                else if (g->getBalance() == 0)
                {
                    n->setBalance(0);
                    c->setBalance(0);
                    
                }
                else if (g->getBalance() == 1)
                {
                    n->setBalance(-1);
                    c->setBalance(0);
                    
                }
                g->setBalance(0);
                removeFix(p, ndiff);
            }
        }
        else if(n->getBalance() + diff == 1)
        {
            n->setBalance(1);
            return;
        }
        else if(n->getBalance() + diff == 0)
        {
            n->setBalance(0);
            removeFix(p, ndiff);
        }

    }
}

//Followed the psudocode in Lecture 19 page 32.
template<typename Key, typename Value>
void AVLTree<Key, Value>::insertfix(AVLNode<Key, Value>* p, 
    AVLNode<Key, Value>* n)
{   
    if(p == NULL) 
    {
        return;
    }
    if(p->getParent() == NULL)
    {
        return;
    } 
    AVLNode<Key, Value>* g = p->getParent();
    //p: left child
    if(p == g->getLeft())
    {
        int temp = g->getBalance();
        g->setBalance(temp-1);
        if(g->getBalance() == 0)
        {
            return;
        }
        else if(g->getBalance() == -1)
        {
            insertfix(g, p);
        }
        else if(g->getBalance() == -2)
        {
            //zig-zig Left
            if(n == p->getLeft() && g->getLeft() == p)
            {
                rotateRight(g);
                p->setBalance(0);
                g->setBalance(0);
                
            }
            //zig-zag
            else if(n == p->getRight()&& g->getLeft() == p)
            {
                rotateLeft(p);
                rotateRight(g);

                if(n->getBalance() == -1)
                {
                    p->setBalance(0);
                    g->setBalance(1);
                    
                }
                else if(n->getBalance() == 0)
                {
                    p->setBalance(0);
                    g->setBalance(0);
                    
                }
                else if(n->getBalance() == 1)
                {
                    p->setBalance(-1);
                    g->setBalance(0);
                    
                }
                n->setBalance(0);
                
            }
        }
    }
    //p: right child
    else if(p == g->getRight())
    {
        int temp = g->getBalance();
        g->setBalance(temp+1);
        if(g->getBalance() == 0)
        {
            return;
        }
        else if(g->getBalance() == 1)
        {
            insertfix(g, p);
            return;
        }
        else if(g->getBalance() == 2)
        {
            //zig-zig Right
            if(n == p->getRight() && g->getRight() == p)
            {
                rotateLeft(g);
                p->setBalance(0);
                g->setBalance(0);
                
            }
            //zig-zag
            else if(n == p->getLeft()&& g->getRight() == p)
            {
                rotateRight(p);
                rotateLeft(g);
                if(n->getBalance() == 1)
                {
                    p->setBalance(0);
                    g->setBalance(-1);
                }
                else if(n->getBalance() == 0)
                {
                    p->setBalance(0);
                    g->setBalance(0);
                }
                else if(n->getBalance() == -1)
                {
                    p->setBalance(1);
                    g->setBalance(0);
                }
                n->setBalance(0);
                
            }
        }
    }
    
}


template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair
    <const Key, Value> &new_item)
{
    // TODO
    AVLNode<Key, Value>* newNode = 
    new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);

    //all new node is set as balance factor 0
    newNode->setBalance(0);

    //if there was nothing, newnode is now new root_.
    if(this->root_ == NULL)
    {
        this->root_ = newNode;
        return;
    }

    //if there was some node.
    else
    {
        AVLNode<Key, Value>* temp 
        = static_cast<AVLNode<Key, Value>*>(this->root_);
        
        while (temp != NULL)
        {
            //check for duplicates
            if (temp->getKey() == newNode->getKey()) 
            {
                temp->setValue(newNode->getValue());
                delete newNode;
                return;
            }
            //if newnode is smaller than tempnode
            else if (newNode->getKey() < temp->getKey()) 
            {
                //traverse left
                if(temp->getLeft() != NULL)
                {
                    temp = temp->getLeft();
                }
                //upate the child,parent pointers and set balance 
                //as psudocode indicates
                else
                {
                    temp->setLeft(newNode);
                    newNode->setParent(temp);
                
                    if(temp->getBalance() == -1)
                    {
                        temp->setBalance(0);
                    }
                    else if(temp->getBalance() == 1)
                    {
                        temp->setBalance(0);
                    }
                    else if(temp->getBalance() == 0)
                    {
                        temp->setBalance(-1);
                        insertfix(temp, newNode);
                    }
                    return;
                }
                

            } 
            //if newnode is bigger than the temp node
            else if (newNode->getKey() > temp->getKey()) 
            {
                //explore right tree
                if(temp->getRight() != NULL)
                {
                    temp = temp->getRight();
                }
                //if there is no right child, update child, parent pointers.
                else
                {
                    temp -> setRight(newNode);
                    newNode->setParent(temp);
                    
                    if(temp->getBalance() == -1)
                    {
                        temp->setBalance(0);
                    }
                    else if(temp->getBalance() == 1)
                    {
                        temp->setBalance(0);
                    }
                    else if(temp->getBalance() == 0)
                    {
                        temp->setBalance(1);
                        insertfix(temp, newNode);
                    }
                    return;
                }
                
                
            }

        }

    }
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    int diff;
    AVLNode<Key, Value>* n 
    = static_cast<AVLNode<Key, Value>*>
    (BinarySearchTree<Key, Value>::internalFind(key));
    if (n == NULL)
    {
        return;
    }
    bool leaf = true;
    if(n->getLeft() != NULL && n->getRight() != NULL)
    {
        leaf = false;
    }
    //if has 2 child find pred, and swap using nodeswap.
    if (n!=NULL && !leaf && this->predecessor(n) != NULL)
    {   
        nodeSwap(n, static_cast<AVLNode<Key, Value>*>(this->predecessor(n)));
    }

    AVLNode<Key, Value>* p = n->getParent();
    AVLNode<Key, Value>* child = n->getLeft();
    //update root
    if(p == NULL)
    {
        //SINGLE NODE, update root
        if (n->getLeft() == NULL && n->getRight() == NULL)
        {    
            child = NULL;  
        }
        //Has a left child, root=leftchild
        else if (n->getLeft() != NULL)
        {
            n->getLeft()->setParent(NULL);
        }
        else 
        {
            child = n->getRight();
            n->getRight()->setParent(NULL);
        }

        this->root_ = child;
        delete n;
        return;
    }

   
        //left child set diff to 1
    if (p!=NULL && n == p->getLeft()) 
    {
            p->setLeft(NULL);
            diff = 1;
            //only if n has at least one child.
            if(n->getLeft() != NULL || n->getRight() != NULL)
            {
                if (n->getRight() == NULL)
                {
                    p->setLeft(n->getLeft());
                    p->getLeft()->setParent(p);
                }
                else if (n->getLeft() == NULL)
                {
                    p->setLeft(n->getRight());
                    p->getLeft()->setParent(p);
                }
            }
            else
            {
                delete n;
                removeFix(p, diff);
                return;
            }
        
        
    }
    //right child set diff to -1
    else if (p!=NULL && n == p->getRight()) 
    {
        
            p->setRight(NULL);
            diff = -1;
            //only if n has at least one child then set pointers.
            if(n->getLeft() != NULL || n->getRight() != NULL)
            {
                if (n->getRight() == NULL)
                {
                    p->setRight(n->getLeft());
                    p->getRight()->setParent(p);
                }
                else if (n->getLeft() == NULL)
                {
                    p->setRight(n->getRight());
                    p->getRight()->setParent(p);
                }
            }
            else
            {
                delete n;
                removeFix(p, diff);
                return;
            }
            
        
        
    }
    
    delete n;
    removeFix(p, diff);
    
    

}


template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, 
    AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    char tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
