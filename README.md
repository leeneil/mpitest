# mpitest
Some test scripts for MPI

# Compilation

```
 mpicxx pi.cpp -o pi
 ```
 
# Run
 
## Use default N = 1000
 ```
$ mpirun -np 24 ./pi
N = 1000
pi = 3.188
Time elasped: 0
```


## Use user-specific N
```
$ mpirun -np 24 ./pi 999999999
N = 999999999
pi = 3.14159
Time elasped: 34
```
