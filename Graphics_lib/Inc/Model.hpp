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
        int Num_Rows = 1;

    public:

        Model();
        Model( std::string const &path, int const &tmp_numRows );

        std::vector < Mesh > GetMesh() const;
        std::vector < Texture > GetTexture() const;
        std::string GetDir() const;
        Model &operator=(Model const &obj);

        void Draw();

        void loadModel( std::string path );
        Skybox_s loadSkybox( std::vector<std::string> &texture_paths );
        Particles_s loadParticle( );
        void processNode( aiNode* node, const aiScene* scene );
        Mesh processMesh( aiMesh *mesh, const aiScene *scene );
        std::vector<Texture> loadMaterialTextures( aiMaterial *mat, aiTextureType type, string typeName );

        int GetNumRows() const;
        void SetNumRows( int const &tmp_numRows );
};
