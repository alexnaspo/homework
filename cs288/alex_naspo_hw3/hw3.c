#include <stdio.h>
#include <malloc/malloc.h>
#include <string.h>
#include <stdlib.h>

void insert_user(char *s);

struct clip {
 char *user;
 char *duration;
 char *title;
 char *id;
 int views;

 struct clip *next;
};

int main(int argc, char **argv){
  FILE *fp = fopen("users.txt", "r");
  char line[999];
  struct clip *head;
  head = NULL;
  while (fgets(line, sizeof(line), fp)) {
    
    struct clip *tp, *cur;
    char *user;

    tp = malloc(sizeof(struct clip));
    tp->user = malloc(strlen(line));
    strcpy(tp->user, line);

    tp->next = NULL;
    cur = head;

    if(head == NULL){
      head = tp;
    } else {
      while(cur->next != NULL){
        cur = cur->next;
      }
      cur->next = tp;
    }
  }

  struct clip *temp;

  temp = head;
  while(temp->next != NULL){
    printf("%s\n", temp->user);
    temp = temp->next;
  }
  return 0;
}
