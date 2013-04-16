/******************************************************************************
 CS288 HW6 three search strategies: depth, breadth, and intelligent
 command example: command 16 numbers and search strategy
   fifteen 1 2 3 4 5 6 7 8 9 10 11 12 13 14 0 15 {dfs|bfs|astar}
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BF 4      /* Branching factor of the search tree */
#define N 4     /* fix to fifteen puzzle but should be */
#define NxN 16      /* able to handle any size */

#define DFS 0                   /* depth first search */
#define BFS 1                   /* breadth first search */
#define BEST 2                  /* best first search */
#define BB 3                    /* branch and bound */
#define ASTAR 4                 /* A* search */

struct node {
  int loc[N+1][N];    /* the last row holds f, g and h */
  struct node *next;
};
struct node *start,*goal;
struct node *initialize(),*expand(),*merge(),*filter();
struct node *insert_front(),*insert_end(),*insert_by_h(),*insert_by_g(),*insert_by_f();
char strategy[10];

int TRUE = 1;
int FALSE = 0;
int goal_found(),expand_a_node(),nodes_same(),find_h(),count();
int up(),dn(),lt(),rt();
void swap(),print_a_node(),print_nodes();
int flag;

int main(int argc,char **argv) {

  int iter,cnt,total;
  struct node *tsucc,*csucc,*copen,*topen,*open,*closed,*succ;

  open=closed=succ=NULL;

  start=initialize(argc,argv);  /* init initial and goal states */
  open=start; 
  iter=0; total=1;  
  printf("%s\n", "========START=========");
  while (open!=NULL) {    /* Termination cond is tested in expand. */
      copen=open;
      open=open->next; /* get the first node from open to expand */
      succ=expand(copen);       /* Find new successors */
      succ=filter(open,succ);   /* New succ list */
      succ=filter(closed,succ); /* New succ list */
      if (goal_found(succ,goal)==TRUE){
        printf("%s\n", "WIN!");
        break;
      } 
      cnt=count(succ);
      total=total+cnt;
      if (succ!=NULL) open=merge(succ,open,flag); /* New open list */
      copen->next=closed;
      closed=copen;   /* New closed */
      iter++;
      printf("%s\n", "------END ROUND----");
   }
   printf("%s strategy: %d iterations %d nodes\n",strategy,iter,total);
   return 0;
}       /* end of main */

int goal_found(struct node *cp,struct node *goal){ /* cp=openp */
  int flg;
  while (cp!=NULL && !nodes_same(cp->loc,goal->loc)) {
      cp=cp->next;
   }
   if (cp==NULL) flg=FALSE; else flg= TRUE;
  return flg;
}

int count(struct node *succ) {
  int cnt=0;
  while (succ!=NULL) {
    cnt++;
    succ=succ->next;
  }
  return cnt;
}

struct node *merge(struct node *succ,struct node *open,int flag) {
  struct node *csucc,*copen;
  
  if (flag==DFS) {  /* attach to the front: succ -> ... -> open */
    //.....
  }else if (flag==BFS) { /* attach to the end: open -> ... -> succ */
    //.....
  }else {       /* Best first: insert in asc order of h value */
    //.....
  }
  return open;
}

/* insert succ into open in ascending order of H value */
struct node *insert_by_h(struct node *succ,struct node *open) {
  //......
  return open;
}

struct node *expand(struct node *selected) {
  int i,j,k,cnt,succ_buf[BF][N+1][N];
  struct node *cp,*tp,*expanded;
  cp = selected;
  for (i = 0; i < N; i++){
    for (j = 0; j < N; j++){
      for (k = 0; k < N; k++){
        succ_buf[i][j][k] = cp->loc[j][k];
      }
    }
  }  
  for (i = 0; i < N; ++i) {
    for (j = 0; j < N; ++j) {
      if(selected->loc[i][j] == 0) break; //found zero
    }
    if(selected->loc[i][j] == 0) break; //found zero
  }
  
  cnt = 0;
  if(dn(i, j)) {
    swap(i,j,i+1,j,0, succ_buf);
    cnt++;
  } 

  if(rt(i, j)) {
    swap(i,j,i,j+1,cnt, succ_buf);
    cnt++;
  }

  if(up(i, j)) {
    swap(i,j,i-1,j,cnt, succ_buf);
    cnt++;
  }

  if(lt(i, j)) {
    swap(i,j,i,j-1,cnt, succ_buf);
    cnt++;
  }
  expanded = selected;
  for (i = 0; i < cnt; i++){
    tp = malloc(sizeof(struct node));
    // tp->next = NULL;
    for (j = 0; j < N; j++){
      for (k = 0; k < N; k++){        
        tp->loc[j][k] = succ_buf[i][j][k];
      }
    }
    tp->next = expanded;
    expanded = tp;
  }    
  // print_nodes(expanded);

  return expanded;
}

int expand_a_node(int node[N+1][N],int succ_buf[BF][N+1][N]) {
  int i,j,cnt,found,g_val,h_val;

  
  return cnt;     /* number of nodes expanded */
}

/* 0 goes down by a row */
// then create a node this should be a function returning a temp ptr
int dn(int i,int j){ //swap here
  return((0 < i + 1) && (i + 1 < N));
}

/* 0 goes right by a column */
int rt(int i,int j){
  return ((0 < j + 1) && (j + 1 < N));

}

/* 0 goes up by a row */
int up(int i,int j){
  return((0 < i - 1) && (i - 1 < N));

}

/* 0 goes left by a column */
int lt(int i,int j){
  return((0 < j - 1) && (j - 1 < N));
}

void swap(int i,int j,int k,int l,int index,int succ_buf[BF][N+1][N]){
  int temp = succ_buf[index][i][j];
  succ_buf[index][i][j] = succ_buf[index][k][l];
  succ_buf[index][k][l] = temp;
}

struct node *filter(struct node *hp,struct node *succ){ 
  // if any nodes in succ are in hp, then remove them
  return succ;
}

int nodes_same(int a[N+1][N],int b[N+1][N]) {
  int i=0,flg=FALSE;
  int j;

  for (i = 0; i < N; ++i) {
    for (j = 0; j < N; ++j) {
      if(a[i][j] != b[i][j]) {
        flg = FALSE;
        break;
      } else{
        flg = TRUE;
      } 
    }
  }
  return flg;
}

void print_nodes(struct node *cp) {
  while (cp!=NULL) {
    print_a_node(cp);
    cp=cp->next;
  }
}

void print_a_node(struct node *np) {
  int i,j, (*mp)[N];
  mp = np->loc;
  for (i=0;i<N;i++) {
    for (j=0;j<N;j++) printf("%2d ",np->loc[i][j]);
    printf("\n");
  }
  printf("\n");
}

struct node *initialize(int argc, char **argv){
  int i,j,k,idx;
  struct node *tp;

  tp=(struct node *) malloc(sizeof(struct node));
  idx = 1;
  for (j=0;j<N;j++)
    for (k=0;k<N;k++) tp->loc[j][k]=atoi(argv[idx++]);
  for (k=0;k<N;k++) tp->loc[N][k]=0;  /* set f,g,h of initial state to 0 */
  tp->next=NULL;
  start=tp;
  printf("initial state\n"); print_a_node(start);
  
  tp=(struct node *) malloc(sizeof(struct node));
  idx = 1;
  for (j=0;j<N;j++)
    for (k=0;k<N;k++) tp->loc[j][k] = idx++;
  tp->loc[N-1][N-1] = 0;        /* empty tile=0 */
  for (k=0;k<N;k++) tp->loc[N][k]=0;  /* set f,g,h of goal state to 0 */
  tp->next=NULL;
  goal=tp; 
  printf("goal state\n"); print_a_node(goal);
  printf("%s\n", "======================");

  strcpy(strategy,argv[idx]);
  if (strcmp(argv[idx],"dfs")) flag=DFS;
  else if (strcmp(argv[idx],"bfs")) flag = BFS;
  else flag=BEST;

  return start;
}
/* end of hw4.c */
