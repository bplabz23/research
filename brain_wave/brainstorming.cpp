/*
General Plan

Phase 1: Data Collection
Phase 2: Data Analysis
Phase 3: Prediction of good/bad days (via clustering)


*/











// Questions:
// 1) Sending Data from Arduino to a .csv file or something like that? (Use this to determine overall architecture of project)
//      Alternate method to webserver: PuTTY
// 2) Storage capacity and data management
// 3) Object-oriented Programming?
// 4) Utilizing program space (static/flash), Dynamic Memory, and other unconventional buffers/registers



// Reads the data, performs calculations, returns regression line info 
//  i.e.   Regression line equation is of form y = mx + b 
//  Given  a set of x-values and a set of y-values, returns m and b
//  UPDATE: This function needs a better method of handling data points with the same x-values
//  WARNING: This function has side-effects on certain parameters
void calculateRegressionLine(float *x_list, float *y_list, int list_size, float &m, float &b)
{
    // 1. Calculate the average slope between points

    // For every data point
    for(int i = 0; i < list_size; i++)
    {

        // Compare it to every other data point
        for(int j = 0; j < list_size; j++) 
        {


        }


    }

}



















// It may be in our interest to create ordered-pair objects so that y values don't get separated from their x values.





