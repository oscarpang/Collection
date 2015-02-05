/*********************************************************************
File:     chromakey.cpp

Author:   Your name here

Email address:

Usage: program_name in.bmp background.bmp dist_threshold out1.bmp out2.bmp

Notes:
This program performs the chroma key operation on an input 
using two different methods.

Method 1 Utilize a user-defined distance threshold from the
	chromakey value as a discriminator

Method 2 Devise a method that to determine the chromakey mask
	that doesn't require a user-input threshold

********************************************************************/

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "bmplib.h"

using namespace std;

// Prototypes
// IMPORTANT: you must exactly use these input types, function names, and 
// return types. Otherwise the grader can't test them.
void method1(unsigned char inImage[][SIZE][RGB], bool mask[][SIZE],
		double threshold);

void method2(unsigned char inImage[][SIZE][RGB], 
		bool mask[][SIZE]);

void replace(bool mask[][SIZE],
		unsigned char inImage[][SIZE][RGB],
		unsigned char bgImage[][SIZE][RGB],
		unsigned char outImage[][SIZE][RGB]);

// Prototype one functions. 
// The function "distance"  is used to calculate the distance 
// between two vectors.
double distance(int chromaKey[],int pixel[]);



int main(int argc, char *argv[])
{
	// Image data array
	// Note: DON'T use the static keyword except where we expressly say so.
	//	It puts the large array in a separate, fixed, area of memory.
	//	It is bad practice. But useful until we have dynamic allocation.
	static unsigned char inputImage[SIZE][SIZE][RGB];
	static unsigned char bgrndImage[SIZE][SIZE][RGB];
	static unsigned char outputImage[SIZE][SIZE][RGB];
	static bool chromaMask[SIZE][SIZE];

	double threshold;

	if (argc < 6) 
	{
		cerr<<"usage: program_name in.bmp background.bmp"
		<< " dist_threshold out1.bmp out2.bmp" << endl;
		return 0;
	}
	
	if (readRGBBMP(argv[1], inputImage)) 
	{
		cerr << "Error reading file: " << argv[1] << endl;
		return 1;
	}

	if (readRGBBMP(argv[2], bgrndImage)) 
	{
		cout << "Error reading file: " << argv[2] << endl;
		return 1;
	}

	// Write code to convert the threshold (argv[3])
	//  from string format to a double and assign the 'threshold'
	threshold = atof(argv[3]);

	// Call Method 1 Function
	method1(inputImage,chromaMask,threshold);

	// Produce the output by calling replace()
	replace(chromaMask,inputImage,bgrndImage,outputImage);

	// Write the output image to a file using the filename argv[4]
	if (writeRGBBMP(argv[4], outputImage)) 
	{
		cout << "Error writing file: " << argv[4] << endl;
		exit(1);
	}	

	// Call Method 2 Function
	method2(inputImage,chromaMask);

	// Produce the output by calling replace()
	replace(chromaMask,inputImage,bgrndImage,outputImage);

	// Write the output image to a file using the filename argv[5]
	if (writeRGBBMP(argv[5], outputImage)) 
	{
		cout << "Error writing file: " << argv[5] << endl;
		exit(1);
	}	

	return 0;
}



// Use user-provided threshold for chroma-key distance
// The "output" of this method is to produce a valid mask array
//  where entries in the mask array are 1 for foreground image
//  and 0 for 'background'
void method1(unsigned char inImage[][SIZE][RGB], 
		bool mask[][SIZE],
		double threshold)
{
	// Initialize an Integer array, by each of which, I sum up
	// value of each component. chromaKey[0] contains sum of R 
	// component, and chromaKey[1] stands for G, and chromaKey[2]
	// stands for B.
	int chromaKey[3] = {0,0,0};


	// Assume that the upper-left part of the picture belongs to 
	// background, the total number of pixels I assume is
	// (256/5)*(256/5), and sum up value of R component of all pixel
	// within the area, and G and B components.
	for(int i = 0; i < SIZE/5; i++)
	{
		for(int j = 0; j < SIZE/5; j++)
		{
			for(int k = 0; k<RGB;k++)
			{
				chromaKey[k] += inImage[i][j][k];
			}
		}
	}

	// By divide each integer by the number of pixel I assume as background
	// , the array now contain the avarage value of R,G,B component of 
	// the background I assume.
	for(int i = 0; i < RGB; i++)
	{
		chromaKey[i] = chromaKey[i]/((SIZE/5)*(SIZE/5));
	}


	// Declare an integer array, which is used to contain three component
	// of every pixel within the picture.
	int pixel[3];

	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			for(int k = 0; k < RGB; k++)
			{
				// Assign the value of each component to pixel
				// in order of Red, Green, and Blue.
				pixel[k]=inImage[i][j][k];			
			}

			// Determine the distance between vector of color of each 
			// pixel and the vector of chromaKey. And compare the
			// distance with the threshold.
			// Within the threshold distance, the pixel is
			// determined as background(mask[i][j] = 0), or it is 
			// determine as foreground(mask[i][j] = 1).
			if(distance(chromaKey,pixel)<threshold)
			{
				mask[i][j]=0;
			}
			else
			{
				mask[i][j]=1;
			}
		}
	}
}


// This method utilizes statistical approach to determine the residual
// difference of three components of each pixel within the picture
// comparing to three components of chroma background, and generates 
// a threshold without user's input. This funtion utilize the function
// method 1.
void method2(unsigned char inImage[][SIZE][RGB], 
		bool mask[][SIZE])  
{
	// Initialize an integer array, by first of which will contain
	// the sum of red components of the area which is assumed as 
	// background, so as the second and third ones, containing green's
	// and blue's.
	int chromaKey[3] = {0,0,0};

	// Use for loop to sum up the each component.
	for(int i = 0; i<SIZE/5;i++)
	{
		for(int j = 0; j<SIZE/5;j++)
		{
			for(int k=0;k<RGB;k++)
			{
				chromaKey[k]+=inImage[i][j][k];
			}
		}
	}

	// Calculate the average of each component in the chroma background.
	for(int i = 0; i < RGB; i++)
	{
		chromaKey[i] = chromaKey[i]/((SIZE/5)*(SIZE/5));
	}
	

	// Declare and initialize a double array, by first of which will
	// contain the sum of the square of the difference between each red
	// components and the average red component of chroma background, so
	// as the second and the third one, which contain green's and blue's.
	double sumSquare[3] = {0,0,0};


	// Use for loop to sum up the square of difference between each 
	// pixel's component and the average component of the chroma background
	for(int i = 0; i< SIZE; i++)
	{
		for(int j = 0; j< SIZE; j++)
		{
			for(int k = 0; k<RGB; k++)
			{
				sumSquare[k] += pow((chromaKey[k]-inImage[i][j][k]),2);
			}
		}
	}
	

	// At this point the sumSquare[0] contains the sum of square of 
	// residual difference of inImage[i][j][0], which means the red channel
	// of the picture.
	// In statistical the residual of an observed value is the difference 
	// between the observed value and the estimated function value. 
	// It is always used in regression line. In the program, I assume each
	// component has a constant regression line, which is 
	// inImage[i][j][0] == chromaKey[0], and of cause the data point
	// would not stick to the line, so the sum of square of residual
	// difference would be varied according to the overall deviation of
	// each data point and the value of chromaKey.
	double result[3];

	// Divide the sum of square by total number of data points, we could 
	// get average of square of residual difference. 
	result[0] = (sumSquare[0]/(SIZE*SIZE));
	result[1] = (sumSquare[1]/(SIZE*SIZE));
	result[2] = (sumSquare[2]/(SIZE*SIZE));

	// We determine the threshold by taking the square root of sum of three
	// average value, just like processing square of difference btw two x
	// components of two vectors.
	double threshold = sqrt(result[0]+result[1]+result[2]);
	method1(inImage,mask,threshold);
	cout << threshold;
}

// If mask[i][j] = 1 use the input image pixel for the output image
// Else if mask[i][j] = 0 use the background image pixel
void replace(bool mask[SIZE][SIZE],
		unsigned char inImage[SIZE][SIZE][RGB],
		unsigned char bgImage[SIZE][SIZE][RGB],
		unsigned char outImage[SIZE][SIZE][RGB])
{
	// Create the output image using the mask to determine
	// whether to use the pixel from the Input or Background image
	for(int i = 0; i < SIZE ;i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			if(mask[i][j])
			{
				for(int k = 0; k < RGB; k++)
				{
					outImage[i][j][k] = inImage[i][j][k];
				}
			}
			else
			{
				for(int k = 0; k < RGB; k++)
				{
					outImage[i][j][k] = bgImage[i][j][k];
				}
			}
		}
	}


}

// This function calculate the distance between two vectors
double distance(int chromaKey[],
		int pixel[])
{
	int tolOfSquare = 0;
	
	// Calculate the distance according to formular
	// distance = sqrt(x^2+y^2+z^2)
	for(int i = 0; i < 3; i++)
	{
		tolOfSquare += pow((chromaKey[i]-pixel[i]),2);
	}

	return sqrt(((double)tolOfSquare));
}


