///library needs  system to keep track of books
///search  for specific book and find info about book
/// add or remove book
/// 
/// 
/// linked list trial
/// 

#include <stdio.h>
#include "book.h"
#include <string.h>
#include <stdlib.h>

/// 
int main() {
	P_BOOK bookList = NULL; // list of books empty 
	bookList = readBooks(bookList);
	bookList = addBook(bookList);
	bookList = removeBook(bookList);
	saveBooks(bookList);
	

	//P_BOOK searchResult = searchTitle(bookList, "random title two");

	//P_BOOK booklist = removeBook(bookList, "random title one");

	return 0;
}

/*
1
author 1
random title one
32
2
author 2
random title 2
42
3
author 3
random title 3
35
*/