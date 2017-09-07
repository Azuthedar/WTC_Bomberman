#include "../Inc/Particles.hpp"

Particles::Particles()
{
    return ;
}

Particles::Particles( glm::vec3 &tmp_Position, glm::vec3 &tmp_Velocity, GLfloat &tmp_gravity, GLfloat &tmp_LifeLength, GLfloat &tmp_Rotation, GLfloat &tmp_Scale )
{
    this->Position = tmp_Position;
    this->Velocity = tmp_Velocity;
    this->gravity = tmp_gravity;
    this->LifeLength = tmp_LifeLength;
    this->Rotation = tmp_Rotation;
    this->Scale = tmp_Scale;
}

Particles::~Particles()
{
    return ;
}

bool Particles::UpdateParticle( GLfloat &DeltaTime )
{
    Velocity.y += -50 * this->gravity * DeltaTime;
    glm::vec3 change = this->Velocity;

    change.x *= DeltaTime;
    change.y *= DeltaTime;
    change.z *= DeltaTime;

    this->Position.x += change.x;
    this->Position.y += change.y;
    this->Position.z += change.z;

    this->ElapsedTime += DeltaTime;
    return (ElapsedTime < LifeLength);
}

glm::vec3 Particles::GetPosition() const
{
    return (this->Position);
}

GLfloat Particles::GetRotation() const
{
    return (this->Rotation);
}

GLfloat Particles::GetScale() const
{
    return (this->Scale);
}
