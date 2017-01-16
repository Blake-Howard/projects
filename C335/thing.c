
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
  int val;
  struct Node *next;
};

void cons_node(struct Node **head, int num)
{
  struct Node *newNode = malloc(sizeof(struct Node));
  newNode->val = num;
  newNode->next = *head;
  *head = newNode;
 
}


void display_list(struct Node *head)
{
  struct Node *current = head;
  while(current != NULL)
    {
      printf("%d\n", current->val);
      current = current->next;}
  
}

void print_top(struct Node *head)
{
  printf("%d\n", head->val);
}

void clear_stack(struct Node *head)
{
  struct Node *current;
  while ((current = head)!= NULL) {
    head = head->next;
    free(current);
  }
}

int main(){
  
  int input;
  int first = 1;
  char quit = 'n';
  char inputchar[20];
  
  struct Node *head = NULL;
  struct Node *temp;
  
  while (quit == 'n'){
    
    scanf("%s", &inputchar);
    
    if (isdigit(inputchar[0])){
      input = atoi(inputchar);
      cons_node(&head, input);
      first = 0;
    }
    
    else{
      
      if(first == 1){
	printf("List is empty\n");
	if (inputchar[0] = 'q')
	  quit = 'y';
      }
      
      else{
	switch (inputchar[0]){
	case 'q':
	  clear_stack(head);
	  quit = 'y';
	  break;
	case 'E':
	  clear_stack(head);
	  quit = 'y';
	  break;
	case 'f':
	  display_list(head);
	  break;
	case 'p':
	  print_top(head);
	  break;
	case 'c':
	  clear_stack(head);
	  first = 1;
	  free(head);
	  head = NULL;
	  break;
	case 't':
	  temp = head;
	  head = head->next;
	  free(temp);
	  break;
	case '+':
	  head->next->val = head->next->val + head->val;
	  temp = head;
	  head = head->next;
	  free(temp);
	  break;
	case '-':
	  head->next->val -= head ->val;
	  temp = head;
	  head = head->next;
	  free(temp);
	  case '/':
	  head->next->val = head->next->val / head->val;
	  temp = head;
	  head = head->next;
	  free(temp);
	  break;
	  case '*':
	  head->next->val = head->next->val * head->val;
	  temp = head;
	  head = head->next;
	  free(temp);
	  break;
	}
      }
    }
  }
  
  return 0;
}
