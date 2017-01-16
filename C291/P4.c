/*Filename: P4.c *
 *Part of: C291 Programs *
 *Created by: Blake Howard *
 *Created on: 10\14\2014 *
 *Last Modified by: Blake Howard *
 *Last Modified on: 10/14/2014 *
 *  
 *  These programs are programs we worked on in class that demonstrate 
 *  The uses of structs in arrays(ex. demofunction()) and linked lists.
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//Creating a struct for a node which will be used later.
struct CELL {
  int number;
  //using a pointer with our struct
  struct CELL *next;
};

//Declaring prototype functions for later use.
void append_node(struct CELL *llist, int num);
void delete_node(struct CELL *llist, int num);
int search_value(struct CELL *llist, int num);
void display_list(struct CELL *llist);
int demo_function();  
void DisplayStats ();

//Declaring a struct for people which will be used later.
//Consists of four fields, first name(char), last name(char), year(int) and ppg(double)
struct person { 
  char first[32]; 
  char last[32]; 
  int year; 
  double ppg; 
}; 

//Declaring a very lengthy main which is the heart of our linked list program and also calls our 
//People structs at the end in a nice list. 
int main(void)
  
{
  //declaring variables
  int num = 0;
  int input = 1;
  int retval = 0;
  struct CELL *llist;
  
  //Here we initialize a list using malloc and that our nodes have a pointer to the next node.
  llist = (struct CELL *)malloc(sizeof(struct CELL));
  llist->number = 0;
  llist->next = NULL;
  //This while loop sets up the menu and allows us to modify nodes 
  while(input != 0) {
    printf("\n-- Menu Selection --\n");
    printf("0) Quit\n");
    printf("1) Insert\n");
    printf("2) Delete\n");
    printf("3) Search\n");
    printf("4) Display\n");
    scanf("%d", &input);
    switch(input) {
      //Allows user to end menu.
    case 0: 
      printf("Goodbye ...\n");
      input = 0;
      break;
      //create a node at the end to inserst a value
    case 1:
      printf("Your choice: 'Insertion'\n");
      printf("Enter the value which should be inserted: ");
      scanf("%d", &num);
      append_node(llist, num);
      break;
      //remove a node to remove a value
    case 2:
      printf("Your choice: 'Deletion'\n");
      printf("Enter the value which should be deleted: ");
      scanf("%d", &num);
      if((retval = search_value(llist, num)) == -1)
	printf("Value '%d' not found\n", num);
      else
	delete_node(llist, num);
      break;
      //Find a node. Tells the user where the node is located or if it can't be found.
    case 3:
      printf("Your choice: 'Search'\n");
      printf("Enter the value you want to find: ");
      scanf("%d", &num);
      if((retval = search_value(llist, num)) == -1)
	printf("Value '%d' not found\n", num);
      else
	printf("Value '%d' located at position '%d'\n", num, retval);
      break;
      //Displaying whats in a specific list
    case 4:
      printf("You choice: 'Display'\n");
      display_list(llist);
      break;
      //Tells user input is invalid and returns to menu
    default:
      printf("That is not a valid menu option\n");
      break;
    } 
  } 
  free(llist); //freeing malloc
  
  //execute our demo function to display stats of people. 
  demo_function();
  //return an int
  return (0);
}

//Actually appending nodes
void append_node(struct CELL *llist, int num) {
  while(llist->next != NULL)
    llist = llist->next;
  //appending to the end of the list by adding a new node
  llist->next = (struct CELL *)malloc(sizeof(struct CELL));
  llist->next->number = num;
  llist->next->next = NULL;
}
//Removing a node. Using a temporary pointer if the node has been found. 
void delete_node(struct CELL *llist, int num) {
  struct CELL *temp;
  temp = (struct CELL *)malloc(sizeof(struct CELL));
  if(llist->number == num) {
    //removing node
    temp = llist->next;
    free(llist); //freeing memory
    llist = temp;
  } else {
    while(llist->next->number != num)
      llist = llist->next;
    temp = llist->next->next;
    free(llist->next); 
    llist->next = temp;
  } 
}
//Searching for a node with a while loop. 
int search_value(struct CELL *llist, int num) {
  int retval = -1;
  int i = 1;
  while(llist->next != NULL) {
    if(llist->next->number == num)
      return i;
    else
      i++;
    llist = llist->next;
  }
  return retval;
}
//Using a while loop to display the list as long as the list isn't empty
void display_list(struct CELL *llist) {
  while(llist->next != NULL) {
    printf("%d ", llist->number);
    llist = llist->next;
  }
  printf("%d", llist->number);
}

//This fucntion creates a stuct array of people structs, populates, and prints them.
int demo_function()
{
  int i;
  struct person class[54]; //creating array of people
  
  //Populating class with a new person
  class[0].year=2004; 
  class[0].ppg=5.2;
  strcpy(class[0].first,"Jane");
  strcpy(class[0].last,"Doe");
  
  //Populating class with a new person
  strcpy(class[1].first,"Brian");
  strcpy(class[1].last,"Smith");
  class[1].year=2005;
  class[1].ppg=4.9;
  
  //Populating class with a new person
  class[2].year=2003; 
  class[2].ppg=9.7;
  strcpy(class[2].first,"Bob");
  strcpy(class[2].last,"Dole");
  
  //Populating class with a new person
  class[3].year=2007; 
  class[3].ppg=6.5;
  strcpy(class[3].first,"GI");
  strcpy(class[3].last,"Jane");
  
  //Populating class with a new person
  class[4].year=2010; 
  class[4].ppg=2.6;
  strcpy(class[4].first,"Oranje");
  strcpy(class[4].last,"Yellow");
  
  //Populating class with a new person
  class[5].year=2009; 
  class[5].ppg=5.8;
  strcpy(class[5].first,"Pete");
  strcpy(class[5].last,"Za");
  
  //Populating class with a new person
  class[6].year=2008; 
  class[6].ppg=6.8;
  strcpy(class[6].first,"Ella");
  strcpy(class[6].last,"Vater");
  
  //Using a while loop to print the elements in class. 
  for (i=0; i<=6; i++)
    {
      DisplayStats(class[i]);
    }
  
}
//This function actually prints the elements inside whatever element of class it was passed. 
void DisplayStats(struct person Input)
{
  // printing name, ppg, and year.
  printf("%s, %s: %lf PPG in %d\n", Input.last, Input.first, Input.ppg, Input.year);
}

//End of program

