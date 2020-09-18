// Utility Includes
#include "utilities/csv_reader.h"

// Standard Includes
#include <iostream>

/// @fn     CSVReader( string filename )
/// @param  filename  File to be parsed
/// @param  delimiter Expected file delimeter
/// @brief  Construct the object that will read in and parse the data file
CSVReader::CSVReader( std::string filename, std::string delimiter )
    : delimeter( delimeter ) {
  csv.open( filename.c_str(), std::ios::in );
}

/// @fn     ~CSVReader( void )
/// @brief  Clear memory and close files
CSVReader::~CSVReader( void ) {
  csv.close();
}

/// @fn     parseData( unsigned int elements )
/// @param  elements  Number of elements expected in the dataset
/// @brief  Read in and parse the dataset
DataIn CSVReader::parseData( unsigned int elements ) {
  // Initialize
  DataIn data;

  std::string::size_type pos  = 0;
  std::string::size_type prev = 0;
  std::string            element;

  // Process Headers
  std::string line;
  std::getline( csv, line );
  for ( unsigned int iter = 0; iter < elements; ++iter ) {
    pos     = line.find( ',', pos );
    pos     = ( pos < line.length() ) ? pos : line.length();
    element = line.substr( prev, pos - prev );
    data[element].clear();
    prev = ++pos;
  }

  // Process Data
  while ( std::getline( csv, line ) ) {
    pos = prev = 0;
    for ( auto& field : data ) {
      pos     = line.find( ',', pos );
      pos     = ( pos < line.length() ) ? pos : line.length();
      element = line.substr( prev, pos - prev );
      field.second.push_back( element );
      prev = ++pos;
    }
  }

  return data;
}
