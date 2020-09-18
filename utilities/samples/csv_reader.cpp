#include "utilities/csv_reader.h"

int main( void ) {
  CSVReader file( "./iris.csv" , ",");
  file.parseData( 5 );
  return 0;
}
