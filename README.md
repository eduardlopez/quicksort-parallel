# quicksort-parallel
Parallel quicksort algorithm implemented in OpenMP 

<br/>
##Execution demo:
Some technical info of the computer:


<table>
  <tbody>
    <tr>
      <td>Processor</td>
      <td>Intel Core i7 950 (4 Cores x 2 Threads per core = 8 Hardware Threads)</td>
    </tr>
    <tr>
      <td>Processor frequency</td>
      <td>Base:3.06Ghz, Turbo:3.33GHz</td>
    </tr>
    <tr>
      <td>DRAM</td>
      <td>6 GBytes</td>
    </tr>
    <tr>
      <td>Cache</td>
      <td>L3:8MB, L2:256KB, L1:32KB</td>
    </tr>
    <tr>
      <td>OS</td>
      <td>Scientific Linux release 6.7 (Carbon)</td>
    </tr>
    <tr>
      <td>Compiler</td>
      <td>gcc version 4.9.0 (GCC)</td>
    </tr>
  </tbody>
</table>


<br/>
####Compilation:
```
gcc -O3 -fopenmp quicksort-demo-comparison.c -o quicksort-demo-comparison
```
####Execution:
```
./quicksort-demo-comparison
```
####Output Result:
```
Size of the array (aprox.): 1000 MBytes
TOTAL MEMORY ALLOCATED:  3 x array = (aprox.): 3000 MBytes

Initializing the arrays with random numbers...
Initialization complete

Sorting with serial 'qsort' function of 'stdlib.h' ...
Sorted in (aprox.): 45.110000 seconds


Sorting with custom serial QuickSort...
Sorted in (aprox.): 33.530000 seconds


Sorting with custom PARALLEL QuickSort...
Sorted in (aprox.): 6.699294 seconds


Checking if the results are correct...
The result with 'custom serial QuickSort' is CORRECT
The result with 'custom PARALLEL QuickSort' is CORRECT
```

