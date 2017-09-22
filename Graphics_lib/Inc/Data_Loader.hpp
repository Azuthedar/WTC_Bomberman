#pragma once

#include "Base.hpp"

class Data_Loader
{
    private:

        std::vector < GLuint > VAO;
        std::vector < GLuint > VBO;
        std::vector < GLuint > Texture_ID;
        Exceptions excep;

        unsigned int GetArrayLen( GLfloat *tmp );
        void Store_Data( int attrib_number, GLuint data_size , int data_num,  GLfloat *data );
        void Bind_toBuffer( GLuint *indicies, GLuint data_size );
        GLuint Create_VAO();

    public:

        Data_Loader();
        ~Data_Loader();

        Data_Loader(Data_Loader const &src);
        Data_Loader &operator=(Data_Loader const &rhs);

        void Unbind_VAO();

        GLuint LoadCubemap( std::vector<std::string> &texture_paths );
        GLuint load_texture( const char *texture_path, std::string directory );

        const std::vector<GLuint> &getVAO() const;
        const std::vector<GLuint> &getVBO() const;
        const std::vector<GLuint> &getTexture_ID() const;
};
