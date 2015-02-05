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
    ifstream ifile (filename);
    ifile >> *rows;
    ifile >> *cols;

    ifile.seekg(1,ios_base::cur); 
    char** maze = new char*[*rows];

    for(int i = 0; i < *rows; i++)
    {
        maze[i] = new char[*cols];
        for(int j = 0; j < *cols; j++)
        {
            ifile >> maze[i][j];
        }
    } 

    ifile.close();
    return maze;

}

/*************************************************
 * Print the maze contents in a 2D format to the
 * screen
 *
 *************************************************/
void print_maze(char **maze, int rows, int cols)
{
    cout << rows << " " << cols << endl;

    for(int i = 0; i<rows; i++)
    {
        for(int j = 0; j< cols; j++)
        {
            cout << maze[i][j];
        }
        cout << endl;
    }

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
    
    ofstream ofile (filename);

    ofile << rows << " " << cols << endl;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            ofile << maze[i][j];
        }
        ofile << endl;
    }
    
    ofile.close();


}
