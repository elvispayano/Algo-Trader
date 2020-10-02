#include "comms/msg_base.h"

MsgBase::MsgBase( void ) {
  memset( buffer, '\0', MAX_MSG_SIZE );
  msgSize = 0;
}
