#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#define DEBUG 1
#define	FEW	8

/* Set DEBUG to 1 to print few element before and after the sort */
/* This piece of code is to assist you. Don't expect comments on what it
   does (it's obvious); If you find it useful use it, otherwise discard it.
 */
/* Additional note:
 *  In VISUAL C++ or other environments you might have to replace
 *  random() with rand() that has prototype int rand(void)
 *  In that case INT_MAX might have to be replaced by RAND_MAX
 *  clock() and CLOCKS_PER_SEC might also cause problems.
 */

extern clock_t clock();

/*          [] Pntr,   #Element, len in byte, compare function */    
void bubble(void *akeys, int n, int size, int (*compare) (const void * , const void *))
{
	register int i,j,k;
	char	*x;
  char    *keys;

 keys= (char *) akeys;

	x = (char *) malloc(size*sizeof(char));
	for(i=1;i<n;i++) {
		k=i;
		memcpy(x,&keys[i*size],size);
		for(j=n-1;j>=i;j--) {
			if (compare(&keys[(j-1)*size],&keys[j*size]) > 0) {
				memcpy(x,&keys[(j-1)*size],size);
				memcpy(&keys[(j-1)*size],&keys[j*size],size);
				memcpy(&keys[j*size],x,size);
			}
		}
	}
        free((char *)x);
}

/* insertion-sort  */
void inssrt(void *akeys, int n, int size, int (*compare) (const void * , const void *)) {
	
	// register int i,j,temp;
	// char	*x;
 //    char    *keys;

	// keys= (char *) akeys;
	// x = (char *) malloc(size*sizeof(char));
	
	// //loop to go to the end of array
	// for (i=1; i <n; i++){	 
	// memcpy(x,&keys[i*size],size);	
	
	// 	//loop to go from current to the front
	// 	for (j=i; j>=0; j-- ){		
	// 		//compare
			
	// 		if (compare(&keys[j*size],&keys[(j-1)*size]) < 0){
	// 			memcpy(temp,&keys[(j-1)*size],size);
	// 			memcpy(&keys[(j-1)*size],&keys[j*size],size);
	// 			memcpy(&keys[j*size],temp,size);
	// 		}


	// 	}
	// }
	// free((char *)x);
}


/* rmgsrt-sort  */
void rmgsrt(void *akeys, int n, int size, int (*compare) (const void * , const void *)) {
  register int i,j,temp; 
  char  *x;
  char  *keys;
  // char string[] = "Hello World";
  char s[] = "C string";

int x;

for(x = 0; x < sizeof(s);x++)

{

    printf("%c",s[x]);

}
  
  // printf(string);

  keys= (char *) akeys;
  x = (char *) malloc(size*sizeof(char));
  //printf('%s', 'here');
  //loop to go to the end of array
  for (i=1; i <n; i++){  
  memcpy(x,&keys[i*size],size); 
  
    //loop to go from current to the front
    //for (j=i; j>=0; j-- ){    
      //compare
      
      // if (compare(&keys[j*size],&keys[(j-1)*size]) < 0){
      //   memcpy(temp,&keys[(j-1)*size],size);
      //   memcpy(&keys[(j-1)*size],&keys[j*size],size);
      //   memcpy(&keys[j*size],temp,size);
      // }


    //}
  }
  free((char *)x);
}


/* nmgsrt-sort  */
void nmgsrt(void *akeys, int n, int size, int (*compare) (const void * , const void *)) {

}


int compare(const void  *x,const void  *y)
{
	return(* ((int*)x)-*((int *)y));
}


int main(int argc,char *argv[])
{
	int i,j,n,runs;
	int *ptr,*bptr;
	clock_t t1,t0;
	size_t n_t;
  double elapsed;

	n=1000;runs=1;
        if ( 1 == argc ) {
	      printf("Usage: %s size \n",argv[0]);
	      exit(1);
	} else {
	      n = atoi(argv[1]);
	}

	ptr= (int*) malloc(n*sizeof(int));
	bptr= (int*) malloc(n*sizeof(int));

	n_t =  (size_t) n;

	for(i=0;i<n_t;i++) 
          bptr[i]=ptr[i] = (int) (n_t*(random()/((double) INT_MAX)));
/*
          bptr[i]=ptr[i] = random();
          bptr[i]=ptr[i] = 90;
          bptr[i]=ptr[i] = n_t -i;
          bptr[i]=ptr[i] = i;
*/

/* generic qsort */
  if (DEBUG) {
	  for(i=0;i<FEW;i++) 
            printf("%d ",ptr[i]); printf("...");
	  for(i=n_t-FEW;i<n_t;i++) 
            printf("%d ",ptr[i]); printf("\n");
        }
	elapsed=0.0; 
  for(j=0;j<runs;j++){	
	   for(i=0;i<n_t;i++) ptr[i] = bptr[i];
	   t0=clock(); 
             qsort(ptr,(size_t) n_t,sizeof(int),compare); 
           t1=clock();
	   elapsed +=(t1-t0)/((double)CLOCKS_PER_SEC);
	}

  if (DEBUG) {
	  for(i=0;i<FEW;i++) 
           printf("%d ",ptr[i]); printf("...");
	  for(i=n_t-FEW;i<n_t;i++) 
           printf("%d ",ptr[i]); printf("\n");
        }
    //    printf("qsort generic:Elapsed time is %10.8f\n",elapsed/runs);
	for(i=0;i<n_t-1;i++) 
  if (ptr[i] > ptr[i+1] )  {
    printf("qsort does not sort! \n");
    fflush(stdout);
  }

/* End of qsort */

	for(i=0;i<n_t;i++) 
           ptr[i]=bptr[i] ;

/* bubble sort */
  if (DEBUG) {
	  for(i=0;i<FEW;i++) 
      printf("%d ",ptr[i]); printf("...");
	     for(i=n_t-FEW;i<n_t;i++) 
          printf("%d ",ptr[i]); printf("\n");
  }
  elapsed=0.0; 
  for(j=0;j<runs;j++){	
    for(i=0;i<n_t;i++) ptr[i] = bptr[i];
      t0=clock(); 
      bubble(ptr,n_t,sizeof(int),compare); 
      t1=clock();
      elapsed +=(t1-t0)/((double)CLOCKS_PER_SEC);
	  }  

  if (DEBUG) {
	  for(i=0;i<FEW;i++) 
      printf("%d ",ptr[i]); printf("...");
	  for(i=n_t-FEW;i<n_t;i++) 
       printf("%d ",ptr[i]); printf("\n");
  }
  //printf("BubbleSort:Elapsed time is %10.8f\n",elapsed/runs);
	for(i=0;i<n_t-1;i++) 
    if (ptr[i] > ptr[i+1] )  {
      //printf("bubblesort does not sort! \n");
      fflush(stdout);
    }

	free((void *) ptr);
	free((void *) bptr);
}