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
        GLuint texture_id;

        float ElapsedTime;

    public:

        Particles();
        Particles( GLuint const &tmp_texture_id, glm::vec3 const &tmp_Position, glm::vec3 const &tmp_Velocity, GLfloat const &tmp_gravity, GLfloat const &tmp_LifeLength, GLfloat const &tmp_Rotation, GLfloat const &tmp_Scale );
        ~Particles();

        glm::vec3 GetPosition() const;
        GLfloat GetRotation() const;
        GLfloat GetScale() const;
        GLuint GetTextureID() const;

        bool UpdateParticle( const GLfloat &DeltaTime );

};
