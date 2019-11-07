/* 
 * File:   main.cpp
 * Author: Arman Belyalov
 * Created on November 5, 2019, 7:23 PM
 */

#include <iostream>
#include <random>
#include <chrono>
#include <thread>

#include "SortedLinkedList.h"
using namespace std;

///***** PROTOTYPES *****///
template <class ItemType>
void displayAnArray(ItemType anArray[], int size);
int generateARandomNumber();


int main(int argc, char** argv) {
    
    int size = 21;        
    
    SortedListInterface<int>* obj = new SortedLinkedList<int>();
    int firstEntry;
    
    cout << "Object isEmpty?: " << obj->isEmpty() << "(should be 1)" << endl;
    cout << "Populating the chain with random numbers:";
    for (int i=1; i<=size; i++)
    {
        int randomNumber = generateARandomNumber();
        obj->insertSorted(randomNumber);
        cout << ' ' << randomNumber;
        if (i==1)
        {
            firstEntry = randomNumber;
        }
    } cout << endl;
    cout << "Object isEmpty?: " << obj->isEmpty() << "(should be 0)" << endl;
    cout << "Chain length: " << obj->getLength() << endl;
    
    cout << "First entry is: " << firstEntry << endl;
    cout << "Removing the first entry (" << firstEntry << ")..." << endl;
    if (obj->removeSorted(firstEntry))
    {
        cout << "The first entry was successfully removed." << endl;
    } else {
        cout << "Couldn't remove the first entry." << endl;
    }
    cout << "Chain content: ";
    for (int i=1; i<=obj->getLength(); i++)
    {
        cout << obj->getEntry(i) << ' ';
    } cout << endl;
    
    
//    cout << "Testing the copy constructor:" << endl;    
//    SortedListInterface<int>* obj2 = new SortedLinkedList<int>(obj);
//    cout << "obj2 length: " << obj2->getLength() << endl;
            
    return 0;
}


                        ///***** GENERATE A RANDOM NUMBER *****///
//template <class ItemType>
int generateARandomNumber()
{
    ///***** Chrono library: *****///
    typedef chrono::high_resolution_clock myclock;
    myclock::time_point beginning = myclock::now();
    
    // Creates an interval between two now() to get a higher seed:
    this_thread::sleep_for(chrono::milliseconds(3));
    
    // Duration calculates the time span between two now() measurements:
    myclock::duration d = myclock::now() - beginning;
    
    unsigned seed = d.count();
    default_random_engine generator (seed);    
    
    uniform_int_distribution<int> distribution(1,100);
//    for (int i=0; i<size; i++)
//        anArray[i] = distribution(generator);
    return distribution(generator);
}
