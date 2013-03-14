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
  char *duration;
  char *title;
  struct clip *next;
} *head;

int main(int argc, char **argv) {
  build_a_lst(*(argv+1));
  //print_lst(head);    /* prints the table */
  int_radix_sort(head);
  //print_lst(head);    /* prints the table but now sorted */
  return 0;
}

void build_a_lst(char *fn) {
  FILE *fp;
  char line[LINE_LENGTH];
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
      i++; 
  }
  

  struct clip *tp, *cp;

  tp = malloc(sizeof(struct clip));
  
  tp->views = atoi(arr[0]);
  
  tp->user = malloc(strlen(arr[1]));
  strcpy(tp->user, arr[1]);

  tp->duration = malloc(strlen(arr[1]));
  strcpy(tp->duration, arr[2]);
  
  tp->title = malloc(strlen(arr[3]));
  strcpy(tp->title, arr[3]); //need to convert MY_COMMA back to comma

  // free(arr);

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
  int rnd = 0;
  int cnt[9999];
  int map[9999];
  int buf[9999];
  int lst[9999];
  int i = 0;
  int j;
  int c;
  int bucket = 16;
  int mask = bucket - 1;
  // 0 out bucket?

  while(cp->next != NULL){
    lst[i] = cp->views;
    cp = cp->next;
    i = i + 1;
  }

  int n = i;

  for (int i = 0; i < n; ++i)
  { 
    // printf("%x\n", lst[i]);
    // printf("%x\n", (lst[i] >> 4 * rnd & mask));
    // printf("%s\n", "");
  }  
  map[0] = 0;

  for (i = 0; i < n; ++i)
  {
    cnt[(lst[i] >> 4 * rnd) & mask]++;
  }
  
  for (i = 0; i < bucket; i++) {   
    map[i] = map[i-1] + cnt[i-1];
  }

  for (j = 0; j < n; j++)
  {
    buf[map[(lst[j] >> (4 * rnd)) & mask]++] = lst[j];   
  }
  printf("%s\n", "=======");  

  for (c = 0; c < n; c++){
    printf("%x\n", buf[c]);
  }

    

}




/* prints all the users */
void print_lst(struct clip *cp) {
  while(cp->next != NULL){
    cp = cp->next;
    // printf("%s\n", cp->user);
    // printf("%s\n", cp->duration);
    // printf("%s\n", cp->title);
    printf("%i\n", cp->views);
  }
}

/* end */