#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average;

    // Iterate over rows
    for (int j = 0; j < height; j++)
    {
        // Iterate over rows` pixels
        for (int i = 0; i < width; i++)
        {

            // Skip pixels that are already in grayscale
            if (image[j][i].rgbtBlue == image[j][i].rgbtGreen && image[j][i].rgbtBlue == image[j][i].rgbtRed)
            {
                continue;
            }
            // Convert pixels to grayscale
            else
            {
                // Calculate average
                average = (image[j][i].rgbtBlue + image[j][i].rgbtGreen + image[j][i].rgbtRed) / (float)3;

                // Assign new values for each color
                image[j][i].rgbtBlue = image[j][i].rgbtGreen = image[j][i].rgbtRed = round(average);
            }
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Deckare a temp original row array
    RGBTRIPLE temp[width];

    // Iterate over rows
    for (int j = 0; j < height; j++)
    {
        // Save a temp array for original row
        for (int i = 0; i < width; i++)
        {
            temp[i] = image[j][i];
        }

        // Assign new values for row
        for (int i = 0; i < width; i++)
        {
            image[j][i].rgbtBlue = temp[(width - 1) - i].rgbtBlue;
            image[j][i].rgbtGreen = temp[(width - 1) - i].rgbtGreen;
            image[j][i].rgbtRed = temp[(width - 1) - i].rgbtRed;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Declare a temp original image 2d array
    RGBTRIPLE temp[height][width];

    // Save a temp image 2d array
    for (int j = 0; j < height; j++)
    {
        // Save a temp array for original row
        for (int i = 0; i < width; i++)
        {
            temp[j][i] = image[j][i];
        }
    }

    // Declare variables
    int count;
    float averageBlue, averageGreen, averageRed;
    int sumBlue, sumGreen, sumRed;

    // Iterate over rows
    for (int j = 0; j < height; j++)
    {
        // Iterate over the pixels of the rows
        for (int i = 0; i < width; i++)
        {
            // Set variables to 0
            count = 0;
            averageBlue = averageGreen = averageRed = 0;
            sumBlue = sumGreen = sumRed = 0;

            // Iterate over the 9 pixels box rows
            for (int y = j - 1; y < j + 2; y++)
            {
                // Iterate over the pixels of the box rows
                for (int x = i - 1; x < i + 2; x++)
                {
                    // Skip pixels that are outside the image
                    if (y < 0 || y >= height || x < 0 || x >= width)
                    {
                        continue;
                    }

                    // Convert pixels to blur
                    else
                    {
                        sumBlue += temp[y][x].rgbtBlue;
                        sumGreen += temp[y][x].rgbtGreen;
                        sumRed += temp[y][x].rgbtRed;

                        // Increment count
                        count++;
                    }
                }
            }

            // Calculate averages
            averageBlue = sumBlue / (float)count;
            averageGreen = sumGreen / (float)count;
            averageRed = sumRed / (float)count;

            // Set new image pixel
            image[j][i].rgbtBlue = round(averageBlue);
            image[j][i].rgbtGreen = round(averageGreen);
            image[j][i].rgbtRed = round(averageRed);
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Declare a temp original image 2d array
    RGBTRIPLE temp[height][width];

    // Save a temp image 2d array
    for (int j = 0; j < height; j++)
    {
        // Save a temp array for original row
        for (int i = 0; i < width; i++)
        {
            temp[j][i] = image[j][i];
        }
    }

    // Declare variables
    int count;
    int GxGreen, GyGreen, GxBlue, GyBlue, GxRed, GyRed;
    int newBlue, newGreen, newRed;

    // temp[3][3].rgbtBlue = 0;
    // temp[3][4].rgbtBlue = 128;
    // temp[3][5].rgbtBlue = 255;
    // temp[4][3].rgbtBlue = 0;
    // temp[4][4].rgbtBlue = 128;
    // temp[4][5].rgbtBlue = 255;
    // temp[5][3].rgbtBlue = 0;
    // temp[5][4].rgbtBlue = 128;
    // temp[5][5].rgbtBlue = 255;

    // Iterate over rows
    for (int j = 0; j < height; j++)
    {
        // Iterate over the pixels of the rows
        for (int i = 0; i < width; i++)
        {
            // Set variables to 0
            count = 0;
            GxGreen = GyGreen = GxBlue = GyBlue = GxRed = GyRed = 0;

            // Iterate over the 9 pixels box rows
            for (int y = j - 1; y < j + 2; y++)
            {
                // Iterate over the pixels of the box rows
                for (int x = i - 1; x < i + 2; x++)
                {
                    switch (count)
                    {
                        // Box pixel [0][0]
                        case 0:
                            if (y < 0 || x < 0)
                            {
                                break;
                            }
                            else
                            {
                                GxGreen += (-1) * temp[y][x].rgbtGreen;
                                GyGreen += (-1) * temp[y][x].rgbtGreen;
                                GxBlue += (-1) * temp[y][x].rgbtBlue;
                                GyBlue += (-1) * temp[y][x].rgbtBlue;
                                GxRed += (-1) * temp[y][x].rgbtRed;
                                GyRed += (-1) * temp[y][x].rgbtRed;

                                break;
                            }



                        // Box pixel [0][1]
                        case 1:
                            if (y < 0)
                            {
                                break;
                            }
                            else
                            {
                                GyGreen += (-2) * temp[y][x].rgbtGreen;
                                GyBlue += (-2) * temp[y][x].rgbtBlue;
                                GyRed += (-2) * temp[y][x].rgbtRed;

                                break;
                            }

                        // Box pixel [0][2]
                        case 2:
                            if (y < 0 || x >= width)
                            {
                                break;
                            }
                            else
                            {
                                GxGreen += temp[y][x].rgbtGreen;
                                GyGreen += (-1) * temp[y][x].rgbtGreen;
                                GxBlue += temp[y][x].rgbtBlue;
                                GyBlue += (-1) * temp[y][x].rgbtBlue;
                                GxRed += temp[y][x].rgbtRed;
                                GyRed += (-1) * temp[y][x].rgbtRed;

                                break;
                            }

                        // Box pixel [1][0]
                        case 3:
                            if (x < 0)
                            {
                                break;
                            }
                            else
                            {
                                GxGreen += (-2) * temp[y][x].rgbtGreen;
                                GxBlue += (-2) * temp[y][x].rgbtBlue;
                                GxRed += (-2) * temp[y][x].rgbtRed;

                                break;
                            }

                        // Box pixel [1][2]
                        case 5:
                            if (x >= width)
                            {
                                break;
                            }
                            else
                            {
                                GxGreen += 2 * temp[y][x].rgbtGreen;
                                GxBlue += 2 * temp[y][x].rgbtBlue;
                                GxRed += 2 * temp[y][x].rgbtRed;

                                break;
                            }

                        // Box pixel [2][0]
                        case 6:
                            if (y >= height || x < 0)
                            {
                                break;
                            }
                            else
                            {
                                GxGreen += (-1) * temp[y][x].rgbtGreen;
                                GyGreen += temp[y][x].rgbtGreen;
                                GxBlue += (-1) * temp[y][x].rgbtBlue;
                                GyBlue += temp[y][x].rgbtBlue;
                                GxRed += (-1) * temp[y][x].rgbtRed;
                                GyRed += temp[y][x].rgbtRed;

                                break;
                            }

                        // Box pixel [2][1]
                        case 7:
                            if (y >= height)
                            {
                                break;
                            }
                            else
                            {
                                GyGreen += 2 * temp[y][x].rgbtGreen;
                                GyBlue += 2 * temp[y][x].rgbtBlue;
                                GyRed += 2 * temp[y][x].rgbtRed;

                                break;
                            }

                        // Box pixel [2][2]
                        case 8:
                            if (y >= height || x >= width)
                            {
                                break;
                            }
                            else
                            {
                                GxGreen += temp[y][x].rgbtGreen;
                                GyGreen += temp[y][x].rgbtGreen;
                                GxBlue += temp[y][x].rgbtBlue;
                                GyBlue += temp[y][x].rgbtBlue;
                                GxRed += temp[y][x].rgbtRed;
                                GyRed += temp[y][x].rgbtRed;

                                break;
                            }
                    }

                    count++;
                }
            }

            // printf("GxGreen = %i\n", GxGreen);
            // printf("GyGreen = %i\n", GyGreen);
            // printf("GxBlue = %i\n", GxBlue);
            // printf("GyBlue = %i\n", GyBlue);
            // printf("GxRed = %i\n", GxRed);
            // printf("GyRed = %i\n", GyRed);


            // Calculate Square root of Gx^2 + Gy^2 for each channel
            newBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
            newGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
            newRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));

            // // Set new image pixel

            // Assign new values for each color
            if (newBlue > 255)
            {
                image[j][i].rgbtBlue = 255;
            }
            else
            {
                image[j][i].rgbtBlue = newBlue;
            }

            if (newGreen > 255)
            {
                image[j][i].rgbtGreen = 255;
            }
            else
            {
                image[j][i].rgbtGreen = newGreen;
            }

            if (newRed > 255)
            {
                image[j][i].rgbtRed = 255;
            }
            else
            {
                image[j][i].rgbtRed = newRed;
            }
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed, sepiaGreen, sepiaBlue;

    // Iterate over rows
    for (int j = 0; j < height; j++)
    {
        // Iterate over rows` pixels
        for (int i = 0; i < width; i++)
        {
            // Calculate Sepia Formula
            sepiaBlue = .272 * image[j][i].rgbtRed + .534 * image[j][i].rgbtGreen + .131 * image[j][i].rgbtBlue;
            sepiaGreen = .349 * image[j][i].rgbtRed + .686 * image[j][i].rgbtGreen + .168 * image[j][i].rgbtBlue;
            sepiaRed = .393 * image[j][i].rgbtRed + .769 * image[j][i].rgbtGreen + .189 * image[j][i].rgbtBlue;

            // Assign new values for each color
            if (round(sepiaBlue) > 255)
            {
                image[j][i].rgbtBlue = 255;
            }
            else
            {
                image[j][i].rgbtBlue = round(sepiaBlue);
            }

            if (round(sepiaGreen) > 255)
            {
                image[j][i].rgbtGreen = 255;
            }
            else
            {
                image[j][i].rgbtGreen = round(sepiaGreen);
            }

            if (round(sepiaRed) > 255)
            {
                image[j][i].rgbtRed = 255;
            }
            else
            {
                image[j][i].rgbtRed = round(sepiaRed);
            }
        }
    }
}