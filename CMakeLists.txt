cmake_minimum_required (VERSION 3.5)

set(PROJECT_NAME "Bomberman")
project (${PROJECT_NAME})

set(glew_USE_STATIC_LIBS ON)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_BUILD_TYPE Debug)
set(PLATFORM ${CMAKE_SYSTEM_NAME})

message("Detected Platform ${PLATFORM}")

set(BREW ~/.brew)
set(BREW_INCLUDE ${BREW}/include)
set(BREW_LIB ${BREW}/lib)

#GLEW
set(GLEW_INCLUDE "~/.brew/opt/glew/include/")
set(GLEW_LIB_DIR "~/.brew/opt/glew/lib/"})
set(GLEW_LIB ${GLEW_LIB_DIR}libGLEW.2.0.dylib)
set(GLEW_NAME GLEW.2.0)
message ("Found glew library at ${GLEW_LIB}")

#SOIL
set(SOIL_INCLUDE "Graphics_lib/Soil/SOIL2/")
set(SOIL_LIB_DIR "Graphics_lib/Soil/Mac/")
set(SOIL_LIB ${SOIL_LIB_DIR}libsoil2.a)
set(SOIL_NAME soil2)

#OPENAL
find_package(OpenAL)
set(OPENAL_INCLUDE ${OPENAL_INCLUDE_DIR})
set(OPENAL_LIB_DIR ${OPENAL_LIBRARY})
message ("Found OpenAL library at ${OPENAL_INCLUDE}")
message ("Found OpenAL library at ${OPENAL_LIBRARY}")

#ALUT
set(ALUT_INCLUDE ${BREW_INCLUDE}/)
set(ALUT_LIB_DIR ${BREW_LIB})
set(ALUT_LIB libalut.a)
set(ALUT_NAME alut)
message ("Found ALUT library at ${ALUT_LIB}")

#OPENGL
find_package(OpenGL)
set(OPENGL_INCLUDE ${OPENGL_INCLUDE_DIR}/Headers)
message ("Found OpenGL library at ${OPENGL_INCLUDE}")
message ("Found OpenGL library at ${OPENGL_gl_LIBRARY}")

#ASSIMP
set(ASSIMP_INC ${BREW_INCLUDE}/)
set(ASSIMP_LIB_DIR ${BREW_LIB})
set(ASSIMP_LIB ${ASSIMP_LIB_DIR}/libassimp.4.0.1.dylib)
set(ASSIMP_NAME ASSMIP)
message ("Found ASSIMP library at ${ASSIMP_LIB}")

set(CEGUI_LIBS_DYNAMIC  CEGUIBase-0.dylib
        CEGUICommonDialogs-0.dylib
        CEGUICoreWindowRendererSet.dylib
        CEGUIExpatParser.dylib
        CEGUIOpenGLRenderer-0.dylib
        CEGUISILLYImageCodec.dylib)
set(CEGUI_LIB_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/darwin/cegui)

#GLFW
set(GLFW_INCLUDE ${BREW_INCLUDE}/)
set(GLFW_LIB_PATH ${BREW_LIB}/)
set(GLFW_DYLIB libglfw.3.2.dylib)
set(GLFW_NAME GLFW)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR})

#GLM
set(GLM_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/libs/glm)

#SOURCE_FILES
set(SRC "src/")
set(GRAPHICS_SRC "./Graphics_lib/Src/")
set(SOUND_LIB "./Sound_lib/src/")

set(SOURCE
        ${SRC}AEntity.class.cpp
        ${SRC}Enemy.class.cpp
        ${SRC}Explosion.class.cpp
        ${SRC}Gate.class.cpp
        ${SRC}Powerup.class.cpp
        ${SRC}main.cpp
        ${SRC}Bomb.class.cpp
        ${SRC}Exception.class.cpp
        ${SRC}GameEngine.class.cpp
        ${SRC}Player.class.cpp
        ${SRC}Wall.class.cpp

        ${GRAPHICS_SRC}Camera.cpp
        ${GRAPHICS_SRC}Data_Loader.cpp
        ${GRAPHICS_SRC}Model_Text.cpp
        ${GRAPHICS_SRC}Render.cpp
        ${GRAPHICS_SRC}Shaders.cpp
        ${GRAPHICS_SRC}Component.cpp
        ${GRAPHICS_SRC}Light_class.cpp
        ${GRAPHICS_SRC}Model.cpp
        ${GRAPHICS_SRC}Object_Loader.cpp
        ${GRAPHICS_SRC}Render_Engine.cpp
        ${GRAPHICS_SRC}Text_Model.cpp

        ${SOUND_LIB}SoundEngine.cpp
        )

#INCLUDE_FILES
set(INCLUDE "./include/")
set(GRAPHICS_INCLUDE "./Graphics_lib/Inc/")
set(SOUND_INC "./Sound_lib/include/")

set(HEADERS
        ${INCLUDE}AEntity.class.hpp
        ${INCLUDE}Enemy.class.hpp
        ${INCLUDE}Explosion.class.hpp
        ${INCLUDE}Gate.class.hpp
        ${INCLUDE}Powerup.class.hpp
        ${INCLUDE}main.hpp
        ${INCLUDE}Bomb.class.hpp
        ${INCLUDE}Exception.class.hpp
        ${INCLUDE}GameEngine.class.hpp
        ${INCLUDE}Player.class.hpp
        ${INCLUDE}Wall.class.hpp

        ${GRAPHICS_INCLUDE}Base.hpp
        ${GRAPHICS_INCLUDE}Component.hpp
        ${GRAPHICS_INCLUDE}Light_class.hpp
        ${GRAPHICS_INCLUDE}Model_Text.hpp
        ${GRAPHICS_INCLUDE}Render.hpp
        ${GRAPHICS_INCLUDE}Shaders.hpp
        ${GRAPHICS_INCLUDE}Camera.hpp
        ${GRAPHICS_INCLUDE}Data_Loader.hpp
        ${GRAPHICS_INCLUDE}Model.hpp
        ${GRAPHICS_INCLUDE}Object_Loader.hpp
        ${GRAPHICS_INCLUDE}Render_Engine.hpp
        ${GRAPHICS_INCLUDE}Text_Model.hpp
        ${GRAPHICS_INCLUDE}platform.hpp

        ${SOUND_INC}SoundEngine.hpp
        )


set(BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${INCLUDE} ${GRAPHICS_INCLUDE} ${ALUT_INCLUDE} ${SOIL_INCLUDE} ${OPENAL_INCLUDE} ${GLEW_INCLUDE} ${GLM_INCLUDE} ${OPENGL_INCLUDE} ${GLFW_INCLUDE})

link_directories(${GLFW_LIB_PATH} ${SOIL_LIB_DIR} ${ALUT_LIB_DIR} ${GLEW_LIB_DIR} ${CEGUI_LIB_PATH})

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADERS})

target_link_libraries(${PROJECT_NAME} "-framework Cocoa" ${OPENGL_gl_LIBRARY} ${GLEW_NAME} ${OPENAL_LIBRARY} ${SOIL_NAME} ${ALUT_LIB} ${CEGUI_LIBS_DYNAMIC} ${GLFW_DYLIB})
