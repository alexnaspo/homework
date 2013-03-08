#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 100

void build_a_lst(),print_a_line(),print_lst();
void insert_at_end();
void int_radix_sort();

struct clip {
  int views;
  char *user;
  char *id;
  char *title;
  struct clip *next;
} *head;

int main(int argc, char **argv) {
  build_a_lst(*(argv+1));
  print_lst(head);    /* prints the table */
  // int_radix_sort(head);
  // print_lst(head);    /* prints the table but now sorted */
  return 0;
}

void build_a_lst(char *fn) {
  FILE *fp;
  char line[LINE_LENGTH];
  //  char *line;
  if ((fp = fopen(fn,"r")) != NULL) {
    while (fgets(line, LINE_LENGTH, fp) != NULL) {
      insert_at_end(line);  /* insert a user at end of the list */
    }
    fclose (fp);
  }
}

void insert_at_end(char *s) {
  // split s into four fields and insert all of them
  // views need to be converted to int using atoi(views_str)
  //create clip

  char delims[] = ",";
  char *result;
  char *arr[4];
  result = strtok( s, delims );
  int i = 0;
  while( result != NULL ) {
      arr[i] = result;
      result = strtok( NULL, delims );
      // printf("%s\n", arr[i]);
      // printf("%s\n", "---------------");
      i++; 
  }

  struct clip *tp, *cp;

  tp = malloc(sizeof(struct clip));

  tp->views = (int)arr[0];

  tp->user = malloc(strlen(arr[1]));
  strcpy(tp->user, arr[1]);
  
  tp->title = malloc(strlen(arr[3]));
  strcpy(tp->title, arr[3]);

  tp->next = NULL;

  //traverse and add
  cp = head;
  if(head == NULL){
    head = tp;
  } else {
    while(cp->next != NULL){
      cp = cp->next;
    }
    cp->next = tp;
  }  


}

void int_radix_sort(struct clip *cp) {
  /*
    you will need a wrapper here for radix_sort only, without having to involve
    struct clip or linked list
  */
  // we'll talk more on this on Thur, 3/7/2013
  // FILL IN
  // ...
  // FILL IN
}


/* prints all the users */
void print_lst(struct clip *cp) {
  while(cp->next != NULL){
    cp = cp->next;
    printf("%s\n", cp->user);
  }
}

/* end */