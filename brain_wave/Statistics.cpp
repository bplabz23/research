
/*
*           Name:       Statistics.cpp
*           Author:     Basil Moledina
*           Date:       4/02/2024
*
*           Description: Function implementations for the Statistics library
*
*/





#include "Statistics.h"
#include <math.h>



float Statistics::average(float* data_list, int data_size)
{
    // 1. Setup
    float sum = 0;

    // 2. Get the sum of data
    for (int i = 0; i < data_size; i++)
    {
        // For every piece of data i, add it to the sum
        sum += data_list[i];
    }

    // 3. Divide the sum of all data by the sample size to get the average 
    float mean = sum / (float)data_size;

    return mean;
}









float Statistics::stdDeviation(float* data_list, const int data_size)
{
    // 1. Compute the mean of the data set
    float mean = average(data_list, data_size);


    // 2. Make a new list. We're gonna keep a list of each data point subtracted by the mean
    //      (Basically, we are finding how far each piece of data is from the mean)
    float differences[data_size];       // WARNING: This will give you errors in C++, but should be fine for Arduino's compiler (if not use macro)

    for (int i = 0; i < data_size; i++)
    {
        differences[i] = data_list[i] - mean;
    }
    

    // 3. Take the square of each of those values
    for (int i = 0; i < data_size; i++)
    {
        differences[i] = differences[i] * differences[i];
    }
    

    // 4. Take the sum of our squared differences (I think we are just taking an average so some stuff can be optimized here)
    float sum = 0;
    
    for (int i = 0; i < data_size; i++)
    {
        sum += differences[i];
    }


    // 5. Divide by (sample size - 1)
    float variance = sum / ( (float)data_size - 1.0);

    // 6. Take the square root of the variance.
    float std_deviation = sqrt(variance);

    // Return standard deviation
    return std_deviation;
}







// Returns the z-score of the data provided 

float Statistics::zScore(float data, float mean, float std_dev)
{
    // Z-score is just a way of telling how many standard deviations our data is from the mean


    // 1. Get distance of data from the mean
    float z = data - mean;

    // 2. Divide by standard deviation
    z = z / std_dev;

    return z;
}







float Statistics::getLinearCorrelation(float *var_x, float *var_y, const int data_size)
{
    // What we do for a datapoint is 
    //      1. Get its z-score in the x dimension (how much the data deviates from the average x value)
    //      2. Get its z-score in the y dimension (how much the data deviates from the average y value)
    //      3. Take the product of those z-scores
    
    //  Then for all data points, we take the average product


    // 1. Get data we need for x and y variables
    float x_mean = average(var_x, data_size);
    float x_deviation = stdDeviation(var_x, data_size);

    float y_mean = average(var_y, data_size);
    float y_deviation = stdDeviation(var_y, data_size);


    // 2. We're going to get z-scores for each piece of data, take the product, and then keep a list of products
    float x_score;
    float y_score;

    float products[data_size];

    // For data-point i
    for (int i = 0; i < data_size; i++)
    {

        x_score = zScore( var_x[i], x_mean, x_deviation );      // Get its z-score for its x-value
        y_score = zScore( var_y[i], y_mean, y_deviation );      // Get its z-score for its y-value

        products[i] = x_score * y_score;                        // Get the product of its scores
    }


    // 3. Take the average of the products (or find the average area produced by the z-scores)

    //  WARNING: In calculating r, we have to consider the degrees of freedom, MEANING this is a strange case of the mean 
    //            where we have to use (n-1) instead of n. And on top of that, we can't just pass n-1 to average()
    //            because otherwise, the function will not read the full array due to the way it's written.

    //  OPTIMIZE:    This program can definitely be optimized by creating a sum() function

    float sum = 0;
    for (int i = 0; i < data_size; i++)
    {
        sum += products[i];
    }

    float r = sum / (data_size - 1);       // correlation co-efficient = sum / (n-1)

    return r;
}








float Statistics::getLinearSlope(float *var_x, float *var_y, const int data_size)
{
    // m  = r * (y_deviation / x_deviation)
    // We still sort of have that idea of rise over run, how much the standard deviation in y changes per standard deviation of x

    float r = getLinearCorrelation(var_x, var_y, data_size);
    float x_stdDeviation = stdDeviation(var_x, data_size);
    float y_stdDeviation = stdDeviation(var_y, data_size);

    float m = r * ( y_stdDeviation / x_stdDeviation );
    return m;
}







float Statistics::getLinearIntercept(float *var_x, float *var_y, const int data_size)
{
    // We know that one our points our line goes through is (x_avg, y_avg)
    // All we have to do is plug this and our slope into the line equation and solve for b
    // b = y - mx

    float m = getLinearSlope(var_x, var_y, data_size);
    float x_mean = average(var_x, data_size);
    float y_mean = average(var_y, data_size);

    float b = y_mean - (m * x_mean);

    return b;
}
