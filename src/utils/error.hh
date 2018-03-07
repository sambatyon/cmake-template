#pragma once

#include <system_error>

#include <boost/system/error_code.hpp>

// TODO: Add conversion from and to boost and std error_code.
// Use this as reference:
//
// inline std::error_code convert(const boost::system::error_code& error) {
//   if (error.category() == boost::system::generic_category()) {
//     return std::error_code(error.value(), bridge::generic_category());
//   }
//   assert(false);
//   return {}; // We could define a bridge conversion error instead
// }

namespace error {
enum ErrorCode {
  kError
};

template <typename Base>
const Base& template_category();

namespace detail {
template <typename Base>
class tempalte_category : public Base
{
 public:
  const char *name() const noexcept override {
    return "template category";
  }

  std::string message(int value) const override {
    switch (ErrorCode(value)) {
      case kError:
        return "error";
    }
    return "unknown template category";
  }
};
} // namespace detail

template <typename Base>
const Base& template_category() {
  static detail::tempalte_category<Base> category;
  return category;
}

} // namespace error

namespace std {
template<>
struct is_error_code_enum<error::ErrorCode> : public std::true_type {};

inline std::error_code make_error_code(error::ErrorCode e)
{
  return std::error_code(static_cast<int>(e),
                         error::template_category<std::error_category>());
}
} // namespace std


namespace boost {
namespace system {
template<>
struct is_error_code_enum<error::ErrorCode> : public std::true_type {};

inline std::error_code make_error_code(error::ErrorCode e)
{
  return std::error_code(
      static_cast<int>(e),
      error::template_category<boost::system::error_category>());
}
} // namespace system
} // namespace boost
