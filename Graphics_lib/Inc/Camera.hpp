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

        GLfloat mouseSensitivity;
        GLfloat zoom;

        void updateCameraVectors( );

    public:

        Camera( glm::vec3 position = glm::vec3( 0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3( 0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH );
        Camera( GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);


        glm::mat4 GetViewMatrix();
        //void ProcessKeyboard( Camera_movement direction, GLfloat deltaTime );
        void ProcessKeyboard( glm::vec3 player_pos);
        void ProcessMouseMovement( GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true );
        void ProcessMouseScroll( GLfloat yOffset );
        GLfloat GetZoom( );
};
