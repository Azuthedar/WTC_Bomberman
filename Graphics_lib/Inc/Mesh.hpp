#pragma once

#include "Base.hpp"
#include "Shaders.hpp"

using namespace std;

class Mesh
{
    private:
        GLuint VAO;
        GLuint VBO;
        GLuint EBO;

        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        std::vector<Texture> textures;

        void setupMesh( );

    public:

        Mesh( std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures );
        Mesh();

        void Draw( Shaders shader );
};
