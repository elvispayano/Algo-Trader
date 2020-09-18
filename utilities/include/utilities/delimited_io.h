/// Delimited IO
///
/// A class that allows for reading, writing, and parsing delimited data files
///
/// \author   Elvis Payano
/// \date     18/09/2020
/// \version  0.0.1

// Standard Includes
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

typedef std::map<std::string, std::vector<std::string>> DataIn;

class DelimitedIO {
public:
  /// @fn     DelimitedIO( string delimiter )
  /// @param  delimiter Expected file delimeter
  /// @brief  Construct the object that will read in and parse the data file
  DelimitedIO( std::string delimiter );

  /// @fn     ~DelimitedIO( void )
  /// @brief  Clear memory and close files
  ~DelimitedIO( void );

  /// @fn     openFile ( string filename, string mode )
  /// @param  filename  File to be opened
  /// @param  mode      Mode in which to open the file
  /// @brief  Open a file that can be read or written to
  void openFile( std::string filename, std::ios::_Openmode mode );

  /// @fn     parseData( unsigned int elements )
  /// @param  elements  Number of elements expected in the dataset
  /// @brief  Read in and parse the dataset
  virtual DataIn parseData( unsigned int elements );

private:
  std::string  delimiter;
  std::fstream datafile;
};

class CSVIO : public DelimitedIO {
public:
  CSVIO( void )
      : DelimitedIO( "," ) {}

  ~CSVIO( void ) {}
};
