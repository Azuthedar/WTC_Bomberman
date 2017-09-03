#pragma once

#include "Base.hpp"

class Model
{
    private:
        GLuint VAO_ID;
        unsigned int vertex_count;

    public:

        Model();
        Model( GLuint const &vao_id, unsigned int const &vert_count );
        ~Model();

        GLuint GetVAO() const;
        unsigned int GetVertexCount() const;

        Model &operator=(Model const &obj);
};
