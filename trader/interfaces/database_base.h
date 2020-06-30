#ifndef DATABASE_BASE_H
#define DATABASE_BASE_H

#include <string>

class DatabaseBase {
public:
  DatabaseBase(void);
  ~DatabaseBase(void);

  virtual bool connect(void) = 0;
  virtual void disconnect(void) = 0;

  virtual int getNetworkCount(void) = 0;
  virtual std::string getNetwork(size_t id) = 0;
  virtual int getLayerCount(std::string ticker) = 0;
  
  virtual int getInputs(std::string ticker, int layerNum) = 0;
  virtual int getNodes(std::string ticker, int layerNum) = 0;
  virtual int getIndex(std::string ticker, int layerNum) = 0;

  int toInt(std::string in);
  float toFloat(std::string in);
};

#endif /* DATABASE_BASE_H */