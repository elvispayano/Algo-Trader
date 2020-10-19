/// Mesage Base
///
/// Base architecture to transfer packetized serialized data between multiple
/// systems
///
/// \author   Elvis Payano
/// \date     02/10/2020
/// \version  0.0.1

#ifndef MSG_BASE_H
#define MSG_BASE_H

// Standard Includes
#include <string>

static const unsigned int MAX_MSG_SIZE = 50;

template<typename T, unsigned int BYTE, unsigned int BIT, unsigned int SCALE>
class Map {
public:
  Map( void ) {}
  ~Map( void ) {}
};

class MsgBase {
public:
  /// @fn     MsgBase( void )
  /// @brief  Initialize an empty message packet
  MsgBase( void ) {
    memset( buffer, '\0', MAX_MSG_SIZE );
    msgSize = 0;
  }

  /// @fn     ~MsgBase( void )
  /// @brief  Clear and reset packet memory
  ~MsgBase( void ) {}

  typedef unsigned char uchar;
  typedef unsigned int  uint;

  template<uint BYTE, uint BIT>
  void read( Map<bool, BYTE, BIT, 0U> map, bool& out, MsgBase* msg ) {
    uchar outBuffer = '\0';
    memcpy( &outBuffer, &msg->buffer[BYTE], 1 );
    out = static_cast<bool>( ( outBuffer >> BIT ) & 0x01 );
  }

  template<uint BYTE, uint BIT>
  void write( Map<bool, BYTE, BIT, 0U> map, bool& in, MsgBase* msg ) {
    uchar inBuffer = ( static_cast<uchar>( in ) << BIT ) | msg->buffer[BYTE];
    memcpy( &msg->buffer[BYTE], &inBuffer, 1 );
  }

  // Short Unsigned Integer Access
  typedef short unsigned int suint;
  template<uint BYTE, uint BIT>
  void read( Map<suint, BYTE, BIT, 0U> map, suint& out, MsgBase* msg ) {
    uchar outBuffer = '\0';
    memcpy( &outBuffer, &msg->buffer[BYTE], 1 );
    out = static_cast<suint>( outBuffer );
  }

  template<uint BYTE, uint BIT>
  void write( Map<suint, BYTE, BIT, 0U> map, suint& in, MsgBase* msg ) {
    uchar inBuffer = static_cast<uchar>( in );
    memcpy( &msg->buffer[BYTE], &inBuffer, 1 );
  }

  // Unsigned Integer Access
  template<uint BYTE, uint BIT>
  void read( Map<uint, BYTE, BIT, 0U> map, uint& out, MsgBase* msg ) {
    uchar outBuffer = '\0';
    for ( uint ind = 0; ind < 2; ++ind ) {
      memcpy( &outBuffer, &msg->buffer[BYTE + ind], 1 );
      out |= static_cast<uint>( outBuffer << ( 8 * ind ) );
    }
  }

  template<uint BYTE, uint BIT>
  void write( Map<uint, BYTE, BIT, 0U> map, uint& in, MsgBase* msg ) {
    uchar inBuffer = '\0';
    for ( uint ind = 0; ind < 2; ++ind ) {
      inBuffer = static_cast<uchar>( in >> ( 8 * ind ) );
      memcpy( &msg->buffer[BYTE + ind], &inBuffer, 1 );
    }
  }

  // Short Integer Access
  typedef short int sint;
  template<uint BYTE, uint BIT>
  void read( Map<sint, BYTE, BIT, 0U> map, sint& out, MsgBase* msg ) {
    uchar outBuffer = '\0';
    for ( uint ind = 0; ind < 2; ++ind ) {
      memcpy( &outBuffer, &msg->buffer[BYTE + ind], 1 );
      out |= static_cast<sint>( outBuffer << ( 8 * ind ) );
    }
  }

  template<uint BYTE, uint BIT>
  void write( Map<sint, BYTE, BIT, 0U> map, sint& in, MsgBase* msg ) {
    uchar inBuffer = '\0';
    for ( uint ind = 0; ind < 2; ++ind ) {
      inBuffer = static_cast<uchar>( in >> ( 8 * ind ) );
      memcpy( &msg->buffer[BYTE + ind], &inBuffer, 1 );
    }
  }

  // Float
  template<uint BYTE, uint BIT, uint SCALE>
  void read( Map<float, BYTE, BIT, SCALE> map, float& out, MsgBase* msg ) {
    uchar outBuffer[4];
    memset( outBuffer, '\0', 4 );
    for ( uint iter = 0; iter < 4; ++iter ) {
      memcpy( &outBuffer[iter], &msg->buffer[BYTE + iter], 1 );
    }
    out = *reinterpret_cast<float*>( outBuffer );
  }

  template<uint BYTE, uint BIT, uint SCALE>
  void write( Map<float, BYTE, BIT, SCALE> map, float& in, MsgBase* msg ) {
    uchar* inBuffer = reinterpret_cast<uchar*>( &in );
    for ( uint iter = 0; iter < 4; ++iter ) {
      memcpy( &msg->buffer[BYTE + iter], &inBuffer[iter], 1 );
    }
  }

  // String
  typedef std::string String;
  template<uint BYTE, uint SCALE>
  void read( Map<String, BYTE, 0, SCALE> map, String& out, MsgBase* msg ) {
    out.clear();
    for ( uint iter = 0; iter < SCALE; ++iter ) {
      uchar character = '\0';
      memcpy( &character, &msg->buffer[BYTE + iter], 1 );
      if ( character != '\0' ) {
        out.push_back( character );
      }
    }
  }

  template<uint BYTE, uint SCALE>
  void write( Map<String, BYTE, 0, SCALE> map, String& in, MsgBase* msg ) {
    for ( uint iter = 0; iter < SCALE; ++iter ) {
      if (iter > in.size()) {
        msg->buffer[BYTE + iter] = '\0';
      } else {
        memcpy( &msg->buffer[BYTE + iter], &in[iter], 1 );
      }
    }
  }

  /// @fn     void read( Map map, T& out, MsgBase& msg)
  /// @brief  Deserialize the data from the message buffer
  template<typename T, uint BYTE, uint BIT>
  void read( Map<T, BYTE, BIT, 0> map, T& out, MsgBase* msg ) {
    uchar outBuffer = '\0';
    memcpy( &outBuffer, &msg->buffer[BYTE], 1 );
    out = static_cast<T>( outBuffer );
  }

  /// @fn     void write( Map map, T& in, MsgBase& msg)
  /// @brief  Serialize the current message and populate the message buffer
  template<typename T, uint BYTE, uint BIT>
  void write( Map<T, BYTE, BIT, 0> map, T& in, MsgBase* msg ) {
    uchar inBuffer = static_cast<uchar>( in );
    memcpy( &msg->buffer[BYTE], &inBuffer, 1 );
  }

  uchar buffer[MAX_MSG_SIZE];
  uint  msgSize;
};

#endif /* MSG_BASE_H */
