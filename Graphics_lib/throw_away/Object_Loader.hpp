#pragma once

#include "Base.hpp"
#include "Model.hpp"
#include "Data_Loader.hpp"

class Object_Loader
{
    private:
        Data_Loader loader;

    public:

        void fill_data( std::vector < std::string > &data, const std::string &line);
        void seperate_face_data( std::vector < std::string > &data, const std::string &line);
        std::string trim( std::string line );
        Model *Load_Object( const std::string &obj_path );
};
