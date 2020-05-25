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
                float average;
                average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
                
                //  Round to nearest int
                int grayscale = round(average);
                
                //  Set all values to the average
                image[i][j].rgbtRed = grayscale;
                image[i][j].rgbtGreen = grayscale;
                image[i][j].rgbtBlue = grayscale;
                
            }
        }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    
    //  Calculate new color value for each pixel
    //  Loop through each row in image
    for (int i = 0; i < height; i++)
        {
            //  Loop through each pixel in row
            for (int j = 0; j < width; j++)
            {
                // Set original RGB-values
                float originalRed = image[i][j].rgbtRed;
                float originalGreen = image[i][j].rgbtGreen;
                float originalBlue = image[i][j].rgbtBlue;
                
                //  Calculate Sepia RGB-values
                int SepiaRed = round((.393 * originalRed) + (.769 * originalGreen) + (.189 * originalBlue));
                int SepiaGreen = round((.349 * originalRed) + (.686 * originalGreen) + (.168 * originalBlue));
                int SepiaBlue = round((.272 * originalRed) + (.534 * originalGreen) + (.131 * originalBlue));
            
                // Insure that result is an int between 0-255
                
                if (SepiaRed > 255)
                    SepiaRed = 255;
                    
                if (SepiaGreen > 255)
                    SepiaGreen = 255;    
                
                if (SepiaBlue > 255)
                    SepiaBlue = 255;
                    
                //  Set all values to the corresponding sepia-value
                image[i][j].rgbtRed = SepiaRed;
                image[i][j].rgbtGreen = SepiaGreen;
                image[i][j].rgbtBlue = SepiaBlue;
            }
        }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //  Temporary array for swapping pixels
    RGBTRIPLE swap[height][width];  
    
    //  Loop through each row in image
    for (int i = 0; i < height; i++)
    {
        //  Loop through each pixel in row up to the middle pixel ( == width/2)
        for (int j = 0; j < width / 2; j++)
        {
            
            // Copy to temporary array
            swap[i][j] = image[i][j];
            
            //  Swap i with value on opposite side
            image[i][j] = image[i][width - j];
            
            //  Swap temp value with value on opposite side
            image[i][width - j] = swap[i][j];
           
        }
    }
            
    
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
