#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "activation_types.h"
#include "matrix.h"

class Activation {
public:
  Activation(void);
  Activation(ActivationTypes select);

  void setTF(ActivationTypes select) { TF = select; };

protected:
  dMatrix perform(dMatrix);

private:
  ActivationTypes TF;

  dMatrix tanh(dMatrix);
  dMatrix sig (dMatrix);
  dMatrix relu(dMatrix);
  dMatrix bin (dMatrix);
  dMatrix none(dMatrix);
};

#endif /*ACTIVATION_H*/