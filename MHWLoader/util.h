#pragma once

#include <functional>
#include <source_location>
#include "MinHook.h"

template <typename T>
inline T* offsetPtr(void* ptr, int offset) {
  return (T*)(((char*)ptr) + offset);
}

#define SHOW(VAR) "\"" #VAR "\"={" << VAR << "}"

consteval int line(std::source_location loc = std::source_location::current()) {
  return loc.line();
}

template <typename F, int Id = 0>
struct Hook {};
template <typename R, typename... A, int Id>
struct Hook<R(A...), Id> {
  using func = R(A...);
  using hook_function = std::function<R(R (*)(A...), A...)>;

  inline static hook_function static_hook = {};
  inline static func* orig = nullptr;
  inline static constexpr int id = Id;

  static R c_hook(A... args) { return static_hook(orig, args...); }

  static bool hook(void* addr, hook_function f) {
    static_hook = f;
    MH_CreateHook(addr, (void*)c_hook, (void**)&orig);
    MH_QueueEnableHook(addr);
    return true;
  };
};
