#include "../Inc/Light_class.hpp"

Light_class::Light_class()
{
    return ;
}

Light_class::Light_class( glm::vec3 const &tmp_pos, glm::vec3 const &tmp_colour )
{
    this->position = tmp_pos;
    this->colour = tmp_colour;
}

void Light_class::SetPosition( glm::vec3 const &tmp_pos )
{
    this->position = tmp_pos;
}

void Light_class::SetColour( glm::vec3 const &tmp_colour )
{
    this->colour = tmp_colour;
}

glm::vec3 Light_class::GetColour() const
{
    return ( this->colour );
}

glm::vec3 Light_class::GetPosition() const
{
    return ( this->position );
}
