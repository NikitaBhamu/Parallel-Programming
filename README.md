# Parallel-Programming
This repository contains two assignments of the course Parallel-Programming.<br /><br />
## Assignment 1 :- 
This assignment is about parallelising the sum of first N natural numbers using two different strategies and then analysing their performance.<br /><br />
-> Strategy 0 is the approach in which we calculate the partial sums of the n/p  partitions and then add those partial sums sequentially.<br />
-> Strategy 1 is the approach in which a downward heap is formed if we draw the steps.<br /><br />
### Assignment 2 :- 
This assignment is about parallelising the Crout matrix decomposition using four different strategies and then analysing their performance.<br /><br />
-> Strategy 0 :-  It is the sequential code provided for LU decomposition in this assignment.<br />
-> Strategy 1 :- In this strategy the “parallel for” construct of the openmp library is used.<br />
-> Strategy 2 :- In this strategy the “sections” construct of the openmp library is used.<br />
-> Strategy 3 :- In this strategy the “parallel for” and “sections” construct of the openmp library are used together.<br />
-> Strategy 4 :- In this strategy the “mpi interface” of the mpi library has been used.<br />
