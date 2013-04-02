#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define LINE_LENGTH 100

void build_a_lst(),print_a_line(),print_lst();
void insert_at_end();
void int_radix_sort();
void radix_wrapper();

struct clip {
  int views;
  char *user;
  char *duration;
  char *title;
  struct clip *next;
} *head;

int main(int argc, char **argv) {
  build_a_lst(*(argv+1));
  print_lst(head);    /* prints the table */
  int_radix_sort(head);
  printf("%s\n", "=====SORT=====");
  print_lst(head);    /* prints the table but now sorted */
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

  tp->duration = malloc(strlen(arr[2]));
  strcpy(tp->duration, arr[2]);
  
  tp->title = malloc(strlen(arr[3]));
  strcpy(tp->title, arr[3]); //need to convert MY_COMMA back to comma

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
  struct clip *dest[9999];
  struct clip *source[9999];
  int i = 0;
  int flag = 0;
  int rnd = 0;
  i = 1;

  source[0] = cp;
  while(cp->next != NULL){
    cp = cp->next;
    source[i] = cp;
    i = i + 1;
  }
  source[i] = cp;

  int n = i;

  while (rnd < n - 1 ){
    if (flag == 0) {
      radix_wrapper(source, dest, n, rnd);
      flag = 1;  
    } else {
      radix_wrapper(dest, source, n, rnd);
      flag = 0;
    }  
    rnd = rnd + 1;
  }

  // re-link clips
  head = source[0];
  cp = head;
  for ( i = 1; i <= n; i++)
  {
    cp->next = source[i];
    if (i == n)
      cp->next = NULL;
    else
      cp = cp->next;  
  }
}

void radix_wrapper(struct clip *source[], struct clip *dest[], int n, int rnd){
  int i;
  int cnt[9999];
  int map[9999];
  int bucket = 256;
  int mask = bucket - 1;

  for (i = 0; i < bucket; ++i)
  { 
    map[i] = 0;
    cnt[i] = 0;
  }

  for (i = 0; i < n; i++)
  {
    cnt[(source[i]->views >> 8 * rnd) & mask]++;
  }

  for (i = 1; i < bucket; i++) {   
    map[i] = map[i-1] + cnt[i-1];
  }  

  for (i = 0; i < n; i++) {
    dest[map[(source[i]->views >> (8 * rnd)) & mask]++] = source[i];  
  }
}
/* prints all the users */
void print_lst(struct clip *cp) {
  printf("%i\n", cp->views);
  while(cp->next != NULL){
    cp = cp->next;
    printf("%i\n", cp->views);
    printf("%s\n", cp->user);
    printf("%s\n", cp->duration);
    printf("%s\n", cp->title);
    printf("%s\n", "============");
    
  }
}
/* end */