#include "neuralnetwork/neural_network.h"

int main( void ) {
  LayerConfiguration config;
  config.activation = ActivationTypes::LINEAR;
  config.layer      = LayerTypes::FULLYCONNECTED;

  NeuralNetwork network;

  config.hyperparams.resize( 4, 4, 0.0 );
  config.hyperparams.randomize();
  network.addInputLayer( 4, config );

  config.nodes = 10;
  config.hyperparams.resize( config.nodes, 4, 0.0 );
  config.hyperparams.randomize();
  network.addLayer( config );

  config.hyperparams.resize( config.nodes, config.nodes, 0.0 );
  config.hyperparams.randomize();
  network.addLayer( config );

  config.hyperparams.randomize();
  network.addLayer( config );

  config.hyperparams.resize( 3, config.nodes, 0.0 );
  config.hyperparams.randomize();
  network.addOutputLayer( 3, config );

  dMatrix input( 4, 1, 0.0 );
  input.randomize();
  dMatrix output = network.process( input );
  return 0;
}
