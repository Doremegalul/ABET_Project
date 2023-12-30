/*****************************************************
min heap class
*******************************************************/
#ifndef MINHEAP_GRAPH_H
#define MINHEAP_GRAPH_H
#include <iostream> //for operator<<()
using namespace std;
#include "swap.h" //for mySwap(). 

template <class T>
class minHeap;

template <class T>
ostream& operator<<(ostream& o, const minHeap<T>& h);

template <class T>
class minHeap
{
	friend ostream& operator<< <T>(ostream& o, const minHeap<T>& h);
private:
	T* ar; //dynamic array
	int capacity; //the size of ar
	int num; //the number of elements I have in ar
public:
	minHeap(){ar = NULL; capacity = 0; num = 0;}
	minHeap(int c){capacity = c; ar = new T [capacity]; num = 0;}
	~minHeap(){if(ar!=NULL)delete [] ar;}
	void min_heapify(int* curDist, int* locator, int i);
	void bubbleUp(int* curDist, int* locator, int i);
	void insert(int* curDist, int* locator, const T& el);
	int find(int key) const;
	void remove(int* curDist, int* locator, int i);
	T getMin(int* curDist, int* locator);
  
	int getNum() const;
	void fixHeap(int* curDist, int* locator, int i);

	class Overflow{};
	class BadIndex{};
	class NotFound{};
};


/*
This function is a buble down function or to setup of heap rooted
int i is the index
*/
template <class T>
void minHeap<T>::min_heapify(int* curDist, int* locator, int i)
{
	int l = 2 * i + 1; //Left 
	int r = 2 * i + 2; //Right
	int smallest = i; 

	if(l < num && curDist[ar[l]] < curDist[ar[smallest]]) //If left is smaller
    {
      smallest = l; 
    }
	if(r < num && curDist[ar[r]] < curDist[ar[smallest]]) //If right is smaller
    {
      smallest = r; 
    }
	if(smallest != i) //If left or right child is smaller, swap
    {
		mySwap(locator[ar[i]], locator[ar[smallest]]);
		mySwap(ar[i], ar[smallest]);
		min_heapify(curDist, locator, smallest);
    }
}

/*
This function is to corrects a violiation at i by bubbling it up to the correct place 
int i is the index 
*/
template <class T>
void minHeap<T>::bubbleUp(int* curDist, int* locator, int i)
{
	int parent = (i - 1) / 2; //Creating a parent.
	if(curDist[ar[i]] < curDist[ar[parent]] && i > 0)
	{
		mySwap(locator[ar[i]], locator[ar[parent]]);
		mySwap(ar[i], ar[parent]);
		bubbleUp(curDist, locator, parent);
	}
}

/*
This function is to insert the element to the array
const Y& el is element
*/
template <class T>
void minHeap<T>::insert(int* curDist, int* locator, const T& el)
{
	if(num == capacity) //Array is full
    {
		throw Overflow(); //"The array is full";
    }
	
	ar[num] = el; 
	bubbleUp(curDist, locator, num - 1); 
	num++;
}

/*
This function returns the index where key was found or throws an exception if key is not found.
Return index
*/
template <class T>
int minHeap<T>::find(int key) const
{
	for(int i = 0; i < num; i++)//Go through array
	{
		if(ar[i] == key)
		{
			return i;
		}
		else
		{
			return -1;
		}
	}
}

/*
This function is to remove the element in the array
int i is index
*/
template <class T>
void minHeap<T>::remove(int* curDist, int* locator, int i)
{
	if(i < 0 || i >= num) //If there is nothing
	{
		throw BadIndex(); //"The element doesn't exist";    
	}

	mySwap(locator[ar[i]], locator[ar[num - 1]]);
	mySwap(ar[i], ar[num - 1]); //Swap top and bottom
	num--; 
	fixHeap(curDist, locator, i);
}

/*
This function is to get the remove element
return element
*/
template <class T>
T minHeap<T>::getMin(int* curDist, int* locator)
{
	//This function removes the top element and returns it.
	//You should be calling remove()
	if(num > 0)
    {
		T el = ar[0]; 
		remove(curDist, locator, 0); 
		return el; 
    }
}

/*
This function is overload operator of cout
ostream& o is cout
const minHeap<T>& h is the struct class accesss
return the array
*/
template<class T>
ostream& operator<<(ostream& o, const minHeap<T>& h)
{
	if(h.num == 0) //If it is empty
	{
		o << "none";
	}
	else
	{
		for(int i = 0; i < h.num; i++) //Go through the current element amount
		{
			o << h.ar[i] << " ";
		}
	}
	o << endl;
	return o;
}
 
//return the number of elements in the heap.
template <class T>
int minHeap<T>::getNum() const
{
	return num;
}

//i is the index (within heap) of the vertex whose distance was changed.
//For example, if vertex 0's distance changed when it is located at 3, i is 3. This is where the heap needs to be fixed by either going up or down.
//curDist is the array that contains the shortest distance from start to every other vertex.
//locator is the array that contains the location of each vertex within the heap. Make sure you understand the homework document posted on Canvas to understand how locator works.  
template <class T>
void minHeap<T>::fixHeap(int* curDist, int* locator, int i)
{
	//We need to maintain the min heap based on curDist. When 2 vertices swap within the heap, their locations will change, hence you need to update the locator array. Make sure you understa nd how each array works by reading the homework document (there are pictures to explain).
  
	//From i, either bubble up or down.                                                                                           
	//For up, call bubbleUp(). For down, call min_heapify(). 
	if(i < num && i >= 0)
    {
		if(curDist[ar[i]] < curDist[ar[(i - 1) / 2]]) 
		{
			bubbleUp(curDist, locator, i);
		}			
		else 
		{
			min_heapify(curDist, locator, i); 
		}
    }
	//Reminder: A lot of the member functions in minHeap class need to have 2 more parameters, int* curDist, int* locator.
	
	//Since I have the same code inside minHeap::remove(), I am now calling fixHeap() from remove() so I won't have duplicate code.	
}

#endif
