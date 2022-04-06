// ------------------------------------------- Main.cpp --------------------------------------------------//

#pragma warning (disable : 4996) // this is so I can use ctime without getting warnings
#include <fstream> // this is for infile and outfile
#include <ctime> // this is to get the time
#include <string> // this is so I can use getline() for sentences
#include <filesystem> // this is so I can use the file_size function
#include "linkedList.h" // file where to declaration of the linkedList and its functions are
#include "linkedList.cpp" // where the implementation details of linkedList functions are

struct bookInfo // This struct will allow us to hold all of our information in a single container
{
	string author;
	string title;
	string publisher;
	string description;
	int ISBN;
	int yearPublished;

	friend istream& operator>>(istream& is, bookInfo& input) // This is so i can read in structs from a text file 
	{
		is >> ws; // ignore whitespace
		getline(is, input.author); // inputs ------
		getline(is, input.title);
		getline(is, input.publisher);
		getline(is, input.description);
		is >> input.ISBN;
		is >> input.yearPublished;
		return is; // the << and >> require you return the input stream

	}

	friend ostream& operator<<(ostream& is, bookInfo& output) // this is overlaoding and it makes it much easier to read out and print out the struct.
	{
		is << output.author << endl;
		is << output.title << endl;
		is << output.publisher << endl;
		is << output.description << endl;
		is << output.ISBN << endl;
		is << output.yearPublished << endl;
		cout << endl;
		return is;

	}

	friend iostream& operator<< (iostream& os, bookInfo& output)
	{
		os << output.author << endl;
		os << output.title << endl;
		os << output.publisher << endl;
		os << output.description << endl;
		os << output.ISBN << endl;
		os << output.yearPublished << endl;
		cout << endl;
		return os;
	}

};


linkedList<bookInfo> bookList; // linked list that will hold the books
linkedListIterator<bookInfo> it; // iterator which is a pointer that makes tranversing the list easy

void sort(linkedList<bookInfo>& unsortedList); // functions for the program declared up here because it looks neater
void printAll(linkedList<bookInfo> tempList);
void addBook(); 
void removeBook(int isbn);
void removeAll();
int displayMenu();
void printTime();
void searchByAuthor(linkedList<bookInfo> &tempList, string author);
void searchByTitle(linkedList<bookInfo> tempList, string title);
void searchByISBN(linkedList<bookInfo> tempList, int isbn);

namespace fs = std::filesystem; // makes using file_size easier and more readable





int main() // start of execution
{
	fstream newfile; // create new file stream object
	if (fs::file_size("bookList") != 0) // if the text file is not empty
	{

		newfile.open("bookList", ios::in); // open the text file and we are going to be reading in
		if (!newfile.is_open()) // check if file was open
		{
			"Cannot open file requested";
		}
		else {

			bookInfo temp; // temp struct to hold info for insertion
			while (newfile >> temp) // while we are still reading in 
			{
				bookList.insertLast(temp); // insert into linked list
			}
		}
		newfile.close(); // close file
	}
	sort(bookList); // sort the linked list
	displayMenu(); // display the menu which is recursive so we only need to call it once
}
	
/* ------------------------------------------------------------
			Start of function Implementation
--------------------------------------------------------------*/
	

void sort(linkedList<bookInfo>& unsortedList) // sorts the books by author name alphabetically
{
	if (fs::file_size("bookList") != 0) // if text file is not empty
	{

		if (unsortedList.length() != 0) // if the unsorted list is not empty make it empty since the list may be deleted and re read in we need it to be empty
		{
			unsortedList.intializeList();
		}

		fstream newfile;

		newfile.open("bookList", ios::in); // open file to be read in
		if (!newfile.is_open()) // if the file didnt open cout error
		{
			"Cannot open file requested";
		}
		else {

			bookInfo temp; // same function used above just reads in from the text file

			while (newfile >> temp) // while we are still reading in actual data and not empty space
			{
				bookList.insertLast(temp);
			}
		}
		newfile.close(); //close the file




		linkedList<bookInfo> sortedList; // create the empty list which we will place sorted items into
		bookInfo unSortedFront = unsortedList.front(); // get the first node of the unsorted list
		sortedList.insertFirst(unSortedFront); // place it into the sorted list since its the only one so far its technically sorted
		unsortedList.deleteFront(); // delete that node from the unsorted list

		while (unsortedList.length() != 0) // while unsorted is not empty
		{
			unSortedFront = unsortedList.front(); // get the next node of the unsorted list
			linkedListIterator<bookInfo> it = sortedList.begin(); // create and iterator and place it at the front of the sortlist so we can compare and determine where the node from unsorted goes

			if (sortedList.length() == 1) //  if there is only one element in sorted list
			{
				if (unSortedFront.author < sortedList.front().author) // if the unsorted node is less than the one and only sorted node 
				{
					sortedList.insertFirst(unSortedFront); // place it in front of it
				}

				else
				{
					sortedList.insertLast(unSortedFront); // if not put it behind it
				}
				unsortedList.deleteFront(); // delete the node from unsorted list
			}
			
			else // if theres more than just one in sorted list
			{
				bool foundSpot = false; // flag so we can stop the loop when we find the correct place
				for (int x = 0; x < sortedList.length() && !foundSpot; x++) // iterate through the list until we found the correct spot
				{
					bookInfo sortedListCurrent = *it; // temp struct which will equal the info of whater it is pointing at
					if (unSortedFront.author < sortedListCurrent.author)  // if the unsorted node is less than the current sorted node which it is pointing at
					{

						if (x == 0) // if this is the first pass which would indicate that we are comparing against the first item in the sorted list
						{
							sortedList.insertFirst(unSortedFront); // put it in the front of the list
							unsortedList.deleteFront(); // delete that node from unsorted
							foundSpot = true; // exit from for loop
						}

						else
						{
							foundSpot = true; // exit from for loop
							sortedList.customInsert(unSortedFront, it); // use the custom insert function which will insert before the place it is pointing at
							unsortedList.deleteFront();
						}
					}

					else if (x == sortedList.length() - 1 && unSortedFront.author >= sortedListCurrent.author) // if the unsorted node is being compared to the last node in sorted and is greater than it
					{
						sortedList.insertLast(unSortedFront); // insert it at the end of sorted
						foundSpot = true; // exit from for loop
						unsortedList.deleteFront();
					}

					else if (unSortedFront.author == sortedListCurrent.author) // if the two book have the same author
					{
						if (it == sortedList.begin()) // honesty not even sure if this line works but im scared to delete it because the iterator comparionsions are spotted
						{
							sortedList.insertFirst(unSortedFront);
							unsortedList.deleteFront();
							foundSpot = true;
						}

						else // if its not at the beggining then just place the book with the same author in front of the other book
						{
							foundSpot = true;
							sortedList.customInsert(unSortedFront, it);
							unsortedList.deleteFront();
						}
					}
					else
					{
						it.operator++(); // increment it to go to the next node for comparision
					}
				}
			}
		}

		unsortedList = sortedList; // recopy this sorted list into the orginal
	}
	else // if the list was empty there is nothing to sort
		{
		cout << "No Data....." << endl;
		}
}

void removeBook(int isbn) // removes the book with the entered isbn number
{
	if (bookList.length() == 0) // if the list is empty
	{
		cout << "Cannot delete from an empty list" << endl;
	}
	linkedListIterator<bookInfo> it = bookList.begin(); // pointer to transverse the list starting at the front
	bool found = false; // flag so we can stop the loop
	for (int x = 0; x < bookList.length() && found == false; x++) // go through entire list
	{
		bookInfo temp = *it; // temp struct so we can check the current nodes isbn
		if (temp.ISBN == isbn) // if t4mp is the one
		{
			bookList.customDelete(it); // delete the node to which it is pointing to 
			found = true; // stop loop
		}
		else if (x == bookList.length() - 1 && temp.ISBN != isbn) // if we went through the entire list
		{
			cout << "Book with the entered ISBN is not in the list" << endl;
		}

		else
		{
			it.operator++(); // move to next node in list
		}
		cout << "Ran...." << endl;
	}
	
	fstream f;
	
	f.open("bookList", ios::out); // rewriting the entire list to the text file which will remove it now since its not in the list
	if (!f.is_open())
	{
		cout << "Cannot open requested file." << endl;
	}
	else
	{
		linkedListIterator<bookInfo> t = bookList.begin();
		linkedList<bookInfo> test;
		for (int x = 0; x < bookList.length(); x++)
		{
			bookInfo test = *t;

			f << test << endl;

			t.operator++();
		}
		f.close();
	}
}

void addBook() // adds book to the list
{
	bookInfo temp; // temp node to hold info
	cout << "Author? ";
	cin.ignore(); // so we dont get caught lacking with the input buffer not being clear
	getline(cin, temp.author); // we use getline in these statement so we can get senteces and mutiple words
	cout << "Title? ";
	getline(cin, temp.title);
	cout << "Publisher? ";
	getline(cin, temp.publisher);
	cout << "Description? ";
	getline(cin, temp.description);
	cout << "ISBN? ";
	cin >> temp.ISBN;
	cout << "Year Published? ";
	cin >> temp.yearPublished;

	bookList.insertLast(temp); // put temp at the end of the list
	
	fstream f;
	f.open("bookList", ios::app); // open the text file in append mode which will just tack temp onto the end of it
	if (!f.is_open())
	{
		cout << "Cannot open requested file" << endl;
	}
	else
	{
		f << temp;
		f.close();
	}
	
}

void removeAll() // deletes the entire list
{
	bookList.intializeList();
	cout << "List has been deleted" << endl;
}

void printAll(linkedList<bookInfo> tempList) // prints entire list
{
	if (tempList.length() == 0)
	{
		cout << "List is Empty." << endl;
	}
	
	else
	{
		linkedListIterator<bookInfo> t = tempList.begin();
		t = tempList.begin();
		for (int x = 0; x < tempList.length(); x++)
		{
			bookInfo test = *t; // set a temp struct equal to the info which it is currently pointing 

			cout << test.author << endl; // could have overloaded the  << cout operator to condense this into one line
			cout << test.title << endl;
			cout << test.publisher << endl;
			cout << test.description << endl;
			cout << test.ISBN << endl;
			cout << test.yearPublished << endl;
			cout << endl;

			t.operator++();
		}
	}
}


int displayMenu() // recursive display menu
{
	int input;
	cout << "-------------Welcome--------------" << " " << "Today's Date: ";
	printTime(); // cout todays date
	cout << "Select from one of the options below." << endl;
	cout << endl;
	cout << "1. Add New Book." << endl;
	cout << "2. Remove Book." << endl;
	cout << "3. Remove All." << endl;
	cout << "4. Sort." << endl;
	cout << "5. Search By Author." << endl;
	cout << "6. Search By Title." << endl;
	cout << "7. Search By ISBN." << endl;
	cout << "8 Print All." << endl;
	cout << "9. Exit." << endl;
	cout << endl;
	cin >> input; // get which option was selected
	cout << endl;

	string author;
	string title;
	int isbn;

	
	switch (input) // just a switch case that calls displays menu in every option but the exit option of course
	{
	case 1:
		addBook();
		cout << endl;
		displayMenu();
		break; // remeber to use break lines
	case 2:
		cout << "Please enter the ISBN of the book to be deleted: ";
		cin >> isbn;
		removeBook(isbn);
		cout << endl;
		displayMenu();
		break;
	case 3:
		removeAll();
		cout << endl;
		displayMenu();
		break;
	case 4:
		sort(bookList);
		cout << endl;
		displayMenu();
		break;
	case 5:
		cout << "Authors Name? ";
		cin.ignore();
		getline(cin, author);
		searchByAuthor(bookList, author);
		displayMenu();
		break;
	case 6:
		cout << "Book Title? ";
		cin.ignore();
		getline(cin, title);
		searchByTitle(bookList, title);
		displayMenu();
		break;
	case 7:
		cout << "Book ISBN? ";
		cin >> isbn;
		searchByISBN(bookList, isbn);
		displayMenu();
		break;
	case 8:
		printAll(bookList);
		cout << endl;
		displayMenu();
		break;
	case 9:
		cout << "Exiting......";
		return 0;
		break;
	}
}

void searchByAuthor(linkedList<bookInfo>& tempList, string author) // trying to be more modular so this function searches by author adn takes a string and a linked list as values, we could do refernces but in this small of an application i dont think it will matter
{
	if (tempList.length() == 0) // if the list is empty
	{
		cout << "List is empty." << endl;
		cout << endl;
	}
	linkedList<bookInfo> foundBooks; // since the author may have written mutiple books we are going to search the entire list and store the authors books in here
	linkedListIterator<bookInfo> it = tempList.begin(); // pointer to transverse the list starting at the front
	for (int x = 0; x < tempList.length(); x++) // go through entire list
	{
		bookInfo temp = *it; // temp struct so we can check the current nodes author
		if (temp.author == author) // if temp is the one
		{
			foundBooks.insertLast(temp); // add temp to the list which we are going to print
		}

		it.operator++(); // move to next node in list
	}

	if (foundBooks.length() == 0) // if the list is empty we didnt found any books
	{
		cout << "No books written by " << author << " were found." << endl;
	}
	else
	{
		cout << "List of books written by " << author << " :" << endl;
		cout << endl;
		printAll(foundBooks); // print out the list of found books
	}


}





void searchByTitle(linkedList<bookInfo> tempList, string title) // again trying to be more modular this functions searches the list for the books title
{
	if (tempList.length() == 0) // if list is empty
	{
		cout << "List is empty." << endl;
		cout << endl;
	}

	linkedList<bookInfo> foundBooks; // since there may be more than one book with the same name we are going to store all the results in this list and then print it.
	linkedListIterator<bookInfo> it = tempList.begin(); // iterator to tranverse the list .begin() places it at the beginning
	for (int x = 0; x < tempList.length(); x++) // search through the entire list
	{
		bookInfo temp = *it; // temp struct set to the derefernced pointer which is its information
		if (temp.title == title) // if temps title is the one
		{
			foundBooks.insertLast(temp); // insert it into the list we are going to print
		}

		it.operator++(); // move the iterator
	}

	if (foundBooks.length() == 0) // if the list is empty we didnt find any matching elements
	{
		cout << "No books titled " << title << " were found." << endl;
	}
	else
	{
		cout << "List of books titled " << title << " :" << endl;
		cout << endl;
		printAll(foundBooks); // print all of the found items
	}

}



void searchByISBN(linkedList<bookInfo> tempList, int isbn) //again trying to be more modular this function searches the list by the isbn takes basically the same foundation as the delete book function
{
	if (tempList.length() == 0) // if list is empty 
	{
		cout << "List is empty." << endl;
		cout << endl;
	}
	linkedListIterator<bookInfo> it = tempList.begin(); // pointer to transverse the list .begin() sets it to point to the front element 
	bookInfo temp; // temp struct so we can make comparisons
	bool found = false; // flag to escape the loop once we have found the element 
	for (int x = 0; x < tempList.length() && found == false; x++) // go through the entire list or untill we have found the element
	{
		temp = *it; // dereferenced iterator se it returns the info and sets it to the temp struct
		if (temp.ISBN == isbn) // if temp equals the search element
		{
			found = true; // we found it yay stop the search
			cout << "Book found! Details below." << endl;
			cout << endl;
			cout << temp << endl; // display out the details
		}

		else if (x == tempList.length() - 1 && temp.ISBN != isbn) // if we reach the end of the list and the last item just aint it 
		{
			cout << "No books with the ISBN " << isbn << " were found." << endl;
			cout << endl;
		}
		
		else
		{
			it.operator++(); // if niether of the above operations are true the we can move onto the next element in the list
		}
	}
}





void printTime() {
	std::time_t t = std::time(0);   // get time now
	std::tm* now = std::localtime(&t);
	std::cout << (now->tm_year + 1900) << '-' // formating for more readablity
		<< (now->tm_mon + 1) << '-'
		<< now->tm_mday
		<< "\n";
}