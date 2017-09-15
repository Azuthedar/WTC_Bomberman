#include "../Inc/Particle_manager.hpp"

Particle_manager::Particle_manager()
{
    return ;
}

Particle_manager::Particle_manager( float const &tmp_particle_speed, float const &tmp_Total_particles, float const &tmp_gravity, float const &tmp_LifeLength )
{
    this->particle_speed = tmp_particle_speed;
    this->Total_particles = tmp_Total_particles;
    this->Gravity = tmp_gravity;
    this->Life_length = tmp_LifeLength;
}

Particle_manager::~Particle_manager()
{
    return ;
}

void Particle_manager::manage_particles( const GLfloat &DeltaTime )
{
    bool tmp_response = false;
    //std::cout << "this Many particles so far " << this->particle_array.size() << std::endl;
    for (GLuint count = 0; count < this->particle_array.size(); count++)
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

void Particle_manager::Generate_Particles( glm::vec3 const &tmp_Origin_Position, GLfloat &tmp_delta_time )
{
    float expected_particles = this->Total_particles; //* tmp_delta_time;
    float deeznuts;
    deeznuts = tmp_delta_time;
    int count = floor( expected_particles );

    const float MIN_RAND = -1.0f, MAX_RAND = 1.0f;
    const float range = MAX_RAND - MIN_RAND;

    glm::vec3 temp_pos = glm::vec3(0.0f);
    //std::cout << count << std::endl;
    //float diff = expected_particles % 1;
    for ( int i = 0; i < count; i++)
    {
        temp_pos = tmp_Origin_Position;
        float dirX = 0.0f;
        float dirZ = 0.0f;

        //std::cout << " direction z " << dirZ << " Direction X " << dirX << std::endl;

        glm::vec3 velocity = glm::vec3( dirX, 1.0f, dirZ );
        velocity = glm::normalize( velocity );

        velocity.x *= this->particle_speed;
        // velocity.y *= this->particle_speed;
        velocity.z *= this->particle_speed;

        temp_pos.x += range * ((((float) rand()) / (float) RAND_MAX)) + MIN_RAND;
        temp_pos.y = 1.0f + (range * ((((float) rand()) / (float) RAND_MAX)) + MIN_RAND);
        temp_pos.z += range * ((((float) rand()) / (float) RAND_MAX)) + MIN_RAND;

        this->particle_array.push_back( new Particles( this->Texture_Data , temp_pos, velocity, this->Gravity, this->Life_length, 0.0f, PARTICLE_SIZE ) );
    }
}

void Particle_manager::SetTexture( Texture const &texture_data )
{
    this->Texture_Data = texture_data;
}

Particles *Particle_manager::GetParticle( int const &pos ) const
{
    return ( this->particle_array[pos] );
}

std::vector < Particles * > Particle_manager::GetParticleArray(  ) const
{
    return ( this->particle_array );
}
