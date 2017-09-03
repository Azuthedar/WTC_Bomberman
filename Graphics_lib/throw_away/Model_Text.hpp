#pragma once

#include "Base.hpp"

class Model_Text
{
    private:
        GLuint Texture_ID;


    public:
        Model_Text();

        Model_Text( GLuint text_id );

        void SetTextureID( GLuint &Texture_ID );
        GLuint GetTextureID( void ) const;

        Model_Text &operator=(Model_Text const &obj);

};
