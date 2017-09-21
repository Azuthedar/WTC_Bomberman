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
        ~Mesh();

        Mesh(Mesh const &src);
        Mesh &operator=(Mesh const &rhs);

        void Draw();

        GLuint getVAO() const;
        GLuint getVBO() const;
        GLuint getEBO() const;
        const vector<Vertex> &getVertices() const;
        const vector<GLuint> &getIndices() const;
        const vector<Texture> &getTextures() const;
};
