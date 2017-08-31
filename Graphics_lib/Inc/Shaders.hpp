#pragma once

#include "Base.hpp"

class Shaders
{
    private:
        GLuint program_id;
        GLuint vertex_id;
        GLuint fragment_id;
        int num_attr;

        void compile(const std::string &file_path, GLuint &tmp_id);

    public:

        Shaders();
        ~Shaders();

        GLuint GetProgramID() const;

        void compile_shaders(const std::string &vertexfile_path, const std::string &fragmentfile_path);
        void link_shaders();
        GLint GetUniformLocation(const std::string& Uniform_name);
        void add_attributes(const std::string &attr_name);
        void use_prog();
        void unuse_prog();


        //Replaced By GLM lib
        void load_float( GLint location_id, GLfloat val );
        void load_vect( GLint location_id, glm::vec3 vect );
        void load_bool( GLint location_id, bool val );
        void load_matrix( GLint location_id, glm::mat4 &matrix );
};
