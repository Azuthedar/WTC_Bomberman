#pragma once

#include "Base.hpp"
#include "Shaders.hpp"
#include "Light_class.hpp"
#include "Particles.hpp"
#include "Component.hpp"

class Render
{
    private:
        glm::mat4 projection;
        glm::mat4 view_matrix;

        GLint modelLoc;
        GLint projLoc;
        GLint viewLoc;
        GLint lightLoc;
        GLint colourLoc;
        GLint shineLoc;
        GLint reflectionLoc;
        GLint ScaleLoc;
        GLint RowLoc;
        GLint OffsetLoc;

        Light_class *light = new Light_class( glm::vec3( 0.0f, 0.f, 0.0f ), glm::vec3( 1.0f, 1.0f, 1.0f ) );

    public:

        Render();
        ~Render();

        void SetViewMatrix( glm::mat4 const &tmp_matrix );
        void SetProjection( GLfloat const &tmp_zoom );
        void Load_Uniform( Shaders &shader );
        void Prep();
        void Render_( std::vector < Component * > &tmp, Shaders &shader );
        void Render_Skybox( Skybox_s &data, Shaders &shader);
        void Render_Particles( const std::vector< Particles *> &tmp, Shaders &shader, Particles_s &data );

};
