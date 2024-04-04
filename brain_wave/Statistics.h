




class Statistics
{
    public:
        
        // Constructor
        Statistics() {}

        // Methods - basic statistics
        float average(float* data_list, int data_size);
        float stdDeviation(float* data_list, const int data_size);
        float zScore(float data, float mean, float std_dev);

        // Linear Regression - stuff for building an equation of the form y = mx + b
        float getLinearCorrelation(float* var_x, float* var_y, const int data_size);
        float getLinearSlope(float* var_x, float* var_y, const int data_size);
        float getLinearIntercept(float* var_x, float* var_y, const int data_size);

};