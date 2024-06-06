cmake_minimum_required(VERSION 3.1...3.29)

project(
  StrackerLoader
  VERSION 1.0
  LANGUAGES CXX
)

set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreaded)

add_subdirectory(external/minhook)

add_library(dinput8 SHARED DllLoader/injectordll.cpp DllLoader/Dinput8.cpp)

add_library(loader SHARED
  MHWLoader/config.cpp
  MHWLoader/loaderdll.cpp
  MHWLoader/log.cpp
)
target_include_directories(loader PRIVATE external/json PUBLIC MHWLoader)
target_link_libraries(loader PRIVATE minhook)
target_compile_features(loader PRIVATE cxx_std_20)
target_compile_definitions(loader PRIVATE MHWLOADER_EXPORTS)
set_property(TARGET loader PROPERTY CXX_STANDARD 20)

add_library(plugin_utils INTERFACE)
target_include_directories(plugin_utils INTERFACE Plugins/utils)
target_link_libraries(plugin_utils INTERFACE loader)

add_library(QuestLoader SHARED Plugins/QuestLoader/dllmain.cpp)
target_link_libraries(QuestLoader PRIVATE loader minhook plugin_utils)
target_compile_features(QuestLoader PRIVATE cxx_std_20)

add_library(MonsterLoader SHARED Plugins/MonsterLoader/dllmain.cpp)
target_link_libraries(MonsterLoader PRIVATE loader minhook plugin_utils)
target_compile_features(MonsterLoader PRIVATE cxx_std_20)
