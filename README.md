# fun-with-functors
How do functors, static member functions, and lambdas interact with stl containers and std algos? Heres a small driver script I built to show you :)

## Context: 
We have a list of boxes 
```
b_0[1, 5], b_1[-3, 5], b_2[7, 9], b_3[1, 5] ... b_n-1[7, 9], b_n[0, 50]
```
These boxes represet a frame captured from a camera. But we do not want to process duplicate frames. 
We need to find a way to dedupliate the list... 

## Assumptions: 
For this sandbox I assume that a box is a duplicate if its top right and bottom left coords are the same. 
```
b_x[bottom_left, top_right]
```
By that definition boxes b_0 and b_3 are duplicates (oof). 

## Soln: 
Review the code to see how to achieve some sort of deduplication :) hope this helps. 

