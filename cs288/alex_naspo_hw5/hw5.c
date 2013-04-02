#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc/malloc.h>

#define LINE_LENGTH 200
#define MAX_CLIPS 100
void print_a_line(),print_a_clip(),print_a_lst(),print_lsts();
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
  // printf("%s\n", "here");
  //print_lsts(hourly);
  //  sort_lsts(); /* sort hourly in descending order of views */
  //  print_lsts(hourly);
  return 0;
}

void sort_lsts() {
  /* 
     sort individual lists in descending order of views
     such that the first clip in each list will have the highest views
     this one is the same as HW4


     once you are done sorting individual lists, sort the entire array
     this one is again the same as HW4 except now that you use values from the first clip of each list

  */
}

/* use print_a_lst(struct clip *cp); */
void print_lsts(struct clip **lst) {
  // FILL IN
  // ...
  // FILL IN
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
    // printf("%s\n", filename);
printf("%s\n", "=======new list=========");    
    hourly[i] = build_a_lst(filename);
    i++;
    print_a_lst(hourly[i]);
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
  
  //@ERROR head is null every time
  // Am I passing the value wrong?
  cp = hp;
  if(hp == NULL){
     hp = tp;
     printf("%s\n", "head is null");
  } else {
    while(cp->next != NULL){
      cp = cp->next;
    }
    cp->next = tp;
  }
  print_a_lst(hp);
  
  return hp;
}

void print_a_lst(struct clip *cp) {
  /* 
     use a while loop and the statement below to print the list
     printf("%d,%s,%s,%s,%s\n",cp->views,cp->user,cp->id,cp->title,cp->time);
  */
  printf("%s\n", "===== print a lst =======" );
  while(cp->next != NULL){
    printf("%i\n", cp->views);
    //printf("%d,%s,%s,%s\n",cp->views,cp->user,cp->title,cp->time);
    cp = cp->next;
  }
  printf("%s\n", "===== end print a lst ====" );

}

/* end */