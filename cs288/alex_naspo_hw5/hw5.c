#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc/malloc.h>

#define LINE_LENGTH 200
#define MAX_CLIPS 100
void print_a_line(),print_a_clip(),print_a_lst(),print_lsts(), print_final_list();
void split_line();

void build_lsts();
void int_radix_sort();
void sort_lsts();
struct clip *insert_at_end();
struct clip *build_a_lst();

struct clip *hourly[MAX_CLIPS];

struct clip {
  int number;
  int views;
  char *user;
  char *id;
  char *title;
  char *time;
  struct clip *next;
};

int main(int argc, char **argv) {
  char filename[LINE_LENGTH];
  build_lsts(*(argv+1));  /* filename prefix */
  print_lsts(hourly);
  printf("%s\n", "=======SORT=========");
  sort_lsts(); /* sort hourly in descending order of views */
  print_lsts(hourly);
  printf("%s\n", "=======END SORT=========");
  printf("%s\n", "=======PRINT FINAL LIST=========");
  print_final_list(hourly);
  printf("%s\n", "=======PRINT FINAL LIST=========");
  return 0;
}

void sort_lsts() {
  struct clip *cp, *tp;
  struct clip *source[256];
  struct clip *dest[256];
  int flag, n, i, j;
  for ( j = 0; j < 60; ++j)
  {
    flag = 0;
    i=0;
    cp = hourly[j];
    
    while(cp->next != NULL){
      source[i] = cp;
      cp = cp->next;
      i++;
    }
    
    for(n = 0; n < 4; n++){
      if(n % 2 == 0){
        int_radix_sort(n,i, source, dest);
      } else {
        int_radix_sort(n,i, dest, source);
      }
    }

    // re-link clips
    int k;
    cp = source[i -1];
    hourly[j] = cp;
    for (k = i - 2; k >= 0; k--)
    { 
      cp->next = source[k];
      if(k == 0)
        cp->next = NULL;
      else
        cp = cp->next;
    }
  }

  n = 60;

  for(i=0; i < 4; i++){
    if (i % 2 == 0){
      int_radix_sort(i,n, hourly, dest);  
    } else {
      int_radix_sort(i,n, dest, hourly);  
    }
    
  }
  
  /* 
     sort individual lists in descending order of views
     such that the first clip in each list will have the highest views
     this one is the same as HW4


     once you are done sorting individual lists, sort the entire array
     this one is again the same as HW4 except now that you use values from the first clip of each list

  */
}

void int_radix_sort(int byte, int n, struct clip *source[], struct clip *dest[]){
  int cnt[256];
  int map[256];
  int i;
  memset(cnt, 0, sizeof(cnt));
  map[0]=0;

  for (i = 0; i < n; i++)
  {
    cnt[((source[i]->views) >> (8 * byte)) & 255]++;
  }

  for (i = 1; i < 256; i++) {   
    map[i] = map[i-1] + cnt[i-1];
  }  

  for (i = 0; i < n; i++) {
    dest[map[((source[i]->views)>> (8 * byte)) & 255]++] = source[i];  
  }  
}

/* use print_a_lst(struct clip *cp); */
void print_lsts(struct clip **lst) {
  int i;
  for (i = 0; i < 60; ++i)
  {
    print_a_lst(lst[i]);
  }
}

/* prefix can be such as: index-2013-03-01-12 
  the directory will have 60 files with the above prefix */
void build_lsts(char *prefix) {

  FILE *fp;
  char *cmd;
  char *filename;
  int i;

  for (i=0;i<MAX_CLIPS;i++) hourly[i] = NULL;

  cmd = malloc(10);
  filename = malloc(strlen("index-2013-03-01-12"));
  sprintf(cmd,"ls %s*",prefix);

  fp = popen(cmd,"r"); 

  /* read output from command */
  i=0;
  while (fscanf(fp,"%s",filename) == 1) {
    hourly[i] = build_a_lst(filename);
    i++;
  }
  fclose(fp);
}

/* open the file, read one line at a time, split and insert */
struct clip *build_a_lst(char *fn) {
  FILE *fp;
  struct clip *hp, *cp;
  char *fields[5];
  char line[LINE_LENGTH];
  int cnt=0;
  hp=NULL;

  if ((fp = fopen(fn,"r")) != NULL) {
    while (fgets(line, LINE_LENGTH, fp) != NULL) {
      split_line(&fields, line);
      hp = insert_at_end(hp, fields);  /* insert a user at end of the list */
    }
    fclose (fp);
  }

  // open fn
  // while no more lines
  // read a line
  // split the line into five substrings and store them in fields
  // insert at the end of the list
  // return the head pointer holding the list

  return hp;
}

/* fields will have five values stored */
void split_line(char **fields,char *line) {
  int i=0;
  char *token, *delim;
  delim = ",";
  /* 
     call strtok(line, delim);
     malloc and strcpy token to fields

     repeat until strtok returns NULL using strtok(NULL, delim);
     each time you get token, malloc and strcpy to fields
  */  
  token = strtok(line,delim);
  while( token != NULL ) {
      fields[i] = malloc(strlen(token));
      strcpy(fields[i], token);
      token = strtok( NULL, delim );
      i++;
  }
}

/* set the five values into a clip
   insert a clip at the of the list */
struct clip *insert_at_end(struct clip *hp,char **five) {
  struct clip *cp,*tp;
  /* 
     malloc tp
     set views using atoi(*five)
     malloc for four strings.
     strcpy four strings to tp
     insert tp at the end of the list pointed by hp
     use cp to traverse the list
     return hp
  */  
  tp = malloc(sizeof(struct clip));

  tp->views = atoi(*five);
  tp->user = malloc(strlen(five[1]));
  strcpy(tp->user, five[1]);

  tp->time = malloc(strlen(five[2]));
  strcpy(tp->time, five[2]);

  tp->title = malloc(strlen(five[3]));
  strcpy(tp->title, five[3]);
  
  cp = hp;
  if(hp == NULL){
     hp = tp;
  } else {
    while(cp->next != NULL){
      cp = cp->next;
    }
    cp->next = tp;
  }
  
  return hp;
}

void print_a_lst(struct clip *cp) {
  /* 
     use a while loop and the statement below to print the list
     printf("%d,%s,%s,%s,%s\n",cp->views,cp->user,cp->id,cp->title,cp->time);
  */
  int i = 0;
  printf("%s\n", "===== print a lst =======" );
  while(cp->next != NULL){
    printf("%d,%s,%s,%s\n",cp->views,cp->user,cp->title,cp->time);
    cp = cp->next;
    i++;
  }
  printf("%s\n", "===== end print a lst ====" );

}

void print_final_list(struct clip *hourly[]){
  int i;
  for ( i = 0; i < 60; ++i)
  {
    printf("%d,%s,%s,%s\n",hourly[i]->views,hourly[i]->user,hourly[i]->title,hourly[i]->time);
  }
}

/* end */