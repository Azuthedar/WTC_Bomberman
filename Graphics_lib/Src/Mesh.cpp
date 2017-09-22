#include "../Inc/Mesh.hpp"

Mesh::Mesh( std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures )
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    this->setupMesh( );
}

void Mesh::setupMesh( )
{
    glGenVertexArrays( 1, &this->VAO );
    if (this->VAO <= 0)
        excep.throwCreateVAO();
    glGenBuffers( 1, &this->VBO );
    if (this->VBO <= 0)
        excep.throwCreateVBO();
    glGenBuffers( 1, &this->EBO );
    if (this->EBO <= 0)
        excep.throwCreateIndices();

    glBindVertexArray( this->VAO );

    glBindBuffer( GL_ARRAY_BUFFER, this->VBO );
    glBufferData( GL_ARRAY_BUFFER, this->vertices.size( ) * sizeof( Vertex ), &this->vertices[0], GL_STATIC_DRAW );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->EBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, this->indices.size( ) * sizeof( GLuint ), &this->indices[0], GL_STATIC_DRAW );

    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( GLvoid * )0 );

    glEnableVertexAttribArray( 1 );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( GLvoid * )offsetof( Vertex, Normal ) );

    glEnableVertexAttribArray( 2 );
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( GLvoid * )offsetof( Vertex, TexCoords ) );

    glBindVertexArray( 0 );
}

void Mesh::Draw()
{
    for( GLuint i = 0; i < this->textures.size( ); i++ )
    {
        glActiveTexture( GL_TEXTURE0 + i );
        glBindTexture( GL_TEXTURE_2D, this->textures[i].id );
    }

    glBindVertexArray( this->VAO );
    glDrawElements( GL_TRIANGLES, this->indices.size( ), GL_UNSIGNED_INT, 0 );
    glBindVertexArray( 0 );

    for ( GLuint i = 0; i < this->textures.size( ); i++ )
    {
        glActiveTexture( GL_TEXTURE0 + i );
        glBindTexture( GL_TEXTURE_2D, 0 );
    }
}

GLuint Mesh::getVAO() const {return VAO;}
GLuint Mesh::getVBO() const {return VBO;}
GLuint Mesh::getEBO() const {return EBO;}
const std::vector<Vertex> &Mesh::getVertices() const {return vertices;}
const std::vector<GLuint> &Mesh::getIndices() const {return indices;}
const std::vector<Texture> &Mesh::getTextures() const {return textures;}

Mesh::~Mesh() {

}

Mesh::Mesh(Mesh const &src) {
    *this = src;
    return;
}

Mesh &Mesh::operator=(Mesh const &rhs) {
    this->VAO = rhs.getVAO();
    this->VBO = rhs.getVBO();
    this->EBO = rhs.getEBO();
    this->vertices = rhs.getVertices();
    this->indices = rhs.getIndices();
    this->textures = rhs.getTextures();

    return *this;
}
