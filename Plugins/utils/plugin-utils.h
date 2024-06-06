#pragma once

#include <format>
#include <optional>
#include <string_view>
#include "loader.h"
#include "scanmem.h"

struct Signature {
  std::string_view name;
  std::string_view binary;
  int offset = 0;
};

namespace plugin {
extern std::string_view module_name;

template <typename... Args>
void log(loader::LogLevel level, std::format_string<Args...>&& fmt, Args... args) {
  if (level >= loader::MinLogLevel) {
    loader::LOG(level) << std::format("[{}]{}", module_name, std::vformat(fmt.get(), std::make_format_args(args...)));
  }
}

inline std::optional<unsigned char*> find_func(Signature sig) {
  using namespace loader;
  auto [bytes, mask] = parseBinary(sig.binary);
  auto found = scanmem(bytes, mask);
  if (found.size() != 1) {
    log(ERR, "failed to find unique function {} found {}", sig.name, found.size());
    return {};
  }
  auto final_addr = found[0] + sig.offset;
  log(INFO, "found function {} at address {:p}", sig.name, (void*)final_addr);
  return final_addr;
}
}  // namespace plugin
