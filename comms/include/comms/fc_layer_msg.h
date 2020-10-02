/// Fully Connected Layer Message
///
/// Message architecture for transfer packetized fully connected layer
/// configuration
///
/// \author   Elvis Payano
/// \date     02/10/2020
/// \version  0.0.1

#ifndef FC_LAYER_MSG_H
#define FC_LAYER_MSG_H

#include "layer_msg.h"
#include "utilities/network_types.h"

class FCLayer : public LayerMsg {
public:
  FCLayer( void );
  ~FCLayer( void );

  bool encode( LayerMsg& msg ) override;
  bool decode( LayerMsg& msg ) override;

  struct {
    ActivationTypes activation;
    sint            row;
    sint            rowMax;
    sint            col;
    sint            colMax;
    float           weight0;
    float           weight1;
    float           weight2;
    float           weight3;
    float           weight4;
    float           bias0;
    float           bias1;
    float           bias2;
    float           bias3;
    float           bias4;
  };

private:
  struct MsgMap {
    Map<ActivationTypes, 0, 0, 0> activation;
    Map<sint, 1, 0, 0>            row;
    Map<sint, 3, 0, 0>            rowMax;
    Map<sint, 5, 0, 0>            col;
    Map<sint, 7, 0, 0>            colMax;
    Map<float, 9, 0, 1>           weight0;
    Map<float, 13, 0, 1>          weight1;
    Map<float, 17, 0, 1>          weight2;
    Map<float, 21, 0, 1>          weight3;
    Map<float, 25, 0, 1>          weight4;
    Map<float, 29, 0, 1>          bias0;
    Map<float, 33, 0, 1>          bias1;
    Map<float, 37, 0, 1>          bias2;
    Map<float, 41, 0, 1>          bias3;
    Map<float, 45, 0, 1>          bias4;
  } x;

  void write( LayerMsg& msg );
  void read( LayerMsg& msg );
};

#endif /* FC_LAYER_MSG_H */
