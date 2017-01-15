cmake_minimum_required(VERSION 2.8.4)
project(Yeast)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14 -Wall -m32")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
#set(CMAKE_PREFIX_PATH "D:\\Qt\\5.7\\mingw53_32\\")
set(CMAKE_AUTOUIC ON)

IF (WIN32)
set(OPENGL_LIBRARIES -lopengl32)
ELSE()
set(OPENGL_LIBRARIES -ldl -lGLEW -lGL -lGLU)
ENDIF()

file(GLOB_RECURSE ENGINE_SOURCE_FILES engine/*.cpp engine/*.c)
#file(GLOB_RECURSE EDITOR_SOURCE_FILES editor/*.cpp editor/*.c)
file(GLOB_RECURSE FRAMEWORK_SOURCE_FILES framework/*.cpp framework/*.c)

# compile the engine
add_library(yeast SHARED ${ENGINE_SOURCE_FILES})
target_include_directories(yeast PRIVATE include)

IF (WIN32)
    target_link_libraries(yeast "${CMAKE_SOURCE_DIR}/lib/libSOIL.a")
    target_link_libraries(yeast "${CMAKE_SOURCE_DIR}/lib/libfreetype.a")
    target_link_libraries(yeast "${CMAKE_SOURCE_DIR}/lib/libglfw3.a")
    target_link_libraries(yeast "${CMAKE_SOURCE_DIR}/lib/libluajit.a")
    target_link_libraries(yeast ${OPENGL_LIBRARIES})
ELSE()
    target_link_libraries(yeast "/usr/local/lib/libSOIL.a")
    target_link_libraries(yeast glfw ${GLFW_LIBRARIES})
    target_link_libraries(yeast ${OPENGL_LIBRARIES})
ENDIF()

# compile the framework
add_executable(framework ${FRAMEWORK_SOURCE_FILES})
target_include_directories(framework PRIVATE engine)
target_include_directories(framework PRIVATE include)
target_link_libraries(framework yeast)

# compile the editor
# Find includes in corresponding build directories
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
#set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
#find_package(Qt5Widgets)
#find_package(Qt5Core)

#add_executable(editor ${EDITOR_SOURCE_FILES})
#set_property(TARGET editor PROPERTY QT5_NO_LINK_QTMAIN ON)
#target_include_directories(editor PRIVATE engine)
#target_include_directories(editor PRIVATE include)
#target_include_directories(editor PRIVATE editor)

IF (WIN32)
ELSE()
ENDIF()

#target_link_libraries(editor Qt5::Widgets)
#target_link_libraries(editor Qt5::Core)
#target_link_libraries(editor yeast)
