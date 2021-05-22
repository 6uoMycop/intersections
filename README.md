# intersections

Program takes set of points which represent a circuit.
Prints out number of intersections between these segments.

## USAGE:

<executable_name>.exe <path/to/file/with/segments/data>.csv

## FILE FORMAT:

every line represents a point (x_i,y_i)

coordinates are positive integer values

first point MUST be the same as last point

minimum 3 points allowed, "void" sections (x,y),(x,y) where both points are the same don't allowed

### EXAMPLE FILE:

    3,9
    156,2
    29,0
    3,9


## Example test cases:

### File 0:

    1,1
    1,11
    11,1
    5,5
    1,1

### Output:

    Number of intersections: 0

### Graph plot:

![alt text](https://github.com/6uoMycop/intersections/raw/master/graph0.png)


### File 1:

    1,1
    1,11
    8,1
    8,11
    1,1

### Output:

    Number of intersections: 1

### Graph plot:

![alt text](https://github.com/6uoMycop/intersections/raw/master/graph1.png)


### File 2:

    1,1
    1,11
    11,11
    11,1
    3,20
    1,1

### Output:

    Number of intersections: 2

### Graph plot:

![alt text](https://github.com/6uoMycop/intersections/raw/master/graph2.png)


### File 3:

    1,1
    1,11
    11,1
    11,4
    4,1
    9,7
    1,1

### Output:

    Number of intersections: 3

### Graph plot:

![alt text](https://github.com/6uoMycop/intersections/raw/master/graph3.png)

