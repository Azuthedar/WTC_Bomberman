#pragma once

#include "Base.hpp"
#include "Particles.hpp"

class Particle_manager
{
    private:
        std::vector < Particles * > particle_array;
        float particle_speed;
        float Total_particles;
        float Gravity;
        float Life_length;
        Texture Texture_Data;

    public:

        Particle_manager();
        Particle_manager( float const &tmp_particle_speed, float const &tmp_Total_particles, float const &tmp_gravity, float const &tmp_LifeLength );
        ~Particle_manager();

        void manage_particles( const GLfloat &DeltaTime );
        void Generate_Particles( glm::vec3 const &tmp_Origin_Position, GLfloat &tmp_delta_time );
        Particles *GetParticle( int const &pos ) const;
        std::vector < Particles * > GetParticleArray( ) const;

        void SetTexture( Texture const &texture_data );
};
