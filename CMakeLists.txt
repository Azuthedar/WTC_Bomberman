cmake_minimum_required (VERSION 3.5)

set(PROJECT_NAME "Bomberman")
project (${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_BUILD_TYPE Debug)
set(PLATFORM ${CMAKE_SYSTEM_NAME})

message("Detected Platform ${PLATFORM}")

if (WIN_32)

    message("UNIX")
    set(LIB_PATH "/usr/")
    set(LIB_INCLUDE "${LIB_PATH}/include/")
    set(LIB_LIBRARY "${LIB_PATH}/lib/x86_64-linux-gnu/")

    #GLEW
    set(GLEW_INCLUDE ${LIB_INLCUDE})
    set(GLEW_LIB_DIR ${LIB_LIBRARY})
    #set(GLEW_LIB ${GLEW_LIB_DIR}libGLEW.a)
    set(GLEW_NAME GLEW)
    message ("Found glew library at ${GLEW_LIBRARY}")

    #SOIL
    set(SOIL_INCLUDE "Graphics_lib/Soil/SOIL2/")
    set(SOIL_LIB_DIR "Graphics_lib/Soil/Unix/")
    set(SOIL_LIB ${SOIL_LIB_DIR}libsoil2.a)
    set(SOIL_NAME soil2-debug)

    #OPENAL
    find_package(OpenAL)
    set(OPENAL_INCLUDE ${OPENAL_INCLUDE_DIR})
    set(OPENAL_LIB_DIR ${OPENAL_LIBRARY})
    message ("Found OpenAL library at ${OPENAL_INCLUDE}")
    message ("Found OpenAL library at ${OPENAL_LIBRARY}")

    #ALUT
    set(ALUT_INCLUDE ${LIB_INLCUDE})
    set(ALUT_LIB_DIR ${LIB_LIBRARY})
    #set(ALUT_LIB libalut.a)
    set(ALUT_NAME alut)
    message ("Found ALUT library at ${ALUT_LIB}")

    #OPENGL
    find_package(OpenGL)
    set(OPENGL_INCLUDE ${OPENGL_INCLUDE_DIR})
    message ("Found OpenGL library at ${OPENGL_INCLUDE}")
    message ("Found OpenGL library at ${OPENGL_gl_LIBRARY}")

    #THREADS
    set(THREADS_INCLUDE ${LIB_INLCUDE})
    set(THREADS_LIB_DIR ${LIB_LIBRARY})
    set(THREADS_NAME pthread)

    #ASSIMP
    set(ASSIMP_INC ${LIB_INLCUDE})
    set(ASSIMP_LIB_DIR ${LIB_LIBRARY})
    #set(ASSIMP_LIB ${ASSIMP_LIB_DIR}/libassimp.4.0.1.dylib)
    set(ASSIMP_NAME assimp)
    message ("Found ASSIMP library at ${ASSIMP_LIB}")

    #GLFW
    set(GLFW_INCLUDE ${LIB_INLCUDE})
    set(GLFW_LIB_PATH ${LIB_LIBRARY})
    #set(GLFW_DYLIB libglfw.3.2.dylib)
    set(GLFW_NAME glfw)

    #GLM
    set(GLM_INCLUDE ${LIB_INLCUDE})

    set(FRAMEWORK_COCOA "")

else()

    message("MAC")

    set(BREW ~/.brew)
    set(BREW_INCLUDE ${BREW}/include)
    set(BREW_LIB ${BREW}/lib)

    #GLEW
    set(GLEW_INCLUDE "~/.brew/include/")
    set(GLEW_LIB_DIR "~/.brew/lib/")
    set(GLEW_LIB ${GLEW_LIB_DIR}libGLEW.a)
    set(GLEW_NAME GLEW)
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
    set(ASSIMP_NAME assimp)
    message ("Found ASSIMP library at ${ASSIMP_LIB}")

    #GLFW
    set(GLFW_INCLUDE ${BREW_INCLUDE}/)
    set(GLFW_LIB_PATH ${BREW_LIB}/)
    set(GLFW_DYLIB libglfw.3.2.dylib)
    set(GLFW_NAME glfw)
    set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR})

    set(CEGUI_LIBS_DYNAMIC  CEGUIBase-0.dylib
            CEGUICommonDialogs-0.dylib
            CEGUICoreWindowRendererSet.dylib
            CEGUIExpatParser.dylib
            CEGUIOpenGLRenderer-0.dylib
            CEGUISILLYImageCodec.dylib)
    set(CEGUI_LIB_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/libs/darwin/cegui)

    #GLM
    set(GLM_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/libs/glm)

    set(FRAMEWORK_COCOA "-framework Cocoa")

endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR})

message("Current Source Directory ${CMAKE_CURRENT_SOURCE_DIR}")

#SOURCE_FILES
set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/Game_Engine/src/ )
set(GRAPHICS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/Graphics_lib/Src/ )
set(SOUND_LIB ${CMAKE_CURRENT_SOURCE_DIR}/Sound_lib/src/ )

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
        ${GRAPHICS_SRC}Render.cpp
        ${GRAPHICS_SRC}Shaders.cpp
        ${GRAPHICS_SRC}Component.cpp
        ${GRAPHICS_SRC}Mesh.cpp
        ${GRAPHICS_SRC}Model.cpp
        ${GRAPHICS_SRC}Light_class.cpp
        ${GRAPHICS_SRC}Render_Engine.cpp
        ${GRAPHICS_SRC}Particles.cpp

        ${SOUND_LIB}SoundEngine.cpp
        )

#INCLUDE_FILES
set(INCLUDE "./Game_Engine/include/")
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
        ${GRAPHICS_INCLUDE}Render.hpp
        ${GRAPHICS_INCLUDE}Shaders.hpp
        ${GRAPHICS_INCLUDE}Camera.hpp
        ${GRAPHICS_INCLUDE}Model.hpp
        ${GRAPHICS_INCLUDE}Data_Loader.hpp
        ${GRAPHICS_INCLUDE}Mesh.hpp
        ${GRAPHICS_INCLUDE}Render_Engine.hpp
        ${GRAPHICS_INCLUDE}Particles.hpp

        ${SOUND_INC}SoundEngine.hpp
        )


set(BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${INCLUDE} ${GRAPHICS_INCLUDE} ${ASSIMP_INC} ${ALUT_INCLUDE} ${SOIL_INCLUDE} ${OPENAL_INCLUDE} ${THREADS_INCLUDE} ${GLEW_INCLUDE} ${GLM_INCLUDE} ${OPENGL_INCLUDE} ${GLFW_INCLUDE})

link_directories(${GLFW_LIB_PATH} ${SOIL_LIB_DIR} ${ASSIMP_LIB_DIR} ${ALUT_LIB_DIR} ${THREADS_LIB_DIR} ${GLEW_LIB_DIR} ${CEGUI_LIB_PATH})

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADERS})

target_link_libraries(${PROJECT_NAME} ${FRAMEWORK_COCOA} ${ASSIMP_NAME} ${THREADS_NAME} ${OPENGL_gl_LIBRARY} ${GLEW_NAME} ${OPENAL_LIBRARY} ${SOIL_NAME} ${ALUT_NAME} ${CEGUI_LIBS_DYNAMIC} ${GLFW_NAME})
