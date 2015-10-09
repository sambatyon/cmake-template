#pragma once

#include <boost/filesystem/path.hpp>

namespace logger {
void Init();

void Init(const boost::filesystem::path& log_config);
} // namespace logger
