#include "utils/logger.hh"

#include <boost/filesystem/operations.hpp>

#include <log4cplus/configurator.h>
#include <log4cplus/consoleappender.h>

#if defined(_WIN32)
# include <winbase.h>
#elif defined(__APPLE__)
# include <mach-o/dyld.h>
# include <sys/syslimits.h>
#else // asuming linux
# if !defined(NDEBUG)
#   include <unistd.h>
# endif // !defined(NDEBUG)
#endif // defined(_WIN32) defined(__APPLE__)

#if defined(PACKAGE_NAME)
# define DEFAULT_LOG_FILE "/var/log/" #PACKAGE_NAME "/logging.conf"
#else // defined(PACKAGE_NAME)
# define DEFAULT_LOG_FILE "/var/log/logging.conf"
#endif // defined(PACKAGE_NAME)

namespace logger {
void Init() {
#if defined(_WIN32)

  TCHAR path_buffer[MAX_PATH];
  DWORD buffer_size = GetModuleFileName(NULL, path_buffer, MAX_PATH);
  // if buffer_size == MAX_PATH the buffer was truncated and
  // GetLastError() returns ERROR_INSUFFICIENT_BUFFER

  // TODO: if buffer_size == 0 check GetLastError()
  boost::filesystem::path log_config(path_buffer);

#elif defined(__APPLE__)

  char path_buffer[PATH_MAX];
  std::uint32_t buffer_size = sizeof(path_buffer);
  int got_path = _NSGetExecutablePath(path_buffer, &buffer_size);
  // TODO: check if got_path != 0, in which case the call failed.
  boost::filesystem::path log_config(path_buffer);

#else // Assuming linux
# if !defined(NDEBUG)

  // On debug the configuration file is in the same directory as the
  // executable
  char path_buffer[8192];
  std::uint32_t buffer_size = sizeof(path_buffer);
  ssize_t path_size = readlink("/proc/self/exe", path_buffer, buffer_size);
  // TODO: if path_size == -1 check errno
  path_buffer[path_size] = '\0';
  boost::filesystem::path log_config(path_buffer);

# else // !defined(NDEBUG)

  // On release mode, it should be in a common directory
  boost::filesystem::path log_config(DEFAULT_LOG_FILE);

# endif
#endif

  log_config.remove_filename();
  log_config /= "logging.conf";

  Init(log_config);
}

void Init(const boost::filesystem::path& log_config) {
  if (boost::filesystem::exists(log_config) &&
        boost::filesystem::is_regular_file(log_config)) {
    log4cplus::PropertyConfigurator configurator(log_config.string());
    configurator.configure();
  } else {
    //log4cplus::BasicConfigurator configurator;
    //configurator.configure();

    // TODO: make this code work
    log4cplus::SharedAppenderPtr appender(
      new log4cplus::ConsoleAppender(false, false));
    appender->setName("RootAppender");
    std::auto_ptr<log4cplus::Layout> layout(
      new log4cplus::PatternLayout("%D{%d.%m.%Y %H:%M:%S.%q} [%8t] %-5p - "
                                   "%c{2} - %m%n"));
    appender->setLayout(layout);
    auto logger = log4cplus::Logger::getRoot();
    logger.addAppender(appender);
    logger.setLogLevel(log4cplus::TRACE_LOG_LEVEL);
  }
}
} // namespace logger
