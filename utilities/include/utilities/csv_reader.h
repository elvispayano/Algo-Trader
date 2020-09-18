/// CSV Reader
///
/// A class that will load, read, and parse a CSV data.
///
/// \author   Elvis Payano
/// \date     17/09/2020
/// \version  0.0.1

#ifndef CSV_READER_H
#define CSV_READER_H

// Standard Includes
#include <fstream>
#include <string>
#include <map>
#include <vector>

typedef std::map<std::string, std::vector<std::string>> DataIn;

class CSVReader {
public:
  /// @fn     CSVReader( string filename )
  /// @param  filename  File to be parsed
  /// @param  delimiter Expected file delimeter
  /// @brief  Construct the object that will read in and parse the data file
  CSVReader( std::string filename, std::string delimiter );

  /// @fn     ~CSVReader( void )
  /// @brief  Clear memory and close files
  ~CSVReader( void );

  /// @fn     parseData( unsigned int elements )
  /// @param  elements  Number of elements expected in the dataset
  /// @brief  Read in and parse the dataset
  DataIn parseData( unsigned int elements );

private:
  std::fstream csv;
  std::string  delimeter;
};

#endif /* CSV_READER_H */
