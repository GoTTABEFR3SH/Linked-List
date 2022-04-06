/*----------------------------------------------------------------
	THIS FILE CONTAINS ALL OF THE LINKED LIST FUNCTION DECLARTIONS
------------------------------------------------------------------*/


#pragma once
#include "linkedListIterator.h" // include the iterators


template <class Type>

class linkedList
{
	public:
		void print() const;
		int length() const;
		Type front() const;
		Type back() const;
		bool isEmpty() const;
		linkedListIterator<Type> begin();
		linkedListIterator<Type> end();
		void intializeList();
		void copyList(const linkedList<Type>& otherList);
		linkedList();
		~linkedList();
		linkedList(const linkedList<Type>& otherList);
		const linkedList<Type>& operator=(const linkedList<Type>& otherlist);
		bool search(const Type& searchItem) const;
		void insertLast(const Type& newItem);
		void insertFirst(const Type& newItem);
		void deleteNode(const Type& deleteItem);
		void customInsert(const Type& newItem, linkedListIterator<Type>& it);
		void deleteFront();
		void customDelete(linkedListIterator<Type>& it);

	private:
		int count; // to keep track of list size 
		nodeType<Type>* first; // to keep track of front of list
		nodeType<Type>* last; // to keep track of back of list
};


