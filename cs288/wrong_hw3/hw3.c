/* HW2 read cafefully and follow all the instructions/comments
   this program compiles and runs as is although it's not doing much.
*/

#include <stdio.h>
#include <malloc/malloc.h>
#include <string.h>
#include <stdlib.h>

#define MAXD 10     /* 3 <= depth < MAXD  */
#define MAXB 10     /* 3 <= breadth < MAXB  */

void create_dir_tree();
void traverse_dir_tree();
int find_total_no_dirs();
int find_dir();

struct dir {
  char *path;      /* path to get to this dir, not including this */
  char *name;      /* current dir name */
  int d;       /* 3 <= depth level < MAXD */
  /* the init_d is depth 0, its immediate subdirs are depth 1, etc. */
  int b;       /* 3 <= breadth or number of sub dirs < MAXB */
  struct dir *up;    /* points to the parent */
  struct dir **down; /* points to the sub dirs of this dir. Note the TWO *'s */
  struct dir *left;    /* left sibling dir, use circular link */
  struct dir *right;     /* right sibling dir, use circular link */
};

int main(int argc, char **argv) {
  struct dir *hp;
  int b,d,n,flag;
  char *init_d,tst_dir[100];

  if (argc < 4) {
    printf("usage: hw3 root_d d b\n");
    return 1;
  }

  argv++;     /* skip the command itself */
  init_d = *(argv++);
  d = atoi(*argv++);
  b = atoi(*argv++);

  create_dir_tree(&hp,init_d,d,b);
  printf("%s\n", "===========");
  traverse_dir_tree(hp);
  n = find_total_no_dirs(hp);
  strcpy(tst_dir,"root_d/a/bb/ccc/dddd");
  if ((flag = find_dir(hp,tst_dir)))
    printf("dir %s found\n",tst_dir);
  else
    printf("no dir %s found\n",tst_dir);
  return 0;
}

/* create directories breadth first */
void create_dir_tree(struct dir **hp,char *name,int d, int b) {
  printf("create_dir_tree init_d=%s depth=%d breadth=%d\n",name,d,b);
  int i, j;
  struct dir *new;
  char *open[1000];
  open[0] = name;
  printf("%s\n", open[0]);
  for (i = 1; i <= d; ++i)
  {
    char temp[1000];
      for (j = 1; j <= b; ++j)
      {
        char str[4];
        char strTwo[4];
        sprintf(str, "%d", i);
        sprintf(strTwo, "%d", j);

        new = malloc(sizeof(struct dir));

        new->path = malloc(sizeof(name));
        strcpy(new->path, name);
        strcat(new->path,"/");
        strcat(new->path, str);
        strcat(new->path,"/");
        strcat(new->path, strTwo);
        
        // printf("%s\n", new->path);
      }
    
  }
  /* fill in here */
}

/* print directories breadth first. use full path */
void traverse_dir_tree(struct dir *hp,char *name) {
  printf("print_dir_tree init_d=%s\n",name);
  /* fill in here */
}

/* find the total number of directories in the dir tree */
/* compute the number by traversing the tree */
int find_total_no_dirs(struct dir *hp){
  int n=0;
  printf("find_total_no_dirs\n");
  /* fill in here */
  return n;
}

/* return 1 if found. otherwise, 0. */
int find_dir(struct dir *hp,char *name){
  int flag=0;
  printf("find_dir %s\n",name);
  /* fill in here */
  return flag;
}