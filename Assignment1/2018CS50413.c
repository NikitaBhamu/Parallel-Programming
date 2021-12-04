/*

COL380. assignment 1.

Deadline: 12.03.2021

Problem:

Compute the sum of the First N natural numbers.

The sequential version is provided below.

1. Develop two parallel versions of the given program using OpenMP `parallel for' with maximum 8 threads.

Compilation command: gcc -O0 ...

2. The speedup and efficiency of both parallel versions for 2, 4, 8 threads for N=10^3, N=10^5 and N=10^7 numbers.

3. Does the speedup follow Amdahl's law?

Hint: Use a time function in the program (e.g. omp_get_wtime) to measure the time.

*/


#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 1000 // vary N as required

unsigned long long helper_func(unsigned long long* a, int s,int e){
    
    unsigned long long sum =0;
   // printf("start %d , end %d\n",s,e);
    for (int i=s; i<e ; i++){
        sum += a[i];
    }
   // printf("%llu\n",sum);
    return sum;
}

int min(int a, int b){
    if(a<=b){
        return a;
    }
    return b;
}

int main(int argc, char* argv[])
{
  //Strategy 0 is the approach in which we calculate the partial sums of the n/p  partitions and then add those partial sums sequentially
  //Strategy 1 is the approach in which a downward heap is formed if we draw the steps
    
   int strategy = atoi(argv[1]);
   int number = atoi(argv[2]);
   int threads = atoi(argv[3]);
    
   double start = omp_get_wtime();
    
   unsigned long long sum=0;

    unsigned long long *a;
    a = (unsigned long long*)malloc(sizeof(unsigned long long)*(number+1));
    a[0] = 1;
    for(int i=1;i<number;i++){
      
        a[i] = i+1;
    }
     a[number] = 0;
    
    omp_set_num_threads(threads);
    
    if(strategy == 0){
        
        int k = number/threads;
        if(k==0){
           k = 1;
        }
        //printf("%d",k);
        unsigned long long* partialsum ;
        partialsum = (unsigned long long*) malloc(sizeof(unsigned long long)*threads);
        
        #pragma omp parallel for
        for (int i=0; i<threads; i++){
            //printf("i = %d\n",i);
            if(i == threads-1){
                int start = min(i*k,number);
                partialsum[i] = helper_func(a,start,number);
            }
            else{
                int start = min(i*k,number);
                int end = min(i*k+k,number);
                partialsum[i] = helper_func(a,start,end);
            }
        }
        #pragma omp barrier
        
        unsigned long long result = 0;
        for(int i=0; i<threads ; i++){
            result += partialsum[i];
        }
        
        free(partialsum);
        sum = result;
        
    }
    else{
        omp_set_num_threads(threads);
        int block;
        
        for(int chunk = 1; chunk <number ; chunk *= 2){
            block = 2*chunk ;
             
            #pragma omp parallel for
            for(int i=0; i<number-chunk; i+=block){
               // printf("threads %d \n", omp_get_num_threads());
                    a[i] = a[i] + a[i+chunk];
            }
            #pragma omp barrier
        }
    
        unsigned long long result = a[0];
        sum = result;
    }
    
    double end = omp_get_wtime();
    double totaltime = end-start;

    printf("%llu\n", sum);
    //printf("The time taken is : %f seconds\n", totaltime);
    free(a);
}

