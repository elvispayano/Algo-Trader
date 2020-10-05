/// FIFO Unidirectional
///
/// A unidirectional FIFO base class to allow one way communication between two
/// systems
///
/// \author   Elvis Payano
/// \date     04/10/2020
/// \version  0.0.1

#ifndef FIFO_UNIDIRECTIONAL_H
#define FIFO_UNIDIRECTIONAL_H

// Standard Includes
#include <queue>

template<typename T> class FIFOUnidirectional {
public:
  FIFOUnidirectional( void ) { counter = 0; }
  ~FIFOUnidirectional( void ) {
    while ( !fifoBuffer.empty() )
      fifoBuffer.pop();
  }

  bool putMessage( T* msg ) {
    if ( counter >= MAX_BUFFER_SIZE )
      return false;

    ++counter;
    fifoBuffer.push( msg );
    return true;
  }

  bool getMessage( T* msg ) {
    if ( fifoBuffer.empty() )
      return false;

    --counter;
    msg = fifoBuffer.front();
    fifoBuffer.pop();
  }

private:
  std::queue<T*> fifoBuffer;

  unsigned int       counter;
  const unsigned int MAX_BUFFER_SIZE = 50;
};

#endif /* FIFO_UNIDIRECTIONAL_H */
