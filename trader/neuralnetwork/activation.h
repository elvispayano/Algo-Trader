#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "activation_types.h"

class Activation {
public:
  Activation(void);
  Activation(ActivationTypes select);

private:
  ActivationTypes TF;
};

#endif /*ACTIVATION_H*/