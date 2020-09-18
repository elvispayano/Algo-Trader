/// Delimited IO
///
/// A class that allows for reading, writing, and parsing delimited data files
///
/// \author   Elvis Payano
/// \date     18/09/2020
/// \version  0.0.1

// Utility Includes
#include "utilities/delimited_io.h"

// Standard Includes
#include <iostream>

/// @fn     DelimitedIO( string delimiter )
/// @param  delimiter Expected file delimeter
/// @brief  Construct the object that will read in and parse the data file
DelimitedIO::DelimitedIO( std::string delimiter )
    : delimiter( delimiter ) {}

/// @fn     ~DelimitedIO( void )
/// @brief  Clear memory and close files
DelimitedIO::~DelimitedIO( void ) {
  if ( datafile.is_open() ) {
    datafile.close();
  }
}

/// @fn     openFile ( string filename, string mode )
/// @param  filename  File to be opened
/// @param  mode      Mode in which to open the file
/// @brief  Open a file that can be read or written to
void DelimitedIO::openFile( std::string filename, std::ios::_Openmode mode ) {
  if ( datafile.is_open() ) {
    return;
  }
  datafile.open( filename, mode );
}

/// @fn     parseData( unsigned int elements )
/// @param  elements  Number of elements expected in the dataset
/// @brief  Read in and parse the dataset
DataIn DelimitedIO::parseData( unsigned int elements ) {
  // Initialize
  DataIn data;

  std::string::size_type pos  = 0;
  std::string::size_type prev = 0;
  std::string            element;

  // Process Headers
  std::string line;
  std::getline( datafile, line );
  for ( unsigned int iter = 0; iter < elements; ++iter ) {
    pos     = line.find( ',', pos );
    pos     = ( pos < line.length() ) ? pos : line.length();
    element = line.substr( prev, pos - prev );
    data[element].clear();
    prev = ++pos;
  }

  // Process Data
  while ( std::getline( datafile, line ) ) {
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
