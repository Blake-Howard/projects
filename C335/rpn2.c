#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CELL {
  int val;
  struct CELL *next;
};

struct LinkedList {
	struct CELL *head;
};

void append_node(struct LinkedList *llist, int num);
void display_list(struct LinkedList *llist);

int main(void)
{
  
  int num = 0;
  int first = 0;
  int input = 0;
  char quit = 'n';
  char inputchar = ' ';
  
  struct LinkedList *head;
  
  head = (struct CELL *)malloc(sizeof(struct CELL));
  head->next = NULL;

  while (quit == 'n'){
    
    if (scanf("%d", &input) == 1){
            
      if ( first == 1 )
	append_node(llist, input);
      
      
      if ( first == 0){
	llist->val = input;
	first = 1;
      }
    }
    
    else{
      inputchar = getchar();
      
      if (llist->next == NULL && first == 0)
	printf("List is empty.\n");
      
      if (inputchar == 'f')
	display_list(llist);
      
      if (inputchar == 'q')
	quit = 'y';
      else if (llist->next != NULL){
	switch (inputchar){
	  
	case 'q':
	  quit = 'y';
	  break;
	}
      }
    }
    
    
  }
  free(llist);
  return 0;
}

void append_node(struct LinkedList *llist, int num) {
  /*while(llist->next != NULL)
     llist = llist->next;
  llist->next = (struct LinkedList *)malloc(sizeof(struct LinkedList));
  llist->next->val = num;
  llist->next->next = NULL;*/

  struct LinkedList *temp;
  temp = (struct LinkedList *)malloc(sizeof(struct LinkedList));
  temp->val = num;
  temp->next = llist;
  llist = temp;
}

void display_list(struct LinkedList *llist)
{
  while(llist->next != NULL) {
    printf("%d\n", llist->val);
    llist = llist->next;
  }
  printf("%d\n", llist->val);
}
