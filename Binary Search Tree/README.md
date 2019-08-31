<Floorplan.cpp>
----------------------------------------------------------------
In this problem you will be given a set of rectangular pieces and an NxM rectangular surface with the goal of finding a layout of all those pieces such that they ALL fit within the surface without overlapping each other (like a puzzle). Each tile will have a specified length and height.

Your program should take two parameters: the first is the filename input, and the second is the filename output. You will call your program in the following manner:

    ./floorplan input.txt output.txt
The input file will be in the following format:

N M X 
ID1 l1 h1
ID2 l2 h2
...
IDX lX hX
N is the length of the surface, M is the height of the surface, X is the number of tiles you have to place, IDi is the identifying number of the ith tile, li is the length of the ith tile, and hi is the height of the ith tile. (0,0) represents the lower-left corner of the surface and (N-1, 0) represents the lower-right corner. All values will be integers. Other than a bad filename (i.e. file doesn't exist) there will be no other format errors you have to check for in this file.

You will store this data a map (first std::map then later your AVLTree). The keyType will be an integer, which will organize rectangles by their integer ID value. The valueType will be the class of type Rectangle, specified below:

struct Rectangle {
    int ID;
    int length;
    int height;
};
You must place all X tiles within the surface in such a way that no tiles overlap. You can rotate the rectangles (i.e. change their orientation), which will be accomplished by swapping a rectangle's height and length values. It is perfectly fine to have free space on the surface as long as all the rectangles fit somewhere.

Your solution will be stored in another map (again, first std::map then later your AVLTree). The keyValue of the map will be a rectangle's ID, and the valueType will be a pair of integers, indicating the lower-left coordinate of the tile's location. The orientation of the rectangle does not need to be stored explicitly but will be reflected by the current height and length.

Your program should solve this problem using a backtracking search. Probably the easiest way to accomplish this (though there are others) is to recurse over all rectangles. Try to place the tile in any available coordinate. If no coordinate works, you should backtrack.

Don't forget you can rotate a tile by swapping its height and length values (i.e. when you try to place it you would need to try both orientations before declaring failure).

If all tiles are placed, then you should print the contents of your solution using the following format:

ID1 x1 y1 l1 h1\
ID2 x2 y2 l2 h2\
...\
IDX xX yX lX hX\
(xi, yi) are the bottom left coordinates of tile i, li is the length of tile i, and hi is the height of tile i.

If you exhaustively search all possibilities and find no solution, you should output No solution found..

In either case, your program should terminate when it finds a solution or is unable to find a solution. You do not need to output all possible solutions.

Examples:
Input:

10 10 2\
576 10 5\
297 4 10\
Possible Output:

297 0 0 4 10\
576 4 0 5 10\
Rectangle 576 is rotated so as to fit in the above example.

Input:

5 5 2\
17 3 3\
29 3 3\
Necessary Output:

No solution found.
Input:

6 6 4
42 3 5
56 6 1
79 5 1
89 5 2
Possible Output:

42 0 0 3 5\
56 0 5 6 1\
79 3 0 1 5\
89 4 0 2 5
