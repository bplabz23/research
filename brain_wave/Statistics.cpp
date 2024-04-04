
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









float Statistics::standardDeviation(float* data_list, const int data_size)
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
    

    // 4. Take the sum of our squared differences (step 3 and 4 may be combined for optimization)
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