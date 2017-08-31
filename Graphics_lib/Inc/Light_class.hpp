#pragma once

#include "Base.hpp"

class Light_class
{
    private:
        glm::vec3 position;
        glm::vec3 colour;

    public:

        Light_class();
        Light_class( glm::vec3 const &tmp_pos, glm::vec3 const &tmp_colour );

        void SetPosition( glm::vec3 const &tmp_pos );
        void SetColour( glm::vec3 const &tmp_colour );

        glm::vec3 GetColour() const;
        glm::vec3 GetPosition() const;

};
