cmake_minimum_required(VERSION 3.15)
project(e2d-examples)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
set(LIBRARIES easy2d user32 gdi32 winmm)

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

add_executable(hello ${CMAKE_CURRENT_LIST_DIR}/hello.c)
target_include_directories(hello PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../include)
target_compile_options(hello PRIVATE ${COMPILE_OPTIONS})
target_link_libraries(hello PRIVATE ${LIBRARIES})

add_executable(stars ${CMAKE_CURRENT_LIST_DIR}/stars.c)
target_include_directories(stars PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../include)
target_compile_options(stars PRIVATE ${COMPILE_OPTIONS})
target_link_libraries(stars PRIVATE ${LIBRARIES})
