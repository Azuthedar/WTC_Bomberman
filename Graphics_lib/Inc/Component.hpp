#pragma once

#include "Base.hpp"
#include "Model.hpp"

class Component
{
    private:

        Model model;

        GLfloat Rotation_x;
        GLfloat Rotation_y;
        GLfloat Rotation_z;

        GLfloat Degres;

        GLfloat Scale;

        glm::vec3 position;

        std::string Name;

        Component();

    public:

        Component( const std::string &tmp_Name, Model const &tmp_model, GLfloat const &Degres, GLfloat const &rot_x, GLfloat const &rot_y, GLfloat const &rot_z, GLfloat const &tmp_scale, glm::vec3 const &tmp_pos );
        ~Component();

        void SetModel( Model const &tmp_model );
        void SetRotX( GLfloat const &rot_x );
        void SetRotY( GLfloat const &rot_y );
        void SetRotZ( GLfloat const &rot_z );
        void SetScale( GLfloat const &tmp_scale );
        void SetPosition( glm::vec3 const &tmp_position );
        void SetDegres( GLfloat const &tmp_degres);

        GLfloat GetDegres() const;
        Model GetModel( ) const;
        GLfloat GetRotX( ) const;
        GLfloat GetRotY( ) const;
        GLfloat GetRotZ( ) const;
        GLfloat GetScale( ) const;
        glm::vec3 GetPosition( );

        void inc_rotation( GLfloat const &tmp_x, GLfloat const &tmp_y, GLfloat const &tmp_z );
        void inc_position( GLfloat const &tmp_x, GLfloat const &tmp_y, GLfloat const &tmp_z );
        void dec_position( GLfloat const &tmp_x, GLfloat const &tmp_y, GLfloat const &tmp_z );
        void dec_rotation( GLfloat const &tmp_x, GLfloat const &tmp_y, GLfloat const &tmp_z );

};
