#pragma once

#include "Base.hpp"
#include "Model.hpp"

class Component
{
    private:

        Model *model;

        GLint direction;

        GLfloat Degres;

        GLfloat Scale;

        glm::vec3 position;

        std::string Name;

        int texture_index;

        glm::vec2 Offsets;

        Component();

    public:

        Component( const std::string &tmp_Name, Model *tmp_model, GLfloat const &Degres, GLint const &tmp_dir, GLfloat const &tmp_scale, glm::vec3 const &tmp_pos, int tmp_textureIndex );
        ~Component();

        Component(Component const &src);
        Component &operator=(Component const & rhs);

        void SetModel( Model *tmp_model );
        void SetDirection( GLint &tmp_dir);
        void SetScale( GLfloat const &tmp_scale );
        void SetPosition( glm::vec3 const &tmp_position );
        void SetDegres( GLfloat const &tmp_degres);
        void SetTextureIndex( int const &tmp_textureIndex );

        GLfloat GetDegres() const;
        Model *GetModel( ) const;
        GLint GetDirection() const;
        GLfloat GetScale( ) const;
        glm::vec3 GetPosition( );
        std::string GetName() const;
        int GetTextureIndex() const;
        glm::vec2 GetOffsets() const;

        void inc_position( GLfloat const &tmp_x, GLfloat const &tmp_y, GLfloat const &tmp_z );
        void dec_position( GLfloat const &tmp_x, GLfloat const &tmp_y, GLfloat const &tmp_z );

        void Calculate_Offset( int const &total_rows );


};
