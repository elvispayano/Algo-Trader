#include "database_base.h"

DatabaseBase::DatabaseBase(void) {

}

DatabaseBase::~DatabaseBase(void) {

}

int DatabaseBase::toInt(std::string in) {
  if (in.empty())
    return 0;

  return atoi(in.c_str());
}

float DatabaseBase::toFloat(std::string in) {
  if (in.empty())
    return 0.0f;

  return atof(in.c_str());
}
