CSCI 103 Programming Assignment 3, Path-so-logical, Fall 2014

Name: Weiwu Pang

Email Address: weiwupan@usc.edu

NOTE: You can delete the questions, we only need your responses.

=============================== Prelab =======================================

1. What data structure will you use to remember which locations have
already been added to the queue or not?

A two-dimentional array of boolean value. B(i,j) == true means this position
has been visited.

2. At what step of the BFS algorithm do you have to mark a cell as visited?

After adding the location to queue, then mark the location that was just added
as visited. Before adding the location, firstly the program would check whether
the location is out of bound, then the program will check whether the cell was
visited before. After that, the program would add the location to queue, and 
mark the cell as visited

================================== Review ===================================

1. Describe your "mymaze.txt" test file. It should have multiple paths
of different distances. When you ran your program on it, did your program 
behave as expected?

S#F...#
.#.##.#
.#..#.#
.##.#.#
.#..#.#
.#.##.#
.#..#.#
.##.#.#
......#

The mymaze.txt has two paths with different distance. It does not work properly
when I made a mistake by trace back from the last tail item. The program should
trace back from the last 'head' item of predecessor. Finally it works.

================================ Remarks ====================================

Filling in anything here is OPTIONAL.

Approximately how long did you spend on this assignment?

: 5 hrs.

Were there any specific problems you encountered? This is especially useful to
know if you turned it in incomplete.

:

Do you have any other remarks?

:
