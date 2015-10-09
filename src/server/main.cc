#include <iostream>

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#include "utils/logger.hh"

int main(int /*argc*/, char ** /*argv*/) {
  logger::Init();

  log4cplus::Logger logger = log4cplus::Logger::getInstance("main");
  LOG4CPLUS_WARN(logger, "Hello, World!");

  std::cout << "Hello World!\n";
  return 0;
}
