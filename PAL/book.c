// this was created after .h

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "book.h"
#include <string.h>
#include <stdlib.h>

P_BOOK createBook(double ISBN, char bookAuthor[], char bookTitle[], int volumeNumber) {

	P_BOOK newBook = (P_BOOK)malloc(sizeof(BOOK)); // holding this in the heap
	//(pointer of books) (variable newbook) = (struct of Pointerbooks)(malloc-returns void pointer)(size of books array)
	newBook->ISBN = ISBN;
	strcpy(newBook->bookAuthor, bookAuthor);
	strcpy(newBook->bookTitle, bookTitle);
	newBook->volumeNumber = volumeNumber;

	newBook->next = NULL;
	newBook->prev = NULL;

	return newBook;

}
P_BOOK searchISBN(P_BOOK listOfBooks, int ISBN)
{
	if (listOfBooks == NULL) { // have no book?
		return NULL;
	}
	if (listOfBooks->next == NULL) { // have only one book? ( next book is not there- so cant search for name)
		if (listOfBooks->ISBN == ISBN) { // is the one book the one we want

			return listOfBooks;
		}
		else {
			return NULL;

		}
	}

	P_BOOK currentBook = listOfBooks;
	while (currentBook->next != NULL) {
		if (currentBook->ISBN == ISBN) {

			return currentBook;
		}
		else {
			currentBook = currentBook->next;
			// list of books = list of book->next;
		}

	}

	return NULL;

}

P_BOOK removeBook(P_BOOK bookList) {

	int ISBN = 0;
	printf("Please enter ISBN of book to remove: ");
	scanf_s("%d", &ISBN);
	P_BOOK bookToRemove = searchISBN(bookList, ISBN);

	if (bookToRemove == NULL) {
		return bookList;
	}

	if (bookToRemove->prev == NULL) {
		bookList = bookList->next;
		bookList->prev = NULL;
	}
	else {
		bookToRemove->prev->next = bookToRemove->next;
		bookToRemove->next->prev = bookToRemove->prev;
	}
	free(bookToRemove);

	return bookList;
}

P_BOOK addBook(P_BOOK listofBooks)
{
	char ISBN[MAXLEN];
	char bookAuthor[MAXLEN];
	char bookTitle[MAXLEN];
	char volNum[MAXLEN];
	int trueISBN;
	int trueVolNum;
	printf("Please insert ISBN:\n");
	fgets(ISBN, MAXLEN, stdin);
	trueISBN = atoi(ISBN);
	printf("Input Author name:\n");
	fgets(bookAuthor, MAXLEN, stdin);
	bookAuthor[strlen(bookAuthor) - 1] = '\0';
	printf("Input Book Title:\n");
	fgets(bookTitle, MAXLEN, stdin);
	bookTitle[strlen(bookTitle) - 1] = '\0';
	printf("Input volume number:\n");
	fgets(volNum, MAXLEN, stdin);
	trueVolNum = atoi(volNum);

	P_BOOK aBook = createBook((double)trueISBN, bookAuthor, bookTitle, trueVolNum);
	listofBooks = updateList(listofBooks, aBook);



	return listofBooks;
}

P_BOOK updateList(P_BOOK bookList, P_BOOK nextBook) { // pointing to an empty list

	if (bookList == NULL) { // have one book?
		bookList = nextBook;
	}
	else {
		P_BOOK currentBook = bookList;
		P_BOOK prevBook = bookList->prev;
		while (currentBook->next != NULL) {
			// || currentBook->next->ISBN >= nextBook->ISBN (This is for sorting. 2 be used next session.
			currentBook = currentBook->next;
		}
		prevBook = currentBook;
		currentBook->next = nextBook;
		nextBook->prev = prevBook;
	}

	return bookList;
}

P_BOOK searchTitle(P_BOOK listOfBooks, char bookTitle[])
{
	if (listOfBooks == NULL) { // have one book?
		return NULL;
	}
	if (listOfBooks->next == NULL) { // have only one book? ( next book is not there- so cant search for name)
		if (strcmp(listOfBooks->bookTitle, bookTitle) == 1) { // is the one book the one we want

			return listOfBooks;
		}
		else {
			return NULL;

		}
	}

	P_BOOK currentBook = listOfBooks;
	while (currentBook->next != NULL) {
		if (!strcmp(currentBook->bookTitle, bookTitle)) {

			return currentBook;
		}
		else {
			currentBook = currentBook->next;
			// list of books = list of book->next;
		}

	}

	return NULL;

}

void saveBooks(P_BOOK listofBooks)
{
	FILE* fp;
	fp = fopen("bookList.txt", "w+");
	P_BOOK currentBook = listofBooks;
	while (currentBook != NULL)
	{
		fprintf(fp, "%d\n", currentBook->ISBN);
		fprintf(fp, "%s\n", currentBook->bookAuthor);
		fprintf(fp, "%s\n", currentBook->bookTitle);
		fprintf(fp, "%d\n", currentBook->volumeNumber);
		currentBook = currentBook->next;
	}
	fclose(fp);
}

P_BOOK readBooks(P_BOOK listofBooks)
{
	FILE* fp;
	fp = fopen("bookList.txt", "r");
	char tempISBN[MAXLEN];
	char tempBOOKAUTHOR[MAXLEN];
	
	char tempBOOKTITLE[MAXLEN];
	char tempVOLNUM[MAXLEN];
	int trueISBN;
	int trueVOLNUM;
	P_BOOK tempBOOK;

	while (fgets(tempISBN, MAXLEN, fp) != NULL)
	{
		trueISBN = atoi(tempISBN);
		fgets(tempBOOKAUTHOR, MAXLEN, fp);
		tempBOOKAUTHOR[strlen(tempBOOKAUTHOR) - 1] = '\0';
		fgets(tempBOOKTITLE, MAXLEN, fp);
		tempBOOKTITLE[strlen(tempBOOKTITLE) - 1] = '\0';
		fgets(tempVOLNUM, MAXLEN, fp);
		trueVOLNUM = atoi(tempVOLNUM);
		tempBOOK = createBook((double)trueISBN, tempBOOKAUTHOR, tempBOOKTITLE, trueVOLNUM);
		listofBooks = updateList(listofBooks, tempBOOK);
	}
	fclose(fp);

	return listofBooks;
}



