# Need to set these env vars CC=CL CXX=CL | CC=CL.exe && CXX=CL.exe
cmake_minimum_required(VERSION 3.19)

project(StrackerLoader CXX)

# Only do these if this is the main project, and not if it is included through
# add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  set(CMAKE_CXX_STANDARD 14)
  set(CXX_STANDARD_REQUIRED ON)
  add_compile_definitions(_MBCS)
  # set_property(GLOBAL)

  # Optionally set things like CMAKE_CXX_STANDARD,
  # CMAKE_POSITION_INDEPENDENT_CODE here

  # Let's ensure -std=c++xx instead of -std=g++xx
  set(CMAKE_CXX_EXTENSIONS OFF)

  # Let's nicely support folders in IDE's
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  # Testing only available if this is the main app. Note this needs to be done
  # in the main CMakeLists since it calls enable_testing, which must be in the
  # main CMakeLists.
  include(CTest)

  # Docs only available if this is the main app
  # find_package(Doxygen)
  # if(Doxygen_FOUND)
  #   add_subdirectory(docs)
  # else()
  #   message(STATUS "Doxygen not found, not building docs")
  # endif()
endif()

include(FetchContent)
include(cmake/add_FetchContent_MakeAvailableNotAll.cmake)
FetchContent_Declare(
        nlohmann-json
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
        GIT_TAG v3.9.1
)
FetchContent_Declare(
        memorymodule
        GIT_REPOSITORY "https://github.com/fancycode/MemoryModule"
        GIT_TAG "5f83e41c3a3e7c6e8284a5c1afa5a38790809461"
)
FetchContent_Declare(
        minhook
        GIT_REPOSITORY "https://github.com/TsudaKageyu/minhook"
        GIT_TAG "3f2e34976c1685ee372a09f54c0c8c8f4240ef90"
)
FetchContent_MakeAvailableNotAll(nlohmann-json)
FetchContent_MakeAvailableNotAll(memorymodule)
FetchContent_MakeAvailableNotAll(minhook)

add_subdirectory(DllLoader)
add_subdirectory(MHWLoader)
add_subdirectory(Plugins/MonsterLoader)
add_subdirectory(Plugins/QuestLoader)
# add_subdirectory(Plugins/ClutchRework)
