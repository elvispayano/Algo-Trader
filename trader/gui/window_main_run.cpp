/*
  Title:
    Main Window

  Description:
    The main window functionality and configuration specifications for
    the trader user interface

  Author:
    Elvis Payano
*/

// Test Includes
#include "test_main.h"

// UI Includes
#include "window_main.h"
#include "ui_window_main.h"

void WindowMain::onUnitTestsActionTiggered(void) {
  char* args = "--gtest_output=xml";
  test_main(1, &args);
}
