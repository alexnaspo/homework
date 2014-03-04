#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <time.h>
#include <malloc/malloc.h>

void int_radix_sort();

int main(int argc, char** argv) {
  int i;
  int n;
  n = 12;
  int root, size, sidx, eidx,sbin, ebin;
  int *arr, *arr2;
  int *local_cnt;
  int *global_cnt;
  int bins = 256;
  
  MPI_Init(NULL, NULL);
  // Get the number of processes
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  // Get the rank of the process
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
  // Get the name of the processor
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int name_len;
  MPI_Get_processor_name(processor_name, &name_len);

  // size = n/(world_size);
  sbin = rank * ((bins / world_size));
  ebin = (rank+1) * ((bins / world_size)) - 1;
  // printf("%i - %i\n",sbin, ebin );

  if(rank == 0){
    //create initial array
    arr = (int *)malloc(n*sizeof(int));
    arr2 = (int *)malloc(n*sizeof(int));
    for (i = 0; i < n; ++i)
    {
      arr[i] = rand() % 100;
      // printf("%i\n", arr[i]);
    } 
  }

  size = n/world_size;
  sidx = rank * size;
  eidx = (rank+1) * size;
  local_cnt = (int *)malloc((256)*sizeof(int));

  // distribute the arr to all proc
  // MPI_Scatter(arr, size, MPI_INT,local_arr, size, MPI_INT, 0, MPI_COMM_WORLD);
  int cnt[256];
  int map[256];
  int dest[99999];
  int byte = 0;
  int index;
  if(rank == 0){
    // for (i = 0; i < n; i++){
    //   printf("rank%i - %i\n", rank, arr[i]);
    // }
    memset(cnt, 0, sizeof(cnt));
    memset(map, 0, sizeof(map));
    // map[0] = 0;
    for (i = 0; i < n; i++)
    {
      index = ((arr[i]>>(8 * byte))) & 255;
      printf("%i\n", index);
      cnt[((arr[i]>>(8 * byte))) & 255]++;
      
    }
  }
  MPI_Scatter(cnt, size, MPI_INT,local_cnt, size, MPI_INT, 0, MPI_COMM_WORLD);

  for (i = 0; i < (256/4 - 1); i++) {   
    map[i] = map[i-1] + local_cnt[i-1];
  }

  for (i = 0; i < n; i++) {

    dest[map[((arr[i])>> (8 * byte)) & 255]++] = arr[i];  
    //printf("%i\n",map[((arr[i])>> (8 * byte)) & 255]);
  }  

  

  //gather each array into new location arr2
  // MPI_Gather(cnt, size, MPI_INT, arr2, size, MPI_INT, 0, MPI_COMM_WORLD);



  // if(rank == 0){
  //   for (i = 0; i < n; i++){
  //     printf("rank%i - %i\n", i, arr2[i]);
  //   }
  // }

  // Finalize the MPI environment.
  MPI_Finalize();
}

void int_radix_sort(int byte, int n, int source[], int dest[], int sidx, int eidx){
  int cnt[256];
  int map[256];
  int i;
  // memset(cnt, 0, sizeof(cnt));
  map[0]=0;

  for (i = 0; i < n; i++)
  {
    cnt[(source[i] >> (8 * byte)) & 255]++;
  }

  for (i = sidx; i < eidx; i++) {   
    map[i] = map[i-1] + cnt[i-1];
  }  

  for (i = 0; i < n; i++) {
    dest[map[(source[i] >> (8 * byte)) & 255]++] = source[i];  
  }  
}



// int main(int argc, char** argv) {
//   // Initialize the MPI environment
//   MPI_Init(NULL, NULL);
 
//   // Get the number of processes
//   int world_size;
//   MPI_Comm_size(MPI_COMM_WORLD, &world_size);
 
//   // Get the rank of the process
//   int world_rank;
//   MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
 
//   // Get the name of the processor
//   char processor_name[MPI_MAX_PROCESSOR_NAME];
//   int name_len;
//   MPI_Get_processor_name(processor_name, &name_len);
 
//   // Print off a hello world message
//   printf("Hello world from processor %s, rank %d"
//          " out of %d processors\n",
//          processor_name, world_rank, world_size);
 
//   // Finalize the MPI environment.
//   MPI_Finalize();
// }