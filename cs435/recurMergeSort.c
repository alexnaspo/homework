#include <stdio.h>
#include <stdlib.h>
// #include <time.h>
// #include <limits.h>
#include <string.h>

int recurMergeSort(int *arr, int size){

  if(size/sizeof(int) <= 1){
    return *arr;
  }

  int middle = (size/2)/sizeof(int);
  // printf("%i\n", middle);
  int left[middle];
  int right[middle];

  //split arrays in two
  memcpy(left, arr, middle * sizeof(int));

  memcpy(right, &arr[middle], middle * sizeof(int));
  
  
  //recursive calls
  recurMergeSort(left, sizeof(left));

  recurMergeSort(right, sizeof(right));

  return merge(left, sizeof(left), right, sizeof(right));

}

int merge(int *left, int leftsize, int *right, int rightsize){
  // printf("%i\n", left[0]);
  int i = 0;
  int k = 0;
  int j = 0;
  // int result[sizeof(left) + sizeof(right)];  
  int leftlength = leftsize/sizeof(int);
  int rightlenth = rightsize/sizeof(int);
  int result[rightlenth + leftlength];

  while( i < leftlength && j < rightsize)   {
    if(left[i] <= right[j]){      
      result[k] = left[i];      
      i++;
      k++;
    } else {
      result[k] = right[j];
      j++;
      k++;
    }
  }

  int x;
  for (x = i; x < leftlength; x++)
  {
    // printf("%i\n", sizeof(left)/sizeof(int));
    printf("%i\tleft\n", left[x]);
    result[k] = left[x];
    // printf("%i\n", result[k]);
    k++;
  }

  int y;
  for (y = j; y < rightlenth; y++)
  {
    // printf("%i rightsize \n", rightsize);
    printf("%i\tright\n", right[y]);
    result[k] = right[y];
    
    k++;
  }

  
  int c;
  for (c = 0; c < rightlenth + leftlength; c++)
  {
    if( result[c] ){ 
      printf("%i\n", result[c]);
    }
  }
  printf("%s\n", "=======");
  

  return *result;
}

int main() {
  int arr[] = {2,11,23,41,5,4,1,6};

  int result = recurMergeSort(arr, sizeof(arr));

  //printf("%i\n", result);

  return 0;
}



