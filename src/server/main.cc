#include <iostream>

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#include "utils/logger.hh"
#include "utils/error.hh"

int main(int /*argc*/, char ** /*argv*/) {
  logger::Init();

  log4cplus::Logger logger = log4cplus::Logger::getInstance("main");
  LOG4CPLUS_WARN(logger, "Hello, World!");

  auto std_error = std::make_error_code(error::ErrorCode::kError);
  auto boost_error = boost::system::make_error_code(error::ErrorCode::kError);

  std::cout << "Hello World!\n";
  return 0;
}
