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
    glGenBuffers( 1, &this->VBO );
    glGenBuffers( 1, &this->EBO );

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

void Mesh::Draw( Shaders shader )
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
