#pragma once

#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <istream>
#include <sstream>
#include <fstream>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Soil/SOIL2/SOIL2.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture
{
    GLuint id;
    std::string type;
    aiString path;
    int num_rows;
    int num_columns;
};

struct Skybox_s
{
    GLuint Skybox_VAO;
    GLuint Skybox_VBO;
    GLuint Cubemap_text;
};

struct Particles_s
{
    GLuint Particle_VAO;
    GLuint Particle_VBO;
    GLuint Particle_text;
};
