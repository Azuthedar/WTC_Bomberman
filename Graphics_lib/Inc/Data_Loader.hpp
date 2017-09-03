#pragma once

#include "Base.hpp"

class Data_Loader
{
    private:

        std::vector < GLuint > VAO;
        std::vector < GLuint > VBO;
        std::vector < GLuint > Texture_ID;

        unsigned int GetArrayLen( GLfloat *tmp );
        void Store_Data( int attrib_number, GLuint data_size , int data_num,  GLfloat *data );
        void Bind_toBuffer( GLuint *indicies, GLuint data_size );
        GLuint Create_VAO();

    public:

        Data_Loader();
        ~Data_Loader();

        //Model *Load_VAO( GLfloat *vert, GLuint Vert_Size, GLuint elements , GLuint *indicies, GLuint Ind_Size, GLfloat *texture_coords, GLuint Text_Size, GLfloat *normals, GLuint Norm_size );

        void Unbind_VAO();

        GLuint load_texture( const char *texture_path, std::string directory );
};
