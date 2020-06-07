// trader.cpp : Defines the entry point for the application.
//
#include <iostream>
#ifdef DEBUG
#include "test_main.h"
#endif

int main(int argc, char **argv) {
#ifdef DEBUG
  test_main();
#endif
  std::cin.get();
}
