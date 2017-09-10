#include "../Inc/Particle_manager.hpp"

Particle_manager::Particle_manager()
{
    return ;
}

Particle_manager::~Particle_manager()
{
    return ;
}

void Particle_manager::manage_particles( const GLfloat &DeltaTime )
{
    bool tmp_response = false;
    //std::cout << "this Many particles so far " << this->particle_array.size() << std::endl;
    for (int count = 0; count < this->particle_array.size(); count++)
    {
        tmp_response = this->particle_array[count]->UpdateParticle( DeltaTime );

        if (!tmp_response)
        {
            delete this->particle_array[count];
            if (this->particle_array.size() > 1)
            {
                this->particle_array.erase( this->particle_array.begin() + count, this->particle_array.begin() + (count + 1) );
            }
            else
                this->particle_array.erase( this->particle_array.begin() );
            tmp_response = false;
        }
    }
}

void Particle_manager::push_particle(  glm::vec3 const &tmp_Position, glm::vec3 const &tmp_Velocity, GLfloat const &tmp_gravity, GLfloat const &tmp_LifeLength, GLfloat const &tmp_Rotation, GLfloat const &tmp_Scale )
{
    this->particle_array.push_back( new Particles( tmp_Position, tmp_Velocity, tmp_gravity, tmp_LifeLength, tmp_Rotation, tmp_Scale ) );
}

Particles *Particle_manager::GetParticle( int const &pos ) const
{
    return ( this->particle_array[pos] );
}

std::vector < Particles * > Particle_manager::GetParticleArray(  ) const
{
    return ( this->particle_array );
}
