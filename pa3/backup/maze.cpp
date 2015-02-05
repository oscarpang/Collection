#include <iostream>
#include "maze_io.h"
using namespace std;

// Prototype for maze_search
int maze_search(char **, int, int);

int main(int argc, char *argv[])
{
  int rows, cols, result;

  if(argc < 3){
    cerr << "Usage: ./maze in_filename out_filename" << endl;
    return 1;
  }

  char** mymaze = read_maze(argv[1], &rows, &cols);

  // For checkpoint 1, just leave maze_search() unedited
  //  and the program should read in the maze, print it
  //  and write it back to the output file
  result = maze_search(mymaze, rows, cols);

  if( result == 1 ){
    cout << "Path successfully found!" << endl;
    print_maze(mymaze,rows,cols);
    write_maze(argv[2],mymaze,rows,cols);
  }
  else if (result == 0) {
    cout << "No path could be found!" << endl;
  }
  else {
    cout << "Error occurred during search!" << endl;
  }

  delete [] mymaze;

  return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if an error occurred (no start of finish
 *     cell present in the maze)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 *************************************************/
int maze_search(char **maze, int rows, int cols)
{


  // Change appropriately after Checkpoint 1 is working
  return 1;
}
