/// FIFO Bidirectional
///
/// A bidirectional FIFO base class to allow asynchronous communication between
/// two systems
///
/// \author   Elvis Payano
/// \date     04/10/2020
/// \version  0.0.1

#ifndef FIFO_BIDIRECTIONAL_H
#define FIFO_BIDIRECTIONAL_H

// Utility Includes
#include "fifo_unidirectional.h"

template<typename T, typename U> class FIFOBidirectional {
public:
  FIFOBidirectional( void ) {}
  ~FIFOBidirectional( void ) {}

  /// @fn     bool getInput( T* message )
  /// @param  message  Message from external system
  /// @brief  Read incoming message from buffer
  bool getInput( T& message ) { return input.getMessage( message ); }

  /// @fn     bool putInput( T* message )
  /// @param  message  Message from external system
  /// @brief  Write incoming message from buffer
  bool putInput( T& message ) { return input.putMessage( message ); }

  /// @fn     bool getOutput( T* message )
  /// @param  message  Message from internal system
  /// @brief  Read outgoing message from buffer
  bool getOutput( U& message ) { return output.getMessage( message ); }

  /// @fn     bool putOutput( T* message )
  /// @param  message  Message from internal system
  /// @brief  Write outgoing message to buffer
  bool putOutput( U& message ) { return output.putMessage( message ); }

private:
  FIFOUnidirectional<T> input;
  FIFOUnidirectional<U> output;
};

#endif /* FIFO_BIDIRECTIONAL_H */
