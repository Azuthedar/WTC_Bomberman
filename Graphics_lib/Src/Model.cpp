#include "../Inc/Model.hpp"


Model::Model()
{
    return ;
}

Model::Model( std::string const &path )
{
    this->loadModel( path );
}

std::vector < Mesh > Model::GetMesh() const
{
    return (this->meshes);
}

std::vector < Texture > Model::GetTexture() const
{
    return (this->textures_loaded);
}

std::string Model::GetDir() const
{
    return (this->directory);
}

Model &Model::operator=(Model const &obj)
{
    this->meshes = obj.GetMesh();
    this->directory = obj.GetDir();
    this->textures_loaded = obj.GetTexture();

    return (*this);
}

void Model::Draw( Shaders shader )
{
    for ( GLuint i = 0; i < this->meshes.size( ); i++ )
    {
        this->meshes[i].Draw( shader );
    }
}

void Model::loadModel( std::string path )
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile( path, aiProcess_Triangulate | aiProcess_FlipUVs );

    //Replace With Exception Class Stoof
    if( !scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode )
    {
        cout << "ERROR::ASSIMP:: " << importer.GetErrorString( ) << endl;
        return;
    }

    this->directory = path.substr( 0, path.find_last_of( '/' ) );
    std::cout << this->directory << std::endl;

    this->processNode( scene->mRootNode, scene );
}

void Model::processNode( aiNode* node, const aiScene* scene )
{
    std::cout << "NUM of Meshes " << node->mNumMeshes << std::endl;
    for ( GLuint i = 0; i < node->mNumMeshes; i++ )
    {
        std::cout << "Enter" << std::endl;
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

        this->meshes.push_back( this->processMesh( mesh, scene ) );
    }

    std::cout << "Children Number " <<  node->mNumChildren << std::endl;
    for ( GLuint i = 0; i < node->mNumChildren; i++ )
    {
        this->processNode( node->mChildren[i], scene );
    }
}

Mesh Model::processMesh( aiMesh *mesh, const aiScene *scene )
{
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    for ( GLuint i = 0; i < mesh->mNumVertices; i++ )
    {
        Vertex vertex;
        glm::vec3 vector;

        if ( mesh->HasPositions() )
        {
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;
        }
        else
            exit(8);

        //std::cout << "vertices X " <<  vector.x << " Y " << vector.y << " Z " << vector.z << std::endl;

        if ( mesh->HasNormals() )
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }
        else
        {
            vertex.Normal = glm::vec3( 0.0f, 0.0f, 0.0f );
        }

        //std::cout << "Normals X " <<  vector.x << " Y " << vector.y << " Z " << vector.z << std::endl;

        if( mesh->mTextureCoords[0] ) // Does the mesh contain texture coordinates?
        {
            glm::vec2 vec;

            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
        {
            vertex.TexCoords = glm::vec2( 0.0f, 0.0f );
        }

        vertices.push_back( vertex );
    }

    for ( GLuint i = 0; i < mesh->mNumFaces; i++ )
    {
        aiFace face = mesh->mFaces[i];
        for ( GLuint j = 0; j < face.mNumIndices; j++ )
        {
            indices.push_back( face.mIndices[j] );
        }
    }

    std::cout << "Material " << mesh->mMaterialIndex << std::endl;
    if( mesh->mMaterialIndex >= 0 )
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<Texture> diffuseMaps = this->loadMaterialTextures( material, aiTextureType_DIFFUSE, "texture_diffuse" );
        textures.insert( textures.end( ), diffuseMaps.begin( ), diffuseMaps.end( ) );

        std::vector<Texture> specularMaps = this->loadMaterialTextures( material, aiTextureType_SPECULAR, "texture_specular" );
        textures.insert( textures.end( ), specularMaps.begin( ), specularMaps.end( ) );
    }

    return Mesh( vertices, indices, textures );
}

std::vector<Texture> Model::loadMaterialTextures( aiMaterial *mat, aiTextureType type, string typeName )
{
    std::vector<Texture> textures;

    for ( GLuint i = 0; i < mat->GetTextureCount( type ); i++ )
    {
        aiString str;
        mat->GetTexture( type, i, &str );

        std::cout <<  "Texture File Name " << str.C_Str() << std::endl;

        GLboolean skip = false;

        for ( GLuint j = 0; j < textures_loaded.size( ); j++ )
        {
            if( textures_loaded[j].path == str )
            {
                textures.push_back( textures_loaded[j] );
                skip = true;

                break;
            }
        }

        if( !skip )
        {   // If texture hasn't been loaded already, load it
            Texture texture;
            texture.id = this->load.load_texture( str.C_Str( ), this->directory );
            texture.type = typeName;
            texture.path = str;
            textures.push_back( texture );

            this->textures_loaded.push_back( texture );
        }
    }

    return textures;
}
