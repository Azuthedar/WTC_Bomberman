#pragma once

#include "Base.hpp"
#include "Shaders.hpp"

class Mesh
{
    private:
        GLuint VAO;
        GLuint VBO;
        GLuint EBO;

        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        std::vector<Texture> textures;
        Exceptions excep;

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
        const std::vector<Vertex> &getVertices() const;
        const std::vector<GLuint> &getIndices() const;
        const std::vector<Texture> &getTextures() const;
};
