/*-------------------------------------------------------------------------------
	This File Contains All Of The Impementation Details for Linked List Functions
---------------------------------------------------------------------------------*/


#include <iostream> // for input output
#include <cassert> // for assert function
#include "linkedList.h" // include the declartions

using namespace std; // so I dont have to type std in front of everythin

template<class Type>
 void linkedList<Type>::print() const // this is the general print function for most data type
{
	 nodeType<Type>* current;
	 current = first;
	 
		 while (current != nullptr)
		 {
			 cout << current->info << endl; // cout the info
			 current = current->link; // advance to next node
		 }
	 
}

 template<class Type>
 int linkedList<Type>::length() const // returns the size 
 {
	 return count; 
 }

 template <class Type>
 bool linkedList<Type>::isEmpty() const
 {
	 return (count == 0);
 }


 template<class Type>
 Type linkedList<Type>::front() const // returns first element in list
 {
	 assert(first != nullptr); // make sure first isnt nullptr this is great for trouble shooting
	 return first->info;
}

 template<class Type>
 Type linkedList<Type>::back() const // same deal at first but with the back of list
 {
	 assert(last != nullptr);
	 return last->info;
 }

 template<class Type>
 linkedListIterator<Type> linkedList<Type>::begin() // returns an iterator at the nack of the list so you can creat iterators and place them at the rear like this temp it = list.begin()
 {
	 linkedListIterator<Type> temp(first);
	 return temp;
 }

 template<class Type>
 linkedListIterator<Type> linkedList<Type>::end() // same thing as begin but with the rear of the list
 {
	 linkedListIterator<Type> temp(nullptr);
	 return temp;
 }

 template<class Type>
 void linkedList<Type>::intializeList() // sets list to an empty state
 {
	 nodeType<Type>* temp;

	 while (first != nullptr)
	 {
		 temp = first; // set temp to first
		 first = first->link; // advance first
		 delete temp; // delete temp which used to be the front
	 }
	 last = nullptr; // update last
	 count = 0; // update count

 }


 template<class Type>
 void linkedList<Type>::copyList(const linkedList<Type>& otherList) // copys list into another
 {
	 nodeType<Type>* newNode; // pointer to newnode
	 nodeType<Type>* current; // pointer to keep track of the current node we are copying

	 if (first != nullptr) // if list is not empty make it empty
	 {
		 intializeList();
	 }
	 if (otherList.first == nullptr) // if other list is empty there is nothing to copy so just set it up to be empty too
	 {
		 first = nullptr;
		 last = nullptr;
		 count = 0;
	 }
	 else
	 {
		 current = otherList.first; // current now equals the front of the other list
		 count = otherList.count; // get count of the other list

		 first = new nodeType<Type>; // create the new first node for the list to be copied too
		 first->info = current->info; // set it equal to current
		 first->link = nullptr; // set link equal to nullptr
		 last = first; // since this is the only one its also the last in the list
		 current = current->link; // advance current

		 while (current != nullptr) // copy rest of list
		 {
			 newNode = new nodeType<Type>; // create new node 
			 newNode->info = current->info;
			 newNode->link = nullptr; // since its at the ned its linked to nothing

			 last->link = newNode; // link it to the last node in this list
			 last = newNode; // update last

			 current = current->link; // advance current
		 }
	 }
 }
	 
 
 template <class Type>
 linkedList<Type>::linkedList() // default construtor
 {
	 first = nullptr;
	 last = nullptr;
	 count = 0;
 }
 
 
 
	template<class Type>
	 linkedList<Type>::~linkedList() // deconstrutor
	 {
		 intializeList();
	 }

	 template<class Type>
	 linkedList<Type>::linkedList(const linkedList<Type>& otherList) // copy construtor
	 {
		 first = nullptr;
		 copyList(otherList);
	 }

	 template<class Type>
	 const linkedList<Type>& linkedList<Type>::operator=(const linkedList<Type>& otherlist) // overload assignment operator and use copy list so we can do this list = otherlist 
	 {
		 if (this != &otherlist)
		 {
			 copyList(otherlist);
		 }
		 return *this;
	 }

	 template<class Type>
	 bool linkedList<Type>::search(const Type& searchItem) const // search for an item its a general function but wont work for structs
	 {
		 nodeType<Type>* current;
		 bool found = false;
		 current = first;

		 while (current != nullptr && !found)
		 {
			 if (current->info == searchItem)
			 {
				 found = true;
			 }
			 else
			 {
				 current = current->link;
			 }
		}
	 
		 if (found)
		 {
			 found = (current->info == searchItem);
		 }
		 return found;
	 }

	 template<class Type>
	 void linkedList<Type>::insertLast(const Type& newItem) // inserts node at the rear of the list
	 {
		 nodeType<Type>* newNode;
		 newNode = new nodeType<Type>;

		 newNode->info = newItem;
		 newNode->link = nullptr;

		 if (first == nullptr) // if list is empty
		 {
			 first = newNode;
			 last = newNode;
			 count++;
		 }
		 else
		 {
			 last->link = newNode;
			 last = newNode;
			 count++;
		 }
	 }

	 template<class Type>
	 void linkedList<Type>::insertFirst(const Type& newItem) // inserts node at the front of the list
	 {
		 nodeType<Type>* newNode;
		 newNode = new nodeType<Type>;

		 newNode->info = newItem;
		 newNode->link = first;
		 first = newNode;
		 count++;

		 if (last == nullptr) // if list is empty
		 {
			 last = newNode;
		 }
	 }
	
	 template<class Type>
	 void linkedList<Type>::deleteNode(const Type& deleteItem) // deletes node from the list 
	 {
		 nodeType<Type>* current; // to keep track of the current node
		 nodeType<Type>* trailCurrent; // this is so we can link the last node before the one to be deleted to the one after the deleted node
		 bool found;

		 if (first == nullptr) // case 1 if list is empty
		 {
			 cout << "Cannot delete from an empty list." << endl;
		 }
	 
		 else
		 {
			 if (first->info == deleteItem) // case 2 if the first item is the one to be deleted
			 {
				 current = first; 
				 first = first->link; // move first
				 count--; // decrement sice

				 if (first == nullptr) // list is now empty
				 {
					 last = nullptr;
				 }
				 delete current; // delete the node
			 }
		 
			 else
			 {
				 found = false;

				 trailCurrent = first; // this is always going to be one behind current
				 current = first->link; // advance current

				 while (current != nullptr && !found) // while list is not empty and we have not found the item to be delted
				 {
					 if (current->info != deleteItem) // if current is not the one
					 {
						 trailCurrent = current;
						 current = current->link;
					 }
				 
					 else
					 {
						 found = true;
					 }
				 }
			 
				 if (found) // case 3 when we find it
				 {
					 trailCurrent->link = current->link; // connect trailcurrent to the node that was after current
					 count--;

					 if (last == current) // if we are delteing the last node
					 {
						 last = trailCurrent;
					 }
					 delete current; // delete node
				 }
				 else // if nothing else it was not in the list
				 {
					 cout << "The Item to be deleted is not in the list." << endl;
				 }
			 }
		 }
	 }

	 template<class Type>
	 void linkedList<Type>::customInsert(const Type& newItem, linkedListIterator<Type>& it) // using an iterator this allows us to insert a node before the node the it is pointing at
	 {
		 nodeType<Type>* newNode;
		 newNode = new nodeType<Type>;

		 newNode->info = newItem; // create and setup the newItems node
		 newNode->link = nullptr;
		 if (it.current == first) // if it was the first one just use insert first
		 {
			 insertFirst(newItem);
		 }

		 else if (it.current == nullptr ) // if it was last just use insert last
		 {
			 insertLast(newItem);
		 }
	 
		 else
		 {
			 it.lastCurrent->link = newNode; // literally same premise as delete exept we are connecting it in between lastcurrent which is one beind current
			 newNode->link = it.current; 
			 count++; // increment the size
		 }	 
	 }


	 template <class Type>
	 void linkedList<Type>::customDelete(linkedListIterator<Type>& it) // allows us to delete any item in the list
	 {
		 if (it.current == first) // if its the first one just use delete front
		 {
			 deleteFront();
		 }

		 else if (it.current == last) // if we are deleted the last node
		 {
			 nodeType<Type>* temp;
			 temp = it.current;
			 it.lastCurrent->link = nullptr; // since lastcurrent is now the last in the list we cut off the link to the one we are going to delete 
			 last = it.lastCurrent; // update last
			 delete temp;
			 count--;
		 }
		 
		 else if (it.current == nullptr) // if it equals nothing 
		 {
			 cout << "Item to be deleted is not found" << endl;
		 }
		 else // if its somewher in the middle
		 {
			 nodeType<Type>* temp; // pointer temp
			 temp = it.current;
			 it.lastCurrent->link = it.current->link; // update the previous nodes link to skip the node that is being delted
			 delete temp;
			 count--;
		 }
	 }


	 template<class Type>
	 void linkedList<Type>::deleteFront() // delete the front element of the list
	 {
		 nodeType<Type>* temp;
		 temp = first;

		 if (first == nullptr)
		 {
			 cout << "Cannot Delete from empty list" << endl;
		 }
	 
		 
		 else
		 {
			 first = first->link; // move first to the next node
			 count--;

			 if (first == nullptr) // if the list is now empty
			 {
				 last = nullptr;
			 }
			 delete temp;
		 }
	 }