#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

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
  print_lsts(hourly);
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
}

/* prefix can be such as: index-2013-03-01-12 
  the directory will have 60 files with the above prefix */
void build_lsts(char *prefix) {
  FILE *fp;
  char *cmd,*filename;
  int i;

  for (i=0;i<MAX_CLIPS;i++) hourly[i] = NULL;

  sprintf(cmd,"ls %s*",prefix);
  fp = popen(cmd,"r"); 
  /* read output from command */
  i=0;
  while (fscanf(fp,"%s",filename) == 1) {
    hourly[i] = build_a_lst(filename);
    i++;
    //    print_a_lst(hourly[i]);
  }
  fclose(fp);
}

/* open the file, read one line at a time, split and insert */
struct clip *build_a_lst(char *fn) {
  FILE *fp;
  struct clip *hp;
  char *fields[5];
  char line[LINE_LENGTH];
  int cnt=0;
  hp=NULL;

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
  delim = ",\n";
  /* 
     call strtok(line, delim);
     malloc and strcpy token to fields

     repeat until strtok returns NULL using strtok(NULL, delim);
     each time you get token, malloc and strcpy to fields
 */
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

  return hp;
}

void print_a_lst(struct clip *cp) {
  /* 
     use a while loop and the statement below to print the list
     printf("%d,%s,%s,%s,%s\n",cp->views,cp->user,cp->id,cp->title,cp->time);
  */
}

/* end */