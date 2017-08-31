#include "../Inc/Model_Text.hpp"


Model_Text::Model_Text()
{
    return ;
}

Model_Text::Model_Text( GLuint text_id )
{
    this->Texture_ID = text_id;
}

void Model_Text::SetTextureID( GLuint &Texture_ID )
{
    this->Texture_ID = Texture_ID;
}

GLuint Model_Text::GetTextureID( void ) const
{
    return ( this->Texture_ID );
}


Model_Text &Model_Text::operator=(Model_Text const &obj)
{
    this->Texture_ID = obj.GetTextureID();

    return (*this);
}
