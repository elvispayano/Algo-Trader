/*
  Title:
    Database Base

  Description:
    This class is the template configuration for managing connections to external
    Databases. This base implementation will allow for the selected solution to be
    independent of how the project is designed.

  Test:
    test_database_base.cc

  Author:
    Elvis Payano
*/

// Interface Includes
#include "database_base.h"

/*
  Function:     toInt
  Inputs:       input (string)
  Outputs:      output (int)

  Description:
    Convert input string into an integer value
*/
int DatabaseBase::toInt(std::string in) {
  if (in.empty())
    return 0;

  return atoi(in.c_str());
}

/*
  Function:     toFloat
  Inputs:       input (string)
  Outputs:      output (float)

  Description:
    Convert input string into a float value
*/
float DatabaseBase::toFloat(std::string in) {
  if (in.empty())
    return 0.0f;

  return atof(in.c_str());
}
