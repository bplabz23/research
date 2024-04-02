/*
*          Name:        main.ino
*          Author:      Basil Moledina
*          Date:        04/02/2024 
*
*          Description: This is the driver program that runs on the Arduino. Its job is to:
*                           1) Receive data from a brain-wave sensor
*                           2) Temporarily store and organize this data
*                           3) package this data as a .csv file and send it off to a computer for data analysis (via PuTTY or etc.)
*                           
*/



// Adjust this value to equal the amount of statistical variables we are observing/collecting data for.
const int VARIABLE_COUNT = 3;


// Adjust this value to match how much data we want to collect for each variable.
const int DATA_COUNT = 50;


// A list of all the statistical variables we are observing. This list holds variables, and each variable holds 50 pieces of data measuring it.
float variable_list[VARIABLE_COUNT][DATA_COUNT];



// Define some enumerators so that we can pull variables out of the table using a name that makes sense, not an index
//    We might move this into a function so that we are using program memory instead of dynamic memory
const int INTENSITY = 0;
const int EMOTIONAL_SPECTRUM = 1;
const int FOCUS = 2;



// For our convenience, let's hold string representations of variables later on for print-out
const String variable_names[] = {"Intensity", "Emotional Spectrum", "Focus"};




void setup() 
{
  Serial.begin(9600);  
  initializeVarList();
  printCSV();



}





void loop() {


}





void printCSV()
{
  // 1. For every variable
  for (int i = 0; i < VARIABLE_COUNT; i++)
  {
    // 2. Dedicate this row to variable i. Create a cell with the variable's name, then separate with comma
    Serial.print( variable_names[i] );
    Serial.print(",");

    // 3. Print that variable's data on this row
    // For every measurement of the variable
    for (int j = 0; j < DATA_COUNT; j++)
    {
      // Print measurement j
      Serial.print( variable_list[i][j] );

      // If we are not at the end of our data (there is more to come)
      if (j != DATA_COUNT - 1)
      {
        // Add a comma (delimiter)
        Serial.print(",");
      }

    }

    // 4. When we are finished printing a variable's data, move to the next row
    Serial.print("\n");
  }

}




// This is a function used primarily in testing some features
void initializeVarList()
{
  for (int i = 0; i < VARIABLE_COUNT; i++)
    {
      for (int j = 0; j < DATA_COUNT; j++)
      {
        variable_list[i][j] = 1;
      }

    }

}
