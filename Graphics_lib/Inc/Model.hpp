#pragma once

#include "Base.hpp"
#include "Data_Loader.hpp"
#include "Mesh.hpp"
#include "Shaders.hpp"

class Model
{
    private:

        std::vector<Mesh> meshes;
        std::string directory;
        std::vector<Texture> textures_loaded;
        Data_Loader load;

    public:

        Model();
        Model( std::string const &path );

        std::vector < Mesh > GetMesh() const;
        std::vector < Texture > GetTexture() const;
        std::string GetDir() const;
        Model &operator=(Model const &obj);

        void Draw( Shaders shader );

        void loadModel( std::string path );
        void processNode( aiNode* node, const aiScene* scene );
        Mesh processMesh( aiMesh *mesh, const aiScene *scene );
        std::vector<Texture> loadMaterialTextures( aiMaterial *mat, aiTextureType type, string typeName );

};
