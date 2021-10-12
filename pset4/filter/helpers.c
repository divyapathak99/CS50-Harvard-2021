#include "helpers.h"
#include <math.h>
#include<stdio.h>
#include <cs50.h>

typedef struct
{
    int rgbtRed;
    int rgbtBlue;
    int rgbtGreen;
}
pixel_values;


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avg_pixel = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //calculating average and rounding it to the nearest integer.
            avg_pixel = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/ (float)3);
            image[i][j].rgbtBlue = avg_pixel;
            image[i][j].rgbtGreen = avg_pixel;
            image[i][j].rgbtRed = avg_pixel;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            //swapping array of pixels.
            temp = image[i][width - 1 - j];
            image[i][width - 1 - j] = image[i][j];
            image[i][j] =  temp;
        }
    }
    return;
}

// Blur image

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    //make a temp matrix to store store the new values of image[i][j].
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j].rgbtRed = 0;
            temp[i][j].rgbtBlue = 0;
            temp[i][j].rgbtGreen = 0;

        }
    }
    float count = 0;
    pixel_values sum_pixel;
    //initialising sum_pixel to 0.
    sum_pixel.rgbtRed = 0;
    sum_pixel.rgbtGreen = 0;
    sum_pixel.rgbtBlue = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //loop k and l will collects neighbour pixels and then will find the averages.
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    //check if finding neighbour pixel does not exceeds the size of image[i][j].
                    if (k >= 0 && l >= 0 && k < height && l < width)
                    {
                        sum_pixel.rgbtRed += image[k][l].rgbtRed;
                        sum_pixel.rgbtGreen += image[k][l].rgbtGreen;
                        sum_pixel.rgbtBlue += image[k][l].rgbtBlue;
                        count += 1;
                    }

                }
            }
            temp[i][j].rgbtRed = round(sum_pixel.rgbtRed / count);
            temp[i][j].rgbtGreen = round(sum_pixel.rgbtGreen / count);
            temp[i][j].rgbtBlue = round(sum_pixel.rgbtBlue / count);

            count = 0;
            sum_pixel.rgbtRed = 0;
            sum_pixel.rgbtGreen = 0;
            sum_pixel.rgbtBlue = 0;
        }
    }
    
    //finally copying final results back to image.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];

        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j].rgbtRed = 0;
            temp[i][j].rgbtBlue = 0;
            temp[i][j].rgbtGreen = 0;

        }
    }
    //create sobel operator matrix along x axis.
    int operator_x[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int operator_y[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    float count = 0;
    pixel_values gx;
    pixel_values gy;
    pixel_values G;
    //initialisation of gx and gy values.
    gx.rgbtRed = 0;
    gx.rgbtGreen = 0;
    gx.rgbtBlue = 0;
    gy.rgbtRed = 0;
    gy.rgbtGreen = 0;
    gy.rgbtBlue = 0;

    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //loop k and l will collects neighbour pixels and then will operate them with sobal operator.
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    //check if finding neighbour pixel does not exceeds the size of image[i][j].
                    if (k >= 0 && l >= 0 && k < height && l < width)
                    {
                        gx.rgbtRed += image[k][l].rgbtRed * operator_x[k - (i - 1)][l - (j - 1)];
                        gy.rgbtRed += image[k][l].rgbtRed * operator_y[k - (i - 1)][l - (j - 1)];
                        gx.rgbtBlue += image[k][l].rgbtBlue * operator_x[k - (i - 1)][l - (j - 1)];
                        gy.rgbtBlue += image[k][l].rgbtBlue * operator_y[k - (i - 1)][l - (j - 1)];
                        gx.rgbtGreen += image[k][l].rgbtGreen * operator_x[k - (i - 1)][l - (j - 1)];
                        gy.rgbtGreen += image[k][l].rgbtGreen * operator_y[k - (i - 1)][l - (j - 1)];

                    }
                    else
                    {
                        //treating pixel at the edge and corner as a solid black pixels.
                        gx.rgbtRed += 0;
                        gy.rgbtRed += 0;
                        gx.rgbtBlue += 0;
                        gy.rgbtBlue += 0;
                        gx.rgbtGreen += 0;
                        gy.rgbtGreen += 0;
                    }

                }
            }
            //finding the final value and rounding it to the nearest integer.
            G.rgbtRed = round(sqrt(pow(gx.rgbtRed, 2) + pow(gy.rgbtRed, 2)));
            G.rgbtGreen = round(sqrt(pow(gx.rgbtGreen, 2) + pow(gy.rgbtGreen, 2)));
            G.rgbtBlue = round(sqrt(pow(gx.rgbtBlue, 2) + pow(gy.rgbtBlue, 2)));
            //making final value capped at 255, if it exceeds the size!
            //for Red rgbt value of pixel.
            if (G.rgbtRed > 255)
            {
                temp[i][j].rgbtRed = 255;
            }
            else
            {
                temp[i][j].rgbtRed = G.rgbtRed;

            }
            //for green rgbt value of pixel.
            if (G.rgbtGreen > 255)
            {
                temp[i][j].rgbtGreen = 255;
            }
            else
            {
                temp[i][j].rgbtGreen = G.rgbtGreen;

            }
            //for blue rgbt value of pixel.
            if (G.rgbtBlue > 255)
            {
                temp[i][j].rgbtBlue = 255;
            }
            else
            {
                temp[i][j].rgbtBlue = G.rgbtBlue;

            }

            gx.rgbtRed = 0;
            gx.rgbtGreen = 0;
            gx.rgbtBlue = 0;
            gy.rgbtRed = 0;
            gy.rgbtGreen = 0;
            gy.rgbtBlue = 0;
        }
    }
    
    //finally copying final results back to image.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j] ;

        }
    }

    return;
}
