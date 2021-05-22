# intersections

Program takes set of segments which represent a circuit.
Prints out number of intersections between these segments.

## USAGE:

<executable_name>.exe <path/to/file/with/segments/data>.csv

## FILE FORMAT:

every line represents vector ((x1_i,y1_i),(x2_i,y2_i))

coordinates are positive integer values

second point of  i-th   vector MUST be the same as first point of  i+1-th      vector

second point of  first  vector MUST be the same as first point of  the last    vector

    <x1_1>,<y1_1>,<x2_1>,<y2_1>
    <x2_1>,<y2_1>,<x2_2>,<y2_2>
    ...
    <xn_1>,<yn_1>,<x1_1>,<y1_1>

### EXAMPLE FILE:
    3,9,156,2
    156,2,29,0
    29,0,3,9


## Example test cases:


### File 1:

    1,1,1,11
    1,11,8,1
    8,1,8,11
    8,11,1,1

### Output:

    Number of intersections: 1

### Graph plot:

![alt text](https://github.com/6uoMycop/intersections/raw/master/graph1.png)


### File 2:

    1,1,1,11
    1,11,11,11
    11,11,11,1
    11,1,3,20
    3,20,1,1

### Output:

    Number of intersections: 2

### Graph plot:

![alt text](https://github.com/6uoMycop/intersections/raw/master/graph2.png)


### File 3:

    1,1,1,11
    1,11,11,1
    11,1,11,4
    11,4,4,1
    4,1,9,7
    9,7,1,1

### Output:

    Number of intersections: 3

### Graph plot:

![alt text](https://github.com/6uoMycop/intersections/raw/master/graph3.png)

