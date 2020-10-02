#include "msg_base.h"

enum class LayerID { UNKNOWN, FULLYCONNECTED };

class LayerMsg : public MsgBase {
public:
  LayerMsg( void );
  ~LayerMsg( void );

  virtual bool encode( LayerMsg& msg ) { return false; }
  virtual bool decode( LayerMsg& msg ) { return false; }

  LayerID getID( void ) { return id; }

protected:
  LayerID id;

};
