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
        Texture texture;

        glm::vec2 Current_Offset;
        glm::vec2 Next_Offset;
        GLfloat Blend_Val;

        float ElapsedTime;

    public:

        Particles();
        Particles( Texture const &tmp_texture, glm::vec3 const &tmp_Position, glm::vec3 const &tmp_Velocity, GLfloat const &tmp_gravity, GLfloat const &tmp_LifeLength, GLfloat const &tmp_Rotation, GLfloat const &tmp_Scale );
        ~Particles();

        Particles(Particles const &src);
        Particles &operator=(Particles const &rhs);

        glm::vec3 GetPosition() const;
        GLfloat GetRotation() const;
        GLfloat GetScale() const;
        glm::vec2 GetCurrentOffset() const;
        glm::vec2 GetNextOffset() const;
        GLfloat GetBlendValue() const;
        int GetNumRows() const;

        void UpdateOffsetInfo();

        bool UpdateParticle( const GLfloat &DeltaTime );
        void Calculate_Offset( int const &index_one, int const &index_two );
};
