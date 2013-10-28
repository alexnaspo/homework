#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <time.h>
#include <malloc/malloc.h>

void int_radix_sort();


int main(int argc, char const *argv[])
{
  int *arr, *arr2;
  int n = 12;
  int i;
  arr = (int *)malloc(n*sizeof(int));
  arr2 = (int *)malloc(n*sizeof(int));
  for (i = 0; i < n; ++i)
  {
    arr[i] = rand() % 100;
    printf("%i\n", arr[i]);
  } 
printf("%s\n", "======");
  int_radix_sort(0,n,arr,arr2);
  int_radix_sort(1,n,arr2,arr);
  int_radix_sort(2,n,arr,arr2);
  int_radix_sort(3,n,arr2,arr);
  
  for (i = 0; i < n; ++i)
  {
    // printf("%i\n", arr[i]);
  } 

  /* code */
  return 0;
}

void int_radix_sort(int byte, int n, int source[], int dest[]){
  int cnt[256];
  int map[256];
  int index;
  int i;
  memset(cnt, 0, sizeof(cnt));
  map[0]=0;

  for (i = 0; i < n; i++)
  {
    index = ((source[i] >> (8 * byte)) & 255);
    printf("%i\n", index);
    cnt[index]++;
  }

  for (i = 1; i < 256; i++) {   
    map[i] = map[i-1] + cnt[i-1];
  }  

  for (i = 0; i < n; i++) {
    dest[map[(source[i] >> (8 * byte)) & 255]++] = source[i];  
  }  
}