#include <iostream>
#include "maze_io.h"
using namespace std;

// Prototype for maze_search
int maze_search(char **, int, int);
int** expand(int* loc,char rows, char cols);
int** validLoc(int** locs);
int numValid(int** locs);

int main(int argc, char *argv[])
{
	int rows, cols, result;

	if(argc < 3)
	{
		cerr << "Usage: ./maze in_filename out_filename" << endl;
		return 1;
	}

	char** mymaze = read_maze(argv[1], &rows, &cols);

	// For checkpoint 1, just leave maze_search() unedited
	//  and the program should read in the maze, print it
	//  and write it back to the output file
	result = maze_search(mymaze, rows, cols);

	if( result == 1 )
	{
		cout << "Path successfully found!" << endl;
		print_maze(mymaze,rows,cols);
		write_maze(argv[2],mymaze,rows,cols);
	}
	else if (result == 0) 
	{
		cout << "No path could be found!" << endl;
	}
	else 
	{
		cout << "Error occurred during search!" << endl;
	}

	for(int i = 0; i < rows; i++)
	{
		delete [] mymaze[i];
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
	//Declare two array, each of which contains two elements(coordinate
	// of start and finish point).
	int start[2];
	int finish[2];

	//Initialize two boolean value to be false to test whether the
	// start and finish point are found.
	bool findStr=false;
	bool findFin=false;

	//Declare a variable to return whether a path is found.
	int result;


	//Search for start and finish point.
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			if(maze[i][j]=='S')
			{
				start[0]=i;
				start[1]=j;
				findStr=true;

			}
			else if(maze[i][j]=='F')
			{
				finish[0]=i;
				finish[1]=j;
				findFin=true;
			}
		}
	}


	//If either one is not found, return -1 and prompt to user.
	if(!(findStr&&findFin))
	{
		return -1;
	}


	//Declare a two-dimentional bool array to record the infomation about
	// whether a specific point has been visited.
	bool** footprint = new bool*[rows];

	//Initialize each point to be false, namely, not visited.
	for(int i = 0; i < rows; i++)
	{
		footprint[i] = new bool[cols];
		
		for(int j = 0; j < cols; j++)
		{
			footprint[i][j] = false;
		}
	}

	//Assign 'true' to the start point.
	footprint[start[0]][start[1]] = true;



	//Initialize a array with length "rows*cols", which is the maximum
	// length of the maze given the rows and cols. Each item of the array
	// is two-element array, the first element is the index of row, and the
	// second element is the index of col.
	int** queue = new int*[rows*cols];

	//Initialize each item with value {-1,-1}.
	for(int i = 0; i < rows*cols; i++)
	{
		queue[i] = new int[2];
		queue[i][0] = -1;
		queue[i][1] = -1;
	}

	//Declare a predecessor array to record predecessor of each item the
	// program search. The arrat is used to find the actual path.
	int* prede = new int[rows*cols];


	//Initialize the first item in the queue with the information of the 
	// start point. And initialize the first item in the prede array as
	// -1, which means it dose not have predecessor.
	queue[0][0] = start[0];
	queue[0][1] = start[1];
	prede[0] = -1;

	//Initialize two variable, head to record the front element, and tail
	// to record the back element.
	int head = 0;
	int tail = 1;

	//A while loop always run.
	while(true)
	{

		//If head >= tail, means that the queue is empty and no path
		// is found, break the loop and set the result to 0;
		if(head >= tail)
		{
			result = 0;
			break;
		}


		//If the head element store the same information as the finish
		// point's, we find the finish point, so break the while loop,
		// and set the result to 1.
		if(queue[head][0]==finish[0]&&queue[head][1]==finish[1])
		{
			result = 1;
			break;
		}


		//Check whether the head element is '#', which means wall in
		// the maze. If not, search the neighbor elements of the head
		// element and add them to the queue.
		if(maze[queue[head][0]][queue[head][1]] != '#')
		{

			//Search the neighbor elements, the expand function
			// will return a 4-item array including invalid points,
			// which are points out of bound and have mark that both
			// row and col equals to -1.
			int** around = expand(queue[head],rows,cols);

			//Check for valid locations in the 'around' array, and
			// return all the valid location as a new array. And
			// count the number of valid locations.
			int** locs = validLoc(around);
			int numLocs = numValid(around);


			//Use a for loop to add the valid neighbor points to
			// the queue.
			for(int i = 0; i < numLocs; i++)
			{

				//Check whether the neighbor points have been
				// visited. If not, add the points to the queue
				if(!footprint[locs[i][0]][locs[i][1]])
				{

					queue[tail][0] = locs[i][0];
					queue[tail][1] = locs[i][1];

					//Set the element with identical index
					// in predecessor array to head.
					prede[tail] = head;
	
					//Record that the program has visited
					// the point.
					footprint[locs[i][0]][locs[i][1]] = true;

					tail++;
				}
			}
			

			//Free the memory allocated to the location array.
			for(int i = 0; i < numLocs; i++)
			{
				delete [] locs[i];
			}
			delete [] locs;

			for(int i = 0; i < 4; i++)
			{
				delete [] around[i];
			}
			delete [] around;
		}

		head+=1;

	}

	//Backtracing the path by the array prede.
	int i = prede[head];
	while(i!=0)
	{
		maze[queue[i][0]][queue[i][1]] = '*';
		i = prede[i];
	}


	//Free the memory allocate to queue, prede and footprint.
	for(int j = 0; j < rows*cols; j++)
	{
		delete [] queue[j];
	}
	delete [] queue;

	delete [] prede;

	for(int j = 0; j < rows; j++)
	{
		delete [] footprint[j];
	}
	delete [] footprint;


	return result;
}

//This function explore four direction of the current location, and grab a
// location from each direction. If a location is out of bound, it would set
// defaultly as (-1,-1).
int** expand(int* loc, char rows, char cols)
{
	int y = loc[0];
	int x = loc[1];

	//Initialize a four-element array to store four locations.
	int** fourDirec = new int*[4];
	for(int i = 0; i < 4; i++)
	{
		fourDirec[i] = new int[2];
		fourDirec[i][0] = -1;
		fourDirec[i][1] = -1;
	}


	//Explore one step forward to each four direction.
	if((y-1 >= 0) && (x >= 0) && (y - 1 < rows) && (x < cols))
	{
		fourDirec[0][0] = y-1;
		fourDirec[0][1] = x;
	}
	if((y >= 0) && (x+1 >= 0) && (y < rows) && (x+1 < cols))
	{
		fourDirec[1][0] = y;
		fourDirec[1][1] = x+1;
	}
	if((y >= 0) && (x-1 >= 0) && (y < rows) && (x-1 < cols))
	{
		fourDirec[2][0] = y;
		fourDirec[2][1] = x-1;
	}
	if((y+1 >= 0) && (x >= 0) && (y+1 < rows) && (x < cols))
	{
		fourDirec[3][0] = y+1;
		fourDirec[3][1] = x;
	}

	return fourDirec;
}


//Return the number of valid location.
int numValid(int** locs)
{

	int count = 0;
	for(int i = 0; i<4; i++)
	{
		if(locs[i][0]!=-1)
		{
			count++;
		}
	}
	return count;
}


//Validate the location array, and return the array that contains all valid
// locations.
int** validLoc(int** locs)
{
	//Declare a bool array to check every single element's validablity
	// and a count to record the number of valid locs.
	bool valid[4];
	int count = 0;

	//Traverse the array, and mark whether the element is valid. And count
	// up.
	for(int i = 0; i<4; i++)
	{
		if(locs[i][0]!=-1)
		{
			count++;
			valid[i] = true;
		}
		else
		{
			valid[i] = false;
		}
	}


	//Initialize a array to contain the valid locations.
	int** validLocs = new int*[count];
	
	//Traverse the original array again, and assign every valid location
	// to the new array.
	int j = 0;
	for(int i = 0; i < count; i++)
	{
		//When the item is not valid, go to next valid element.
		if(j< 4 && !valid[j])
		{
			while( j<4 && !valid[j])
			{
				j++;
			}
		}

		//Store the info of valid locations to new array.
		validLocs[i] = new int[2];	
		validLocs[i][0] = locs[j][0];
		validLocs[i][1] = locs[j][1];
		j++;
		
	}

	return validLocs;

}

