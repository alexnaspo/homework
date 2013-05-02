/******************************************************************************
 CS288 HW6 three search strategies: depth, breadth, and intelligent
 command example: command 16 numbers and search strategy
   fifteen 1 2 3 4 5 6 7 8 9 10 11 12 13 14 0 15 {dfs|bfs|astar}
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
int calc_misplaced(), calc_h();
int flag;

int main(int argc,char **argv) {

  int iter,cnt,total;
  struct node *tsucc,*csucc,*copen,*topen,*open,*closed,*succ;

  open=closed=succ=NULL;

  start=initialize(argc,argv);  /* init initial and goal states */
  start->loc[4][0] = calc_h(start);
  open=start; 
  iter=0; total=1;

  
  while (open!=NULL) {    /* Termination cond is tested in expand. */      
      copen=open;
      open=open->next; /* get the first node from open to expand */                                 

printf("\t\t\t\t\t%s\n\n", "**************CURRENT OPEN************************");                      
print_a_node(copen);
printf("%i\n", copen->loc[4][0]);
printf("\t\t\t\t\t%s\n\n", "**************END CURRENT OPEN************************");  

      succ=expand(copen);       /* Find new successors */

      succ=filter(open,succ);   /* New succ list */

      succ=filter(closed,succ); /* New succ list */

      if (goal_found(succ,goal)==TRUE){
        printf("%s\n", "=====WIN!=====");
        print_nodes(succ);
        printf("%s\n", "=====WIN!=====");
        break;
      } 
      cnt=count(succ);
      // printf("%i\n", cnt);
      total=total+cnt;
      if (succ!=NULL) {
        // printf("%s\n", "new open");
        open=merge(succ,open,flag); /* New open list */
      }
      copen->next=closed;
      closed=copen;   /* New closed */
      iter++;
      // printf("%i\n", iter);
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
  struct node *csucc,*copen, *temp[count(succ)];
  int i,j;
  if (flag==DFS) {  /* attach to the front: succ -> ... -> open */
    csucc = succ;
    // printf("%s\n", "FLAG DFS");
    while(csucc->next != NULL){
      csucc = csucc->next;
    }   
    
    csucc->next = open;  
    open = succ;
    // print_nodes(open);
  } else if (flag==BFS) { /* attach to the end: open -> ... -> succ */
    // printf("%s\n", "FLAG BFS");
    copen = open;
    if(copen == NULL){
      open = succ;
    } else {
      while(copen->next != NULL){
        copen = copen->next;
      }
      copen->next = succ;      
    }    
  } else {       /* Best first: insert in asc order of h value */
    csucc = succ;
    i = 0;
    while(csucc->next != NULL){      
      temp[i++] = csucc;
      csucc = csucc->next;
    }
    temp[i++] = csucc;

    for (j = 0; j < i; j++){
      temp[j]->next = NULL;
      open = insert_by_h(temp[j], open);
    }
  }


  return open;
}

/* insert succ into open in ascending order of H value */
struct node *insert_by_h(struct node *new_node,struct node *head) {
  struct node *cp,*tp;
  if(head == NULL || head->loc[4][0] >= new_node->loc[4][0]){
    new_node->next = head;
    head = new_node;
  } else {
    cp = head;
    while(cp->next != NULL && cp->next->loc[4][0] < new_node->loc[4][0]){      
      // printf("%i\n", cp->loc[4][0]);
      cp = cp->next;
      
    }
    new_node->next = cp->next;
    cp->next = new_node;  
  }  

  return head;
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
  int row, collumn;
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      if(selected->loc[i][j] == 0){
        row = i;
        collumn = j;
        break;
      }  //found zero
    }
    if(selected->loc[i][j] == 0) break; //found zero
  }
  i = row;
  j = collumn;
  
  
  cnt = 0;
  if(dn(i, j)) {
    swap(i,j,i+1,j,cnt, succ_buf);
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
  if(cnt > 4) exit(0);
  expanded = NULL;
  for (i = 0; i < cnt; i++){
    // printf("%i\n", i);
    tp = malloc(sizeof(struct node));
    // tp->next = NULL;
    for (j = 0; j < N; j++){
      for (k = 0; k < N; k++){        
        tp->loc[j][k] = succ_buf[i][j][k];
      }
    }
    tp->loc[4][0] = calc_h(tp);
    
    tp->next = expanded;
    expanded = tp;
  }
  

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
  return((0 <= i - 1) && (i - 1 < N));
}

/* 0 goes left by a column */
int lt(int i,int j){
  return((0 <= j - 1) && (j - 1 < N));
}

void swap(int i,int j,int k,int l,int index,int succ_buf[BF][N+1][N]){
  // printf("I:%i J:%i K:%i L:%i  IJVAL:%i KLVALE:%i\n",i,j,k,l, succ_buf[index][i][j], succ_buf[index][k][l]);
  int temp = succ_buf[index][i][j];
  succ_buf[index][i][j] = succ_buf[index][k][l];
  // printf("I:%i J:%i K:%i L:%i  IJVAL:%i KLVALE:%i\n",i,j,k,l, succ_buf[index][i][j], succ_buf[index][k][l]);
  succ_buf[index][k][l] = temp;
}

struct node *filter(struct node *hp,struct node *succ){ 
  struct node *cp, *sp, *tp, *np, *arr[9999];
  // printf("%s\n", "BEFORE");
  // print_nodes(succ);
  // printf("%s\n", "END BEFORE");

  cp = hp;
  sp = succ;
  tp = succ;
  int cnt, i, match;
  cnt = 0;
  while(sp != NULL){
    cp = hp;
    while (cp!=NULL && !nodes_same(cp->loc,sp->loc)) {
      cp=cp->next;
    }
    if (cp==NULL) {
      // No match
      arr[cnt] = sp;
      cnt++;
    } else {
      // match
    }
    sp = sp->next;
  }
  if(cnt > 0){
    succ = arr[0];
    arr[cnt -1]->next = NULL;
    np = succ;
    // printf("%s\n", "AFTER");
    // print_a_node(arr[0]);
    for (i = 1; i < cnt; ++i)
    {
      np->next = arr[i];
      np = np->next;
      // print_a_node(arr[i]);
    }
    // print_nodes(succ);
    // printf("%s\n", "END AFTER");
  } else {
    succ = NULL;
  }

  return succ;
}

int nodes_same(int a[N+1][N],int b[N+1][N]) {
  int i=0,flg=FALSE;
  int j;

  for (i = 0; i < N; ++i) {
    for (j = 0; j < N; ++j) {
      if(a[i][j] != b[i][j]) {
        return flg = FALSE;
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

int calc_misplaced(struct node *np) {
  int i,j, (*mp)[N];
  int cnt, misplaced;
  misplaced = 0;
  cnt = 1;
  mp = np->loc;
  for (i=0;i<N;i++) {
    for (j=0;j<N;j++) {
      if(np->loc[i][j] == cnt){
        //printf("arr-%i cnt-%i %s\n", np->loc[i][j], cnt, "match");
      } else {
        //printf("%s\n", "no match");
        misplaced++;
      }
      cnt++;
    }
  }
  // printf("%i\n", misplaced);
  // printf("\n");
  return misplaced;
}

// Calculate manhattan distance
// this can probably be done cleaner
int calc_h(struct node *np) {
  int i,j, x, y, (*mp)[N], (*gs)[N];
  int cnt, h, xi, yi;
  h = 0;
  cnt = 1;
  mp = np->loc;
  gs = goal->loc;

  int xidx, yidx, xtemp;
  xidx = yidx = 0;
  for (i = 0; i < N; ++i) {
    xidx=0;
    for (j = 0; j < N; ++j) {    
      if(mp[i][j] == gs[xidx][yidx]) {        
        //match
      } else{
        //no match, calculate the distance from this number
        for (y = 0; y < N; y++) {
          for (x = 0; x < N; x++) {
            if(mp[y][x] == gs[yidx][xidx]){
              xtemp = fabs(y - yidx) + fabs(x - xidx);
              h+= fabs(y - yidx) + fabs(x - xidx);
              break; //found match
            } 
          }
          if(mp[i][j] == gs[xidx][yidx]) break;
        }
      } 
      xidx++;
    }
    yidx++;
  }  
  return h;
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
  if (strcmp(argv[idx],"dfs") == 0){
    flag=DFS; 
  } else if (strcmp(argv[idx],"bfs") == 0){
    flag = BFS;
  } else {
    flag=BEST;
  }

  return start;
}
/* end of hw4.c */
