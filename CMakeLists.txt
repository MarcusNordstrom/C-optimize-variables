cmake_minimum_required(VERSION 3.0.0)
project(optimizeVariables LANGUAGES C VERSION 0.1.0)

#Debug flags (sanitizers) for clang -fsanitize=memory or -fsanitize=address
#set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -fno-omit-frame-pointer -fsanitize=memory -fsanitize=undefined")
#set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -Wall -fno-omit-frame-pointer -fsanitize=memory -fsanitize=undefined")

#Debug flags for gcc
#set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -pg")
#set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -Wall -pg")

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/C-Step-Counter/include)
set(SOURCES, "src/main.c")
file(GLOB SOURCES "src/*.c")
file(GLOB ALGO "C-Step-Counter/src/*.c")

add_executable(optimizeVariables ${SOURCES} ${ALGO})
target_link_libraries(optimizeVariables m)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
