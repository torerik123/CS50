#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //  Loop through each row in image
    for (int i = 0; i < height; i++)
        {
            //  Loop through each pixel in row
            for (int j = 0; j < width; j++)
            {
                //  Find average of pixel value red, green and blue values
                int average;
                average = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue / 3;
                
                //  Round to nearest int    
                average = round(average);
                
                //  Set all values to the average
                image[i][j].rgbtRed = average;
                image[i][j].rgbtGreen = average;
                image[i][j].rgbtBlue = average;
                
            }
        }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
