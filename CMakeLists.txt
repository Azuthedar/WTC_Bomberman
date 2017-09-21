cmake_minimum_required (VERSION 3.5)

set(PROJECT_NAME "Bomberman")
project (${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_BUILD_TYPE Debug)
set(PLATFORM ${CMAKE_SYSTEM_NAME})

message("Detected Platform ${PLATFORM}")

if (WIN32)

    message("UNIX")
    set(LIB_PATH "/usr")
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

    #NANO GUI
    set(NANO_INCLUDE "Menu_lib/nanogui/include/")
    set(NANO_LIB_DIR "Menu_lib/nanogui/build/")
    set(NANO_NAME nanogui)

    #SDL2
	set(SDL_INCLUDE ${LIB_INLCUDE})
    set(SDL_LIB_DIR ${LIB_LIBRARY})
    set(SDL_NAME SDL2)
    message ("Found SDL library at ${SDL_LIB_DIR}")

	#SDL_MIXER
	set(SDL_MIXER_INCLUDE ${LIB_INLCUDE})
    set(SDL_MIXER_LIB_DIR ${LIB_LIBRARY})
    set(SDL_MIXER_NAME SDL2_mixer)
    message ("Found glew library at ${SDL_MIXER_LIB_DIR}")

    #OPENGL
    find_package(OpenGL)
    set(OPENGL_INCLUDE ${OPENGL_INCLUDE_DIR})
    message ("Found OpenGL library at ${OPENGL_INCLUDE}")
    message ("Found OpenGL library at ${OPENGL_gl_LIBRARY}")

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
    set(SOIL_INCLUDE "Libs/Soil/SOIL2/")
    set(SOIL_LIB_DIR "Libs/Soil/Mac/")
    set(SOIL_LIB ${SOIL_LIB_DIR}libsoil2.a)
    set(SOIL_NAME soil2)

	#SDL2
	set(SDL_INCLUDE "~/.brew/include/")
    set(SDL_LIB_DIR "~/.brew/lib/")
    set(SDL_NAME SDL2)
    message ("Found SDL library at ${SDL_LIB_DIR}")

	#SDL_MIXER
	set(SDL_MIXER_INCLUDE "~/.brew/include/")
    set(SDL_MIXER_LIB_DIR "~/.brew/lib/")
    set(SDL_MIXER_NAME SDL2_mixer)
    message ("Found glew library at ${SDL_MIXER_LIB_DIR}")

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

    #NANO GUI
    set(NANO_INCLUDE "Libs/nanogui/include/")
    set(NANO_LIB_DIR "Libs/nanogui/build/")
    set(NANO_NAME nanogui)

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
set(MENU_LIB ${CMAKE_CURRENT_SOURCE_DIR}/Menu_lib/Src/ )

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
        ${SRC}Config.class.cpp

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
        ${GRAPHICS_SRC}Particle_manager.cpp

        ${SOUND_LIB}SoundEngine.cpp

        ${MENU_LIB}Menu_Engine.cpp
        )

#INCLUDE_FILES
set(INCLUDE "./Game_Engine/include/")
set(GRAPHICS_INCLUDE "./Graphics_lib/Inc/")
set(SOUND_INC "./Sound_lib/include/")
set(MENU_INC "./Menu_lib/include/")

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
        ${INCLUDE}Config.class.hpp

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
        ${GRAPHICS_INCLUDE}Particle_manager.hpp

        ${SOUND_INC}SoundEngine.hpp

        ${MENU_INC}Menu_Engine.hpp
        )


set(BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${INCLUDE} ${GRAPHICS_INCLUDE} ${NANO_INCLUDE} ${ASSIMP_INC} ${SOIL_INCLUDE} ${SDL_INCLUDE} ${SDL_MIXER_INCLUDE} ${GLEW_INCLUDE} ${GLM_INCLUDE} ${OPENGL_INCLUDE} ${GLFW_INCLUDE})

link_directories(${GLFW_LIB_PATH} ${SOIL_LIB_DIR} ${NANO_LIB_DIR} ${ASSIMP_LIB_DIR} ${SDL_LIB_DIR} ${SDL_MIXER_LIB_DIR} ${GLEW_LIB_DIR} ${CEGUI_LIB_PATH})

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADERS})

target_link_libraries(${PROJECT_NAME} ${FRAMEWORK_COCOA} ${NANO_NAME} ${ASSIMP_NAME} ${OPENGL_gl_LIBRARY} ${GLEW_NAME} ${SOIL_NAME} ${SDL_NAME}  ${SDL_MIXER_NAME} ${CEGUI_LIBS_DYNAMIC} ${GLFW_NAME})
