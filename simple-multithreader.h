#include <iostream>
#include <list>
#include <functional>
#include <stdlib.h>
#include <cstring>

#include <sys/time.h>

// struct to store the info and the lambda function
typedef struct
{
  int low;
  int high;
  std::function<void(int)> lambda;
} thread_args;

typedef struct
{
  int low1;
  int high1;
  int low2;
  int high2;
  std::function<void(int, int)> lambda;
} thread_args_2;

/*
 * Calculating the execution time taken and then printing it
 */
void print_execution_time(struct timeval start)
{
  struct timeval end;
  gettimeofday(&end, NULL);
  double execution_time;
  execution_time = (end.tv_sec - start.tv_sec);
  execution_time += (end.tv_usec - start.tv_usec) * 1e-6;
  printf("Time taken by program is : %f seconds\n", execution_time);
}

// thread function to execute lambda function in 1-d array
void *thread_function(void *ptr)
{
  thread_args *args = (thread_args *)ptr;
  for (int i = args->low; i < args->high; i++)
  {
    args->lambda(i);
  }
  return NULL;
}

void *thread_function_2(void *ptr)
{
  thread_args_2 *args = (thread_args_2 *)ptr;
  for (int i = args->low1; i < args->high1; i++)
  {
    for (int j = args->low2; j < args->high2; j++)
    {
      args->lambda(i, j);
    }
  }
  return NULL;
}

void parallel_for(int low, int high, std::function<void(int)> &&lambda, int numThreads)
{
  struct timeval start;
  gettimeofday(&start, NULL);
  int NTHREADS = numThreads;
  NTHREADS--;
  // since main thread is counted in numThreads, numThreads -1 are the number of threads that are needed to be created
  thread_args args[NTHREADS];
  int SIZE = high - low;
  pthread_t tid[NTHREADS];
  int chunk = SIZE / NTHREADS;

  // creating threads 
  for (int i = 0; i < NTHREADS; i++)
  {
    args[i].low = low + i * chunk;
    args[i].high = low + (i + 1) * chunk;
    if(SIZE%NTHREADS && i==NTHREADS-1) args[i].high=high;
    args[i].lambda = lambda;
    pthread_create(&tid[i], NULL, thread_function, &args[i]);
    // printf("low: %d high: %d\n",args[i].low,args[i].high);
  }

  // joining threads
  for (int i = 0; i < NTHREADS; i++)
  {
    pthread_join(tid[i], NULL);
  }
  print_execution_time(start);
}

void parallel_for(int low1, int high1, int low2, int high2, std::function<void(int, int)> &&lambda, int numThreads)
{
  struct timeval start;
  gettimeofday(&start, NULL);
  int NTHREADS = numThreads;
  NTHREADS--;
  // since main thread is counted in numThreads, numThreads -1 are the number of threads that are needed to be created
  thread_args_2 args[NTHREADS];
  int SIZE1 = high1 - low1;
  pthread_t tid[NTHREADS];
  int chunk1 = SIZE1 / NTHREADS;

  for (int i = 0; i < NTHREADS; i++)
  {
    args[i].low1 = low1 + i * chunk1;
    args[i].high1 = low1 + (i + 1) * chunk1;
    if(SIZE1%NTHREADS && i==NTHREADS-1) args[i].high1=high1;

    args[i].low2 = low2;
    args[i].high2 = high2;
    args[i].lambda = lambda;
    pthread_create(&tid[i], NULL, thread_function_2, &args[i]);
  }

  for (int i = 0; i < NTHREADS; i++)
  {
    pthread_join(tid[i], NULL);
  }
  print_execution_time(start);
}

int user_main(int argc, char **argv);

/* Demonstration on how to pass lambda as parameter.
 * "&&" means r-value reference. You may read about it online.
 */
void demonstration(std::function<void()> &&lambda)
{
  lambda();
}

int main(int argc, char **argv)
{
  /*
   * Declaration of a sample C++ lambda function
   * that captures variable 'x' by value and 'y'
   * by reference. Global variables are by default
   * captured by reference and are not to be supplied
   * in the capture list. Only local variables must be
   * explicity captured if they are used inside lambda.
   */
  int x = 5, y = 1;
  // Declaring a lambda expression that accepts void type parameter
  auto /*name*/ lambda1 = /*capture list*/ [/*by value*/ x, /*by reference*/ &y](void)
  {
    /* Any changes to 'x' will throw compilation error as x is captured by value */
    y = 5;
    std::cout << "====== Welcome to Assignment-" << y << " of the CSE231(A) ======\n";
    /* you can have any number of statements inside this lambda body */
  };
  // Executing the lambda function
  demonstration(lambda1); // the value of x is still 5, but the value of y is now 5

  int rc = user_main(argc, argv);

  auto /*name*/ lambda2 = [/*nothing captured*/]()
  {
    std::cout << "====== Hope you enjoyed CSE231(A) ======\n";
    /* you can have any number of statements inside this lambda body */
  };
  demonstration(lambda2);
  return rc;
}

#define main user_main
