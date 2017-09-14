#include "../Inc/Data_Loader.hpp"

Data_Loader::Data_Loader()
{
    return ;
}

Data_Loader::~Data_Loader()
{
    for (unsigned int count = 0; count < this->VAO.size(); count++)
    {
        glDeleteVertexArrays( 1, &this->VAO[count] );
    }

    for (unsigned int count = 0; count < this->VBO.size(); count++)
    {
        glDeleteBuffers( 1, &this->VBO[count] );
    }

    return ;
}

GLuint Data_Loader::load_texture( const char *texture_path, std::string directory )
{
    GLuint texture = 0;

    std::string filename = std::string( texture_path );
    filename = directory + '/' + filename;

    int width, height;
    glGenTextures(1, &texture);
    glBindTexture( GL_TEXTURE_2D, texture);

    this->Texture_ID.push_back( texture );

    //std::cout << "LOAD ISSS " << std::endl;

    unsigned char *image = SOIL_load_image(filename.c_str() , &width, &height, 0, SOIL_LOAD_RGB);

    //Failed to load texture?

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap( GL_TEXTURE_2D );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    SOIL_free_image_data( image );
    glBindTexture( GL_TEXTURE_2D, 0);

   // std::cout << " BEFOR LOADISS RET " << std::endl;

    return ( texture );
}

unsigned int Data_Loader::GetArrayLen( GLfloat *tmp )
{
    int count = 0;

    while ( tmp[count] != 10.0f)
    {
        count++;
    }

   // std::cout << count << std::endl;
    exit(7);

    return ( count );
}

GLuint Data_Loader::LoadCubemap( std::vector<std::string> &texture_paths )
{
    GLuint textureID;
    glGenTextures( 1, &textureID );

    int imageWidth, imageHeight;
    unsigned char *image;

    glBindTexture( GL_TEXTURE_CUBE_MAP, textureID );

    for ( GLuint i = 0; i < texture_paths.size( ); i++ )
    {
        image = SOIL_load_image( texture_paths[i].c_str() , &imageWidth, &imageHeight, 0, SOIL_LOAD_RGB );
        glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
        SOIL_free_image_data( image );
    }
    //Failed to load Cubemap?
    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );
    glBindTexture( GL_TEXTURE_CUBE_MAP, 0);

    return textureID;
}

void Data_Loader::Bind_toBuffer( GLuint *indicies, GLuint data_size )
{
    GLuint tmp_EBO = 0;

    glGenBuffers( 1, &tmp_EBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , tmp_EBO );

    this->VBO.push_back( tmp_EBO );

    glBufferData( GL_ELEMENT_ARRAY_BUFFER, data_size , indicies, GL_STATIC_DRAW );
    //Failed to create Indices array?

    //glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 3* sizeof( GLfloat ), ( GLvoid *) 0 );
    //glEnableVertexAttribArray( 1 );
}

GLuint Data_Loader::Create_VAO()
{
    GLuint tmp_vao = 0;

    glGenVertexArrays( 1, &tmp_vao );
    glBindVertexArray( tmp_vao );

   // std::cout << " VATAI tertete " <<  tmp_vao << std::endl;
   //Failed To Create VAO?

    this->VAO.push_back( tmp_vao );

<<<<<<< HEAD
=======
    for (GLuint count = 0; count < this->VAO.size(); count++ )
    {
       // std::cout << " THEM PUSHIES " << this->VAO[count] << std::endl;
    }

>>>>>>> 6608d4df625cc8a3e7cbe7fa1fdedb11fbfcd11c
    return ( tmp_vao );
}

void Data_Loader::Store_Data( int attrib_number, GLuint data_size , int data_num,  GLfloat *data )
{
    GLuint tmp_vbo = 0;

    glGenBuffers( 1, &tmp_vbo ); // Generates a VBO Buffer

    this->VBO.push_back( tmp_vbo );

    //Failed To Store object data?

    //std::cout << "STORE DATAT " << std::endl;

    //binds VBO
    glBindBuffer( GL_ARRAY_BUFFER, tmp_vbo );

    //Copies Vertex data into VBO Bound Memory
    glBufferData( GL_ARRAY_BUFFER, data_size , data, GL_STATIC_DRAW );

    glVertexAttribPointer( attrib_number, data_num, GL_FLOAT, GL_FALSE, data_num * sizeof( GLfloat ), ( GLvoid *) 0 );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void Data_Loader::Unbind_VAO()
{
    glBindVertexArray( 0 );
}
