cmake_minimum_required(VERSION 3.15)
project(easy2d)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/example/bin)

if (MSVC)
  set(COMPILE_OPTIONS
    /Wall
    /wd4820
    /wd4456
    /wd5045
    /wd4061
    /D_CRT_SECURE_NO_WARNINGS)
else()
  set(COMPILE_OPTIONS
    -Wall
    -Wextra
    -Wpedantic
    -Wno-strict-prototypes
    -Wno-deprecated-declarations)
endif()

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  set(BUILD_TYPE _DEBUG)
else()
  set(BUILD_TYPE NDEBUG)
endif()

add_library(${PROJECT_NAME}
  ${CMAKE_CURRENT_LIST_DIR}/src/drawing.c
  ${CMAKE_CURRENT_LIST_DIR}/src/image.c
  ${CMAKE_CURRENT_LIST_DIR}/src/text.c
  ${CMAKE_CURRENT_LIST_DIR}/src/time.c
  ${CMAKE_CURRENT_LIST_DIR}/src/window.c
  ${CMAKE_CURRENT_LIST_DIR}/src/winmain.c
  ${CMAKE_CURRENT_LIST_DIR}/src/event.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTIONS})

# add_executable(stars ${CMAKE_CURRENT_LIST_DIR}/example/stars.c)
# target_include_directories(stars PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
# target_compile_options(stars PRIVATE ${COMPILE_OPTIONS})
# target_link_libraries(stars PRIVATE easy2d user32 gdi32 winmm)

# add_executable(stars ${CMAKE_CURRENT_LIST_DIR}/example/stars.c)
# target_include_directories(stars PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
# target_compile_options(stars PRIVATE ${COMPILE_OPTIONS})
# target_link_libraries(stars PRIVATE easy2d user32 gdi32 winmm)

add_subdirectory(example)
