#include <iostream>
#include <fstream>
#include "maze_io.h"

using namespace std;

/*************************************************
 * Open the file specified by filename, and read the 
 * maze into a dynamically allocated array.
 * 
 * Return the 2D array pointer (don't delete it..
 * we'll do that in main() ).  Return NULL if
 * you are unable to open the file or can't read
 * the dimensions.
 *
 * We also pass in two pointers to integers. Fill 
 *  the integers pointed to by these arguments
 *  with the number of rows and columns 
 *  read by from the file (first two value
 *  in the file)
 *
 *************************************************/

char ** read_maze(char *filename, int *rows, int *cols )
{



}

/*************************************************
 * Print the maze contents in a 2D format to the
 * screen
 *
 *************************************************/
void print_maze(char **maze, int rows, int cols)
{


}

/*************************************************
 * Write maze should open the file specified by 
 * filename and write the contents of the maze
 * array to the file with the dimensions on the first
 * line.
 *
 *************************************************/
void write_maze(char *filename, char **maze, int rows, int cols)
{



}
