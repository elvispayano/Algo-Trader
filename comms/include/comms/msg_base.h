#include <string>

static const unsigned int MAX_MSG_SIZE = 1;

template<typename T, unsigned int BYTE, unsigned int BIT> class Map {
public:
  Map( void ) {}
  ~Map( void ) {}
};

class MsgBase {
public:
  MsgBase( void ) { memset( buffer, '\0', MAX_MSG_SIZE ); }
  ~MsgBase( void ) {}

  typedef unsigned char uchar;
  typedef unsigned int  uint;

  // Boolean Access
  template<uint BYTE, uint BIT>
  void read( Map<bool, BYTE, BIT> map, bool& out, MsgBase& msg ) {
    uchar outBuffer = '\0';
    memcpy( &outBuffer, &msg.buffer[BYTE], 1 );
    out = static_cast<bool>( ( outBuffer >> BIT ) & 0x01 );
  }

  template<uint BYTE, uint BIT>
  void write( Map<bool, BYTE, BIT> map, bool& in, MsgBase& msg ) {
    uchar inBuffer = ( static_cast<uchar>( in ) << BIT ) | msg.buffer[BYTE];
    memcpy( &msg.buffer[BYTE], &inBuffer, 1 );
  }

  // Short Unsigned Integer
  typedef short unsigned int suint;
  template<uint BYTE, uint BIT>
  void read( Map<suint, BYTE, BIT> map, suint& out, MsgBase& msg ) {
    uchar outBuffer = '\0';
    memcpy( &outBuffer, &msg.buffer[BYTE], 1 );
    out = static_cast<suint>( outBuffer );
  }

  template<uint BYTE, uint BIT>
  void write( Map<suint, BYTE, BIT> map, suint& in, MsgBase& msg ) {
    uchar inBuffer = static_cast<uchar>( in );
    memcpy( &msg.buffer[BYTE], &inBuffer, 1 );
  }

  uchar buffer[MAX_MSG_SIZE];
};
