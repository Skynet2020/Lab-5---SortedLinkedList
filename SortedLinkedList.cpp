#ifndef LINKED_LIST_
#define LINKED_LIST_

#include <memory>
#include "SortedListInterface.h"
#include "Node.h"
#include "PrecondViolatedExcep.h"
#include <cassert>

template<class ItemType>
class SortedLinkedList : public SortedListInterface<ItemType>
{
private:
   std::shared_ptr<Node<ItemType>> headPtr; // Pointer to first node in the chain;
   ItemType firstEntry;                     // Contains the first entry in the list
   Node<ItemType>* firstEntryPtr;			// Pointer to the first entry in the list
   int itemCount;           // Current count of list items 
   
   // Locates a specified node in this linked list.
   // @pre  position is the number of the desired node;
   //       position >= 1 and position <= itemCount.
   // @post  The node is found and a pointer to it is returned.
   // @param position  The number of the node to locate.
   // @return  A pointer to the node at the given position.
   shared_ptr<Node<ItemType>> getNodeAt(int position) const;

public:
   SortedLinkedList();
   SortedLinkedList(const SortedLinkedList<ItemType>& aList);
   virtual ~SortedLinkedList();

   virtual bool insertSorted(const ItemType& newEntry) = 0;
   virtual bool removeSorted(const ItemType& anEntry) = 0;
   virtual int getPosition(const ItemType& anEntry) const = 0;
   
   bool isEmpty() const;
   int getLength() const;
   bool remove(int position);
   void clear();
   ItemType getEntry(int position) const;   
}; // end SortedLinkedList


template<class ItemType>
SortedLinkedList<ItemType>::SortedLinkedList() : headPtr(nullptr), itemCount(0)
{
}  // end default constructor

template<class ItemType>
SortedLinkedList<ItemType>::SortedLinkedList(const SortedLinkedList<ItemType>& aList) : itemCount(aList.itemCount)
{
    auto origChainPtr = aList.headPtr;  // Points to nodes in original chain
    
    if (origChainPtr == nullptr)
        headPtr.reset();  // Original list is empty
    else
    {
        // Copy first node
        headPtr = std::make_shared<Node<ItemType>>();
        headPtr->setItem(origChainPtr->getItem());
        
        // Copy remaining nodes
        auto newChainPtr = headPtr;      // Points to last node in new chain
        origChainPtr = origChainPtr->getNext();     // Advance original-chain pointer
        while (origChainPtr != nullptr)
        {
            // Get next item from original chain
            ItemType nextItem = origChainPtr->getItem();
            
            // Create a new node containing the next item
            auto newNodePtr = std::make_shared<Node<ItemType>>(nextItem);
            
            // Link new node to end of new chain
            newChainPtr->setNext(newNodePtr);
            
            // Advance pointer to new last node
            newChainPtr = newChainPtr->getNext();
            
            // Advance original-chain pointer
            origChainPtr = origChainPtr->getNext();
        }  // end while
        
        newChainPtr->setNext(nullptr);              // Flag end of chain
    }  // end if
}  // end copy constructor

template<class ItemType>
SortedLinkedList<ItemType>::~SortedLinkedList()
{
    clear();
}  // end destructor

template<class ItemType>
bool SortedLinkedList<ItemType>::isEmpty() const
{
    return itemCount == 0;
}  // end isEmpty

template<class ItemType>
int SortedLinkedList<ItemType>::getLength() const
{
    return itemCount;
}  // end getLength

template<class ItemType>
bool SortedLinkedList<ItemType>::insert(int newPosition, const ItemType& newEntry)
{
    bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1);
    if (ableToInsert)
    {
        // Create a new node containing the new entry
        auto newNodePtr = std::make_shared<Node<ItemType>>(newEntry);
        
        // Attach new node to chain
        if (newPosition == 1)
        {
            // Insert new node at beginning of chain
            newNodePtr->setNext(headPtr);
            headPtr = newNodePtr;
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
}  // end insert

template<class ItemType>
bool SortedLinkedList<ItemType>::remove(int position)
{
    bool ableToRemove = (position >= 1) && (position <= itemCount);
    if (ableToRemove)
    {
        if (position == 1)
        {
            // Remove the first node in the chain
            headPtr = headPtr->getNext();
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
}  // end remove

template<class ItemType>
void SortedLinkedList<ItemType>::clear()
{
    headPtr.reset();
    // headPtr = nullptr; // is OK also
    itemCount = 0;
}  // end clear

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
        std::string message = "getEntry() called with an empty list or ";
        message  = message + "invalid position.";
        throw(PrecondViolatedExcep(message));
    }  // end if
}  // end getEntry

template<class ItemType>
void SortedLinkedList<ItemType>::replace(int position, const ItemType& newEntry)
{
    // Enforce precondition
    bool ableToSet = (position >= 1) && (position <= itemCount);
    if (ableToSet)
    {
        auto nodePtr = getNodeAt(position);
        nodePtr->setItem(newEntry);
    }
    else
    {
        // auto gives const string literal
        auto message = "replace() called with an invalid position.";
        throw(PrecondViolatedExcep(message));
    }  // end if
}  // end replace

template<class ItemType>
std::shared_ptr<Node<ItemType>> SortedLinkedList<ItemType>::getNodeAt(int position) const
{
    // Debugging check of precondition
    assert( (position >= 1) && (position <= itemCount) );
    
    // Count from the beginning of the chain
    auto curPtr = headPtr;
    for (int skip = 1; skip < position; skip++)
        curPtr = curPtr->getNext();
    
    return curPtr;
}  // end getNodeAt
//  End of implementation file.

#endif 
