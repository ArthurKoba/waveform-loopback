cmake_minimum_required(VERSION 3.20)
project(Visualizer)

set(BUILD_SHARED_LIBS)
# set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

find_package(OpenGL REQUIRED)

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

add_subdirectory(external/glfw)

if (MSVC)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
endif()

add_executable(${PROJECT_NAME} WIN32 source/main.cpp source/loopback.cpp source/window.cpp source/visualizer.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} glfw ${OPENGL_LIBRARIES})
