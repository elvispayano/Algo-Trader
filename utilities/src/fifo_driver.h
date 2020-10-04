/// FIFO Driver
///
/// A FIFO Driver base class that allows for transferring messages
///
/// \author   Elvis Payano
/// \date     04/10/2020
/// \version  0.0.1

#ifndef FIFO_DRIVER_H
#define FIFO_DRIVER_H

// Standard Includes
#include <queue>

template<typename T> class FIFODriver {
public:
  FIFODriver( void ) { counter = 0; }
  ~FIFODriver( void ) {
    while ( !fifoBuffer.empty() )
      fifoBuffer.pop();
  }

  bool put( T msg ) {
    if ( counter >= MAX_BUFFER_SIZE )
      return false;

    ++counter;
    fifoBuffer.push( msg );
    return true;
  }

  bool get( T& msg ) {
    if ( fifoBuffer.empty() )
      return false;

    --counter;
    msg = fifoBuffer.front();
    fifoBuffer.pop();
  }

private:
  std::queue<T> fifoBuffer;

  unsigned int       counter;
  const unsigned int MAX_BUFFER_SIZE = 50;
};

#endif /* FIFO_DRIVER_H */
