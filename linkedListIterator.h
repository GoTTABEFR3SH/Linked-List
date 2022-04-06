/*---------------------------------------------------------------------------------------------------------
    THIS FILE CONTAINS THE FUNCTIONS DECLARTIONS AND IMPLEMENTATION DETAILS OF THE ITERATORS OF LINKED LIST
-----------------------------------------------------------------------------------------------------------*/

#pragma once
template <class Type>
struct nodeType // Define the node for the linked list and the iterators
{
	Type info{}; // to hold data
	nodeType<Type>* link{}; // to link to the next node
};


template <class Type>
class linkedListIterator
{
	public:
		linkedListIterator(); // default construtors
		linkedListIterator(nodeType<Type>* ptr); // custom constructor
		Type operator *(); //overloads on the next foudlins
		linkedListIterator<Type> operator++();
		bool operator==(const linkedListIterator<Type>& right) const;
		bool operator != (const linkedListIterator<Type>& right) const;
	
		nodeType<Type>* current; // the two pointers that make up a iterator I made them public so I could access them in the linked list .cpp
		nodeType<Type>* lastCurrent;
};

template <class Type>
linkedListIterator<Type>::linkedListIterator() // default constructor
{
	current = nullptr;
	lastCurrent = nullptr;
}

template <class Type>
linkedListIterator<Type>::linkedListIterator(nodeType<Type>* ptr) // sets the iterator to the specified ptr this is just to implement begin() and end() in linkedlist.cpp
{
	current = ptr;
	lastCurrent = nullptr;
}

template <class Type>
Type linkedListIterator<Type>::operator*() // derefenceing operator to get the info from the current pointer of the iterator
{
	return current->info;
}

template <class Type> 
linkedListIterator<Type> linkedListIterator<Type>::operator++() // to increment the iterator
{

	lastCurrent = current; // update last current to move forward
	current = current->link; // advance current
	return *this; // return the calling iterator
}

template <class Type>
bool linkedListIterator<Type>::operator==(const linkedListIterator<Type>& right) const // checks the eqaulty of the enter iterator with the current one
{
	return (current == right.current);
}

template <class Type>
bool linkedListIterator<Type>::operator!=(const linkedListIterator<Type>& right) const // same thing as ==
{
	return (current != right.current);
}