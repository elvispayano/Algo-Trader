#include "msg_base.h"

class LayerMsg : public MsgBase {
public:
  LayerMsg( void ) {}
  ~LayerMsg( void ) {}

  virtual bool encode( LayerMsg& msg ) { return false; }
  virtual bool decode( LayerMsg& msg ) { return false; }
};

class FCLayer : public LayerMsg {
public:
  FCLayer( void ) {}
  ~FCLayer( void ) {}

  bool encode( LayerMsg& msg ) override {
    write( msg );
    return false;
  }

  bool decode( LayerMsg& msg ) override {
    read( msg );
    return false;
  }

  struct {
    suint temp1;
  };

private:
  struct MsgMap {
    Map<suint, 0, 0> temp1;
  } x;

  void write( LayerMsg& msg ) { MsgBase::write( x.temp1, temp1, msg ); }

  void read( LayerMsg& msg ) { MsgBase::read( x.temp1, temp1, msg ); }
};
