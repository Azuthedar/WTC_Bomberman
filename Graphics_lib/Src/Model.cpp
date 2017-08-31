#include "../Inc/Model.hpp"

Model::Model()
{
    return ;
}

Model::Model( GLuint const &vao_id, unsigned int const &vert_count )
{
    this->VAO_ID = vao_id;
    this->vertex_count = vert_count;
}

Model &Model::operator=(Model const &obj)
{
    this->VAO_ID = obj.GetVAO();
    this->vertex_count = obj.GetVertexCount();

    return (*this);
}

Model::~Model()
{
    return ;
}

GLuint Model::GetVAO() const
{
    return ( this->VAO_ID );
}

unsigned int Model::GetVertexCount() const
{
    return ( this->vertex_count );
}
