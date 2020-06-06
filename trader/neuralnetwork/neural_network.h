#include <vector>
#include "network_types.h"
#include "matrix.h"

class LayerBase;

class NeuralNetwork {
public:
  NeuralNetwork(void);
  ~NeuralNetwork(void);

  void addLayer(LayerConfiguration configuration);

  size_t getLayerCount(void) { return layers.size(); }

private:
  std::vector<LayerBase*> layers;
};