#pragma once

#include "Base.hpp"

class Particles
{
    private:

        glm::vec3 Position;
        glm::vec3 Velocity;
        GLfloat gravity;
        GLfloat LifeLength;
        GLfloat Rotation;
        GLfloat Scale;

        float ElapsedTime;

    public:

        Particles();
        Particles( glm::vec3 &tmp_Position, glm::vec3 &tmp_Velocity, GLfloat &tmp_gravity, GLfloat &tmp_LifeLength, GLfloat &tmp_Rotation, GLfloat &tmp_Scale );
        ~Particles();

        glm::vec3 GetPosition() const;
        GLfloat GetRotation() const;
        GLfloat GetScale() const;

        bool UpdateParticle( GLfloat &DeltaTime );

};
