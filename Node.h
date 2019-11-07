// Created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** @file Node.h 
    Listing 4-1 */
#ifndef NODE_
#define NODE_

#include <memory>
using namespace std;


                        ///***** CLASS DEFINITION  *****///
template<class ItemType>
class Node
{
private:
   ItemType item; // A data item
   shared_ptr<Node<ItemType>> next; // Pointer to next node
   
public:
   Node();
   Node(const ItemType& anItem);
   Node(const ItemType& anItem, std::shared_ptr<Node<ItemType>> nextNodePtr);
   void setItem(const ItemType& anItem);
   void setNext(std::shared_ptr<Node<ItemType>> nextNodePtr);
   ItemType getItem() const ;
   std::shared_ptr<Node<ItemType>> getNext() const ;

};

                        ///***** DEAULT CONSTRUCTOR *****///
template<class ItemType>
Node<ItemType>::Node()
{
}

                        ///***** PARAMETRIZED CONSTRUCTOR-1  *****///
template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem)
{
}

                        ///***** PARAMETRIZED CONSTRUCTOR-2  *****///
template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem,
                     std::shared_ptr<Node<ItemType>> nextNodePtr)
: item(anItem), next(nextNodePtr)
{
}

                        ///***** SET ITEM  *****///
template<class ItemType>
void Node<ItemType>::setItem(const ItemType& anItem)
{
    item = anItem;
}

                        ///***** SET NEXT  *****///
template<class ItemType>
void Node<ItemType>::setNext(std::shared_ptr<Node<ItemType>> nextNodePtr)
{
    next = nextNodePtr;
}

                        ///***** GET ITEM  *****///
template<class ItemType>
ItemType Node<ItemType>::getItem() const
{
    return item;
}

                        ///***** GET NEXT  *****///
template<class ItemType>
std::shared_ptr<Node<ItemType>> Node<ItemType>::getNext() const
{
    return next;
}

#endif
