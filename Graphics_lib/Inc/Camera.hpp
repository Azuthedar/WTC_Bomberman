#pragma once

#include "Base.hpp"

enum Camera_movement
{
    FORWAR = 0, BACKWAR, LEF, RIGH
};

const GLfloat YAW = 90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 6.0f;
const GLfloat SENSITIVITY = 0.15f;
const GLfloat ZOOM = 45.0f;

class Camera
{
    private:

        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldUp;

        GLfloat yaw;
        GLfloat pitch;

        GLfloat zoom;

        void updateCameraVectors( );

    public:

        Camera( glm::vec3 position = glm::vec3( 0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3( 0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH );
        Camera( GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);

        Camera(Camera const &src);
        Camera &operator=(Camera const &rhs);

        glm::mat4 GetViewMatrix();
        void ProcessKeyboard( glm::vec3 player_pos);

        const glm::vec3 &getPosition() const;

        const glm::vec3 &getFront() const;

        const glm::vec3 &getUp() const;

        const glm::vec3 &getRight() const;

        const glm::vec3 &getWorldUp() const;

        GLfloat getYaw() const;

        GLfloat getPitch() const;

        GLfloat GetZoom() const;
};
