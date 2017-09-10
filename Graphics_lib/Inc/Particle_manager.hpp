#pragma once

#include "Base.hpp"
#include "Particles.hpp"

class Particle_manager
{
    private:
        std::vector < Particles * > particle_array;

    public:

        Particle_manager();
        ~Particle_manager();

        void manage_particles( const GLfloat &DeltaTime );
        void push_particle(  glm::vec3 const &tmp_Position, glm::vec3 const &tmp_Velocity, GLfloat const &tmp_gravity, GLfloat const &tmp_LifeLength, GLfloat const &tmp_Rotation, GLfloat const &tmp_Scale );
        Particles *GetParticle( int const &pos ) const;
        std::vector < Particles * > GetParticleArray( ) const;
};
