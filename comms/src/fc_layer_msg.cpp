
#include "comms/fc_layer_msg.h"

FCLayer::FCLayer( void ) {
  id         = LayerID::FULLYCONNECTED;
  msgSize    = 49;
  activation = ActivationTypes::UNKNOWN;

  row = 0;
  col = 0;

  rowMax = 0;
  colMax = 0;

  weight0 = 0.0f;
  weight1 = 0.0f;
  weight2 = 0.0f;
  weight3 = 0.0f;
  weight4 = 0.0f;

  bias0 = 0.0f;
  bias1 = 0.0f;
  bias2 = 0.0f;
  bias3 = 0.0f;
  bias4 = 0.0f;
}

FCLayer::~FCLayer( void ) {}

void FCLayer::write( LayerMsg& msg ) {
  MsgBase::write( x.activation, activation, msg );
  MsgBase::write( x.row, row, msg );
  MsgBase::write( x.rowMax, rowMax, msg );
  MsgBase::write( x.col, col, msg );
  MsgBase::write( x.colMax, colMax, msg );
  MsgBase::write( x.weight0, weight0, msg );
  MsgBase::write( x.weight1, weight1, msg );
  MsgBase::write( x.weight2, weight2, msg );
  MsgBase::write( x.weight3, weight3, msg );
  MsgBase::write( x.weight4, weight4, msg );
  MsgBase::write( x.bias0, bias0, msg );
  MsgBase::write( x.bias1, bias1, msg );
  MsgBase::write( x.bias2, bias2, msg );
  MsgBase::write( x.bias3, bias3, msg );
  MsgBase::write( x.bias4, bias4, msg );
}

void FCLayer::read( LayerMsg& msg ) {
  MsgBase::read( x.activation, activation, msg );
  MsgBase::read( x.row, row, msg );
  MsgBase::read( x.rowMax, rowMax, msg );
  MsgBase::read( x.col, col, msg );
  MsgBase::read( x.colMax, colMax, msg );
  MsgBase::read( x.weight0, weight0, msg );
  MsgBase::read( x.weight1, weight1, msg );
  MsgBase::read( x.weight2, weight2, msg );
  MsgBase::read( x.weight3, weight3, msg );
  MsgBase::read( x.weight4, weight4, msg );
  MsgBase::read( x.bias0, bias0, msg );
  MsgBase::read( x.bias1, bias1, msg );
  MsgBase::read( x.bias2, bias2, msg );
  MsgBase::read( x.bias3, bias3, msg );
  MsgBase::read( x.bias4, bias4, msg );
}

bool FCLayer::encode( LayerMsg& msg ) {
  if ( msg.msgSize > MAX_MSG_SIZE ) {
    return false;
  }
  write( msg );
  return true;
}

bool FCLayer::decode( LayerMsg& msg ) {
  if ( msg.msgSize > MAX_MSG_SIZE ) {
    return false;
  }

  read( msg );
  return true;
}
