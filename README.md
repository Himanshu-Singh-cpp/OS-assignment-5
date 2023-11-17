# OS-assignment-5

******************************************************** ASSIGNMENT-5 **************************************************************

Link of the github repo: https://github.com/Singh-Himanshu-cpp/OS-assignment-5.git 

In this assignment we have implemented some essential programming efforts that are required when we want to use pthreads.
We have created this abstraction in the header file simple-multithreader.h .Whenever the user wants to use pthreads, they can 
reduce their work by including this header file, and by calling the following 2 functions:

a) void parallel_for(int low, int high, std::function<void(int)> &&lambda, int numThreads);

This function accepts a C++11 Lambda function and helps in parallelizing one-dimensional loops


b) void parallel_for(int low1, int high1, int low2, int high2, std::function<void(int, int)> &&lambda, int numThreads);

This function helps parallelize 2-dimensional loops. 1 represents the outer loop and 2 represents the inner loop above. 


To help us in our implementation, we created 2 structs:

a) thread_args:   For 1-D loops

with attributes:
1) int low
2) int high
3) std::function<void(int)> lambda

b) thread_args_2:     For 2-D loops

with attributes:
1) int low1
2) int high1
3) int low2
4) int high2
5) std::function<void(int, int)> lambda


We also created the following additional functions:

a) void *thread_function(void *ptr):   For 1D loops
b) void *thread_function_2(void *ptr):   For 2D loops


Group Members:

Himanshu Singh         2022217
Vijval Ekbote          2022569

We have both contributed equally towards this assignment.
