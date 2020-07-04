#ifndef DATABASE_BASE_H
#define DATABASE_BASE_H

#include <string>
struct LayerConfiguration;

class DatabaseBase {
public:
  DatabaseBase(void);
  ~DatabaseBase(void);

  // Connection management
  virtual bool connect(void) = 0;
  virtual void disconnect(void) = 0;

  // Network configuration
  virtual int getNetworkCount(void) = 0;
  virtual std::string getNetwork(size_t id) = 0;
  virtual int getLayerCount(std::string ticker) = 0;

  // Layer configuration
  virtual LayerConfiguration* getLayer(std::string ticker, unsigned int layerNum) = 0;

  // Support functions
  int toInt(std::string in);
  float toFloat(std::string in);
};

#endif /* DATABASE_BASE_H */