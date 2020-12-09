///
#ifndef HAZEL_INTERNAL_HPP
#define HAZEL_INTERNAL_HPP
#include <hazel/elf.hpp>

namespace hazel::elf {
inline std::string_view cstring_view(const char *data, size_t len) {
  std::string_view sv{data, len};
  if (auto p = sv.find('\0'); p != std::string_view::npos) {
    return sv.substr(0, p);
  }
  return sv;
}

inline std::string_view cstring_view(const uint8_t *data, size_t len) {
  return cstring_view(reinterpret_cast<const char *>(data), len);
}

// getString extracts a string from symbol string table.
inline std::string getString(std::vector<char> &buffer, int start) {
  if (start < 0 || static_cast<size_t>(start) >= buffer.size()) {
    return "";
  }
  for (auto end = static_cast<size_t>(start); end < buffer.size(); end++) {
    if (buffer[end] == 0) {
      return std::string(buffer.data() + start, end - start);
    }
  }
  return "";
}

} // namespace hazel::elf

#endif