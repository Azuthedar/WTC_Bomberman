#include "../Inc/Camera.hpp"


void Camera::updateCameraVectors( )
{
    glm::vec3 front;
    front.x = cos( glm::radians( this->yaw )) * cos( glm::radians( this->pitch ));
    front.y = sin( glm::radians( this->pitch ));
    front.z = sin( glm::radians( this->yaw )) * cos( glm::radians( this->pitch ));

    this->front = glm::normalize( front );
    this->right = glm::normalize( glm::cross( this->front, this->worldUp ) );
    this->up = glm::normalize( glm::cross( this->right, this->front) );
}

Camera::Camera( glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch ) : front( glm::vec3( 0.0f, 0.0f, -1.0f ) ), mouseSensitivity( SENSITIVITY ), zoom( ZOOM )
{
    this->position = position;
    this->yaw = yaw;
    this->worldUp = up;
    this->pitch = pitch;
    this->updateCameraVectors();

}

Camera::Camera( GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : front( 0.0f, 0.0f, -1.0f), mouseSensitivity( SENSITIVITY ), zoom( ZOOM )
{
    this->position = glm::vec3( posX, posY, posZ);
    this->yaw = yaw;
    this->worldUp =  glm::vec3( upX, upY, upZ);;
    this->pitch = pitch;
    this->updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    return ( glm::lookAt( this->position, this->position + this->front, this->up ));
}

void Camera::ProcessKeyboard( glm::vec3 player_pos)
{
    player_pos.y = 15.0f;
    player_pos.z -= 20.0f;
    this->position = player_pos;

    this->pitch = -30.f;

    this->updateCameraVectors();
}

GLfloat Camera::GetZoom( )
{
    return ( this->zoom );
}
