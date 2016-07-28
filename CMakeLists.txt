cmake_minimum_required(VERSION 2.8.4)
project(I_wanna_kill_the_boshy)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14 -Wall")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

IF (WIN32)
set(OPENGL_LIBRARIES -lopengl32)
ELSE()
set(OPENGL_LIBRARIES -ldl -lGLEW -lGL -lGLU)
ENDIF()

file(GLOB_RECURSE ENGINE_SOURCE_FILES engine/*.cpp engine/*.c)
file(GLOB_RECURSE GAME_SOURCE_FILES game/*.cpp game/*.c)
file(GLOB_RECURSE FRAMEWORK_SOURCE_FILES framework/*.cpp framework/*.c)

# compile the engine, yeast
add_executable(yeast ${ENGINE_SOURCE_FILES} engine/graphics/algorithms/CalculateMaxLum.cpp engine/graphics/algorithms/CalculateMaxLum.h)
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
# add_executable(framework ${FRAMEWORK_SOURCE_FILES})
# target_include_directories(framework PRIVATE engine)
# target_link_libraries(framework yeast)

# compile the sample game
# add_library(I_wanna_kill_the_boshy SHARED ${GAME_SOURCE_FILES})
# target_include_directories(I_wanna_kill_the_boshy PRIVATE engine)
# target_link_libraries(I_wanna_kill_the_boshy yeast)

#add_library(angelscript_lib STATIC IMPORTED)
#set_property(TARGET angelscript_lib PROPERTY
#    IMPORTED_LOCATION "/lib/libAngelscript.a")

#add_dependencies(I_wanna_kill_the_boshy  angelscript_lib)