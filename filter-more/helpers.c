#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <inttypes.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int blue = 0;
    int green = 0;
    int red = 0;
    int average = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // printf("%i\n", image[i][j].rgbtBlue);
            // Get RGB Values
            blue = image[i][j].rgbtBlue;
            green = image[i][j].rgbtGreen;
            red = image[i][j].rgbtRed;
            // Calculate the Average
            average = round((blue + green + red) / 3.0);
            // Adjust that particular pixel
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
       }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    uint8_t tempr = 0;
    uint8_t tempg = 0;
    uint8_t tempb = 0;
    int adj = 0;
    if (width == 1)
    {
        adj = 1;
    } else if (width % 2 == 1)
    {
        adj = (width - 1) / 2;
    } else
    {
        adj = width / 2;
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < adj; j++)
        {
            // Swap Red
            tempr = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width-j-1].rgbtRed;
            image[i][width-j-1].rgbtRed = tempr;
            // Swap Green
            tempg = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width-j-1].rgbtGreen;
            image[i][width-j-1].rgbtGreen = tempg;
            // Swap Blue
            tempb = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width-j-1].rgbtBlue;
            image[i][width-j-1].rgbtBlue = tempb;
       }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Define variables
    int min_h = 0;
    int max_h = 0;
    int min_v = 0;
    int max_v = 0;
    float sum_r = 0;
    float sum_g = 0;
    float sum_b = 0;
    float counter = 0;
    RGBTRIPLE image_copy[height][width];
    // Move throughg every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // For every pixel define the boundaries

            // Vertical
            if ( i == 0 ) {
                min_v = 0;
                max_v = i + 1;
            } else if (i == height - 1 ) {
                min_v = i - 1;
                max_v = i;
            } else {
                min_v = i - 1;
                max_v = i + 1;
            }

            //Horizontal
            if ( j == 0 ) {
                min_h = 0;
                max_h = j + 1;
            } else if (j == width - 1 ) {
                min_h = j - 1;
                max_h = j;
            } else {
                min_h = j - 1;
                max_h = j + 1;
            }

            for (int y = min_v ; y <= max_v ; y++ ) {
                for (int x = min_h ; x <= max_h ; x++ ) {
                    sum_r = sum_r + image[y][x].rgbtRed;
                    sum_g = sum_g + image[y][x].rgbtGreen;
                    sum_b = sum_b + image[y][x].rgbtBlue;
                    counter++;
                }
            }
            // Calculate Averages
            sum_r = round(sum_r / counter);
            sum_g = round(sum_g / counter);
            sum_b = round(sum_b / counter);

            // Copy Ovrt to new Image
            image_copy[i][j].rgbtRed = sum_r;
            image_copy[i][j].rgbtGreen = sum_g;
            image_copy[i][j].rgbtBlue = sum_b;
            sum_r = 0;
            sum_g = 0;
            sum_b = 0;
            counter = 0;
        }
    }
    // Move throughg every pixel and copy across the value
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = image_copy[i][j].rgbtRed;
            image[i][j].rgbtGreen = image_copy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = image_copy[i][j].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
     // Define variables
    float sum_rx = 0;
    float sum_ry = 0;
    float sum_gx = 0;
    float sum_gy = 0;
    float sum_bx = 0;
    float sum_by = 0;
    RGBTRIPLE image_copy[height + 2][width + 2];
    // Move through every pixel and copy over to the working array
    for (int i = 0; i < height + 2 ; i++)
    {
        for (int j = 0; j < width + 2 ; j++)
        {
            if (i == 0 || j == 0 || i == height + 1 || j == width + 1)
            {
                image_copy[i][j].rgbtRed = 0;
                image_copy[i][j].rgbtGreen = 0;
                image_copy[i][j].rgbtBlue = 0;
            }
            else
            {
                // Red
                image_copy[i][j].rgbtRed = image[i - 1][j - 1].rgbtRed;
                // Green
                image_copy[i][j].rgbtGreen = image[i - 1][j - 1].rgbtGreen;
                // Blue
                image_copy[i][j].rgbtBlue = image[i - 1][j - 1].rgbtBlue;
            }
        }
    }

    // Run Algorithm
    for (int y = 1; y < height + 1 ; y++)
    {
        for (int x = 1; x < width + 1 ; x++)
        {
            // Red
            sum_rx = (-1) * (image_copy[y - 1][x - 1].rgbtRed) + (-2) * (image_copy[y][x - 1].rgbtRed) +(-1) * (image_copy[y + 1][x - 1].rgbtRed) + (1) * (image_copy[y - 1][x + 1].rgbtRed) + (2) * (image_copy[y][x + 1].rgbtRed) +(1) * (image_copy[y + 1][x + 1].rgbtRed);
            sum_ry = (-1) * (image_copy[y - 1][x - 1].rgbtRed) + (-2) * (image_copy[y - 1][x].rgbtRed) +(-1) * (image_copy[y - 1][x + 1].rgbtRed) + (1) * (image_copy[y + 1][x - 1].rgbtRed) + (2) * (image_copy[y + 1][x].rgbtRed) +(1) * (image_copy[y + 1][x + 1].rgbtRed);
            if (sqrt(pow(sum_rx,2) + pow(sum_ry,2)) > 255)
            {
                image[y - 1][x - 1].rgbtRed = 255;
            }
            else
            {
                image[y - 1][x - 1].rgbtRed = round(sqrt(pow(sum_rx, 2) + pow(sum_ry, 2)));
            }
            // printf("%f is the same as %d \n", sum_r, image_working_copy_x[y][x].rgbtRed);
            // Green
            sum_gx = (-1) * (image_copy[y - 1][x - 1].rgbtGreen) + (-2) * (image_copy[y][x - 1].rgbtGreen) +(-1) * (image_copy[y + 1][x - 1].rgbtGreen) + (1) * (image_copy[y - 1][x + 1].rgbtGreen) + (2) * (image_copy[y][x + 1].rgbtGreen) +(1) * (image_copy[y + 1][x + 1].rgbtGreen);
            sum_gy = (-1) * (image_copy[y - 1][x - 1].rgbtGreen) + (-2) * (image_copy[y - 1][x].rgbtGreen) +(-1) * (image_copy[y - 1][x + 1].rgbtGreen) + (1) * (image_copy[y + 1][x - 1].rgbtGreen) + (2) * (image_copy[y + 1][x].rgbtGreen) +(1) * (image_copy[y + 1][x + 1].rgbtGreen);
            if (sqrt(pow(sum_gx, 2) + pow(sum_gy, 2)) > 255)
            {
                image[y - 1][x - 1].rgbtGreen = 255;
            }
            else
            {
                image[y - 1][x - 1].rgbtGreen = round(sqrt(pow(sum_gx, 2) + pow(sum_gy, 2)));
            }
            // Blue
            sum_bx = (-1) * (image_copy[y - 1][x - 1].rgbtBlue) + (-2) * (image_copy[y][x - 1].rgbtBlue) +(-1) * (image_copy[y + 1][x - 1].rgbtBlue) + (1) * (image_copy[y - 1][x + 1].rgbtBlue) + (2) * (image_copy[y][x + 1].rgbtBlue) +(1) * (image_copy[y + 1][x + 1].rgbtBlue);
            sum_by = (-1) * (image_copy[y - 1][x - 1].rgbtBlue) + (-2) * (image_copy[y - 1][x].rgbtBlue) +(-1) * (image_copy[y - 1][x + 1].rgbtBlue) + (1) * (image_copy[y + 1][x - 1].rgbtBlue) + (2) * (image_copy[y + 1][x].rgbtBlue) +(1) * (image_copy[y + 1][x + 1].rgbtBlue);
            if (sqrt(pow(sum_bx, 2) + pow(sum_by, 2))  > 255)
            {
                image[y - 1][x - 1].rgbtBlue = 255;
            }
            else
            {
                image[y - 1][x - 1].rgbtBlue = round(sqrt(pow(sum_bx, 2) + pow(sum_by, 2)));
            }
        }
    }
    return;
}
