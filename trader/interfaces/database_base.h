#ifndef DATABASE_BASE_H
#define DATABASE_BASE_H

#include <string>
struct LayerConfiguration;

class DatabaseBase {
public:
  DatabaseBase(void);
  ~DatabaseBase(void);

  virtual bool connect(void) = 0;
  virtual void disconnect(void) = 0;

  virtual LayerConfiguration* getLayer(std::string ticker, unsigned int layerNum) = 0;

  int toInt(std::string in);
  float toFloat(std::string in);
};

#endif /* DATABASE_BASE_H */