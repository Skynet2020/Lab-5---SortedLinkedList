/* 
 * File:   SortedLinkedList.h
 * Author: Arman B.
 *
 * Created on November 5, 2019, 1:58 PM
 */

#ifndef SORTEDLINKEDLIST_H
#define SORTEDLINKEDLIST_H


#include "SortedListInterface.h"
#include "Node.h"
#include "PrecondViolatedExcep.h"
#include <memory>
#include <cassert>
#include <iostream>
using namespace std;


                        ///*****  CLASS DEFINITION  *****///
template<class ItemType>
class SortedLinkedList : public SortedListInterface<ItemType>
{
private:
    
   shared_ptr<Node<ItemType>> head; // Pointer to first node in the chain;
   int itemCount;                   // Current count of list items 
   
   shared_ptr<Node<ItemType>> getNodeAt(int position) const;

public:
   SortedLinkedList();
   SortedLinkedList(const SortedLinkedList<ItemType>& aList);
//   SortedLinkedList(const SortedLinkedList<ItemType>& aList);
   virtual ~SortedLinkedList();

   bool insertSorted(const ItemType& newEntry);
   bool removeSorted(const ItemType& anEntry);
   int getPosition(const ItemType& anEntry) const;
   
   bool remove(int position);
   bool isEmpty() const;
   int getLength() const;
   void clear();
   ItemType getEntry(int position) const;  
};
#endif /* SORTEDLINKEDLIST_H */




                        ///***** DEFAULT CONSTRUCTOR *****///
template<class ItemType>
SortedLinkedList<ItemType>::SortedLinkedList() : head(nullptr), itemCount(0)
{
    cout << "The object was created successfully" << endl;
}


                        ///***** COPY CONSTRUCTOR *****///
template<class ItemType>
SortedLinkedList<ItemType>::SortedLinkedList(const SortedLinkedList<ItemType>& aList) : itemCount(aList.itemCount)
//SortedLinkedList<ItemType>::SortedLinkedList(const SortedLinkedList<ItemType>& aList) : itemCount(aList.itemCount)
{
    auto origChainPtr = aList.head;  // Points to nodes in original chain
    
    if (origChainPtr == nullptr)
        head.reset();  // Original list is empty
    else
    {
        // Copy first node
        head = make_shared<Node<ItemType>>();
        head->setItem(origChainPtr->getItem());
        
        // Copy remaining nodes
        auto newChainPtr = head;      // Points to last node in new chain
        origChainPtr = origChainPtr->getNext();     // Advance original-chain pointer
        while (origChainPtr != nullptr)
        {
            // Get next item from original chain
            ItemType nextItem = origChainPtr->getItem();
            
            // Create a new node containing the next item
            auto newNodePtr = make_shared<Node<ItemType>>(nextItem);
            
            // Link new node to end of new chain
            newChainPtr->setNext(newNodePtr);
            
            // Advance pointer to new last node
            newChainPtr = newChainPtr->getNext();
            
            // Advance original-chain pointer
            origChainPtr = origChainPtr->getNext();
        }  // end while
        
        newChainPtr->setNext(nullptr);
    }
}


                        ///***** DESTRUCTOR *****///
template<class ItemType>
SortedLinkedList<ItemType>::~SortedLinkedList()
{
    clear();
} 


                        ///*****  GET POSITION  *****///
template<class ItemType>
int SortedLinkedList<ItemType>::getPosition(const ItemType& anEntry) const
{
    int position;
    
    position = 1;

    auto curr = head;
    while ( (position <= itemCount) && (anEntry > curr->getItem()) && curr != nullptr)
    {
        position++;
        curr = curr->getNext();
    }

    if ( (position > itemCount) || (anEntry != curr->getItem()) )
        position = -position;
        
    return position;    
}


                        ///*****  INSERT SORTED  *****///
template<class ItemType>
bool SortedLinkedList<ItemType>::insertSorted(const ItemType& newEntry)
{
    int newPosition = abs(getPosition(newEntry));
    bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1);
    if (ableToInsert)
    {
        // Create a new node containing the new entry
        auto newNodePtr = make_shared<Node<ItemType>>(newEntry);
        
        // Attach new node to chain
        if (newPosition == 1)
        {
            // Insert new node at beginning of chain
            newNodePtr->setNext(head);
            head = newNodePtr;
        }
        else
        {
            // Find node that will be before new node
            auto prevPtr = getNodeAt(newPosition - 1);
            
            // Insert new node after node to which prevPtr points
            newNodePtr->setNext(prevPtr->getNext());
            prevPtr->setNext(newNodePtr);
        }  // end if
        
        itemCount++;  // Increase count of entries
    }  // end if
    
    return ableToInsert;
}                  


                        ///*****  REMOVE SORTED *****///
template<class ItemType>
bool SortedLinkedList<ItemType>::removeSorted(const ItemType& anEntry)
{
    bool ableToRemove = false;
    if (!isEmpty())
    {
        int position = getPosition(anEntry);
        
        ableToRemove = position > 0;
        if (ableToRemove)
        {
            ableToRemove = remove(position);
        }
    }
    
    return ableToRemove;
}


                        ///*****  REMOVE  *****///
template<class ItemType>
bool SortedLinkedList<ItemType>::remove(int position)
{
    bool ableToRemove = (position >= 1) && (position <= itemCount);
    if (ableToRemove)
    {
        if (position == 1)
        {
            // Remove the first node in the chain
            head = head->getNext();
        }
        else
        {
            // Find node that is before the one to delete
            auto prevPtr = getNodeAt(position - 1);
            
            // Point to node to delete
            auto curPtr = prevPtr->getNext();
            
            // Disconnect indicated node from chain by connecting the
            // prior node with the one after
            prevPtr->setNext(curPtr->getNext());
        }  // end if
        
        itemCount--;  // Decrease count of entries
    }  // end if
    
    return ableToRemove;
}


                        ///*****  GET ENTRY  *****///
template<class ItemType>
ItemType SortedLinkedList<ItemType>::getEntry(int position) const
{
    // Enforce precondition
    bool ableToGet = (position >= 1) && (position <= itemCount);
    if (ableToGet)
    {
        auto nodePtr = getNodeAt(position);
        return nodePtr->getItem();
    }
    else
    {
        string message = "getEntry() called with an empty list or ";
        message  = message + "invalid position.";
        throw(PrecondViolatedExcep(message));
    }
}

                        ///*****  GET NODE AT  *****///
template<class ItemType>
shared_ptr<Node<ItemType>> SortedLinkedList<ItemType>::getNodeAt(int position) const
{
    // Debugging check of precondition
    assert( (position >= 1) && (position <= itemCount) );
    
    // Count from the beginning of the chain
    auto curPtr = head;
    for (int skip = 1; skip < position; skip++)
        curPtr = curPtr->getNext();
    
    return curPtr;
}


                        ///*****  CLEAR  *****///
template<class ItemType>
void SortedLinkedList<ItemType>::clear()
{
    head.reset();
    itemCount = 0;
}

                        ///*****  isEMPTY?  *****///
template<class ItemType>
bool SortedLinkedList<ItemType>::isEmpty() const
{
    return itemCount == 0;
}

                        ///*****  GET LENGTH  *****///
template<class ItemType>
int SortedLinkedList<ItemType>::getLength() const
{
    return itemCount;
}
