#include "../include/Exception.class.hpp"

/* MAPS */
const char * Exceptions::EMapSizeInvalid::what() const throw()
{
    return ("Given map size is invalid.");
}

const char * Exceptions::ENoMap::what() const throw()
{
    return ("No map found.");
}

const char * Exceptions::EMapInvalid::what() const throw()
{
    return ("Invalid map format");
}

/* FILES */
const char * Exceptions::EInvalidFile::what() const throw()
{
    return ("Given file is invalid.");
}

const char * Exceptions::ENoFile::what() const throw()
{
    return ("File does not exist.");
}

const char * Exceptions::EEmptyFile::what() const throw()
{
    return ("Given file is empty.");
}

/* GAME ENTITIES */
const char * Exceptions::EInvalidPlayer::what() const throw()
{
    return ("Invalid amount of players on map.");
}

const char * Exceptions::EInvalidGates::what() const throw()
{
    return ("Invalid amount of gates on map.");
}

const char * Exceptions::EInvalidSyntax::what() const throw()
{
    return ("Invalid Syntax used");
}

const char * Exceptions::EFileFailedDelete::what() const throw()
{
    return ("Could not Delete file");
}


//Graphics Exceptions!

const char * Exceptions::EFailedLoadTextures::what() const throw()
{
    return ("Failed To Load Textures");
}

const char * Exceptions::EFailedLoadCubemap::what() const throw()
{
    return ("Failed To Load Cubemap");
}

const char * Exceptions::EFailedCreateIndices::what() const throw()
{
    return ("Failed To Create Indices");
}

const char * Exceptions::EFailedCreateVAO::what() const throw()
{
    return ("Failed To Create VAO");
}

const char * Exceptions::EFailedCreateVBO::what() const throw()
{
    return ("Failed To Create VBO");
}

const char * Exceptions::EFailedStoreObjectData::what() const throw()
{
    return ("Failed To Store Object Data");
}

const char * Exceptions::EFailedLoadModel::what() const throw()
{
    return ("Failed To Load Model");
}

const char * Exceptions::EMissingVertices::what() const throw()
{
    return ("Missing Verices");
}

const char * Exceptions::ECouldNotInitGLFW::what() const throw()
{
    return ("Failed To Init GLFW");
}

const char * Exceptions::ECouldNotMakeGLFWWindow::what() const throw()
{
    return ("Failed To Make GLFW Window");
}

const char * Exceptions::ECouldNotInitGlew::what() const throw()
{
    return ("Failed To Init GLEW");
}

const char * Exceptions::EFailedToCreateVertexShader::what() const throw()
{
    return ("Failed To Create Vertex Shader");
}

const char * Exceptions::EFailedToCreateFragmentShader::what() const throw()
{
    return ("Failed To Create Fragment Shader");
}

const char * Exceptions::EFailedToLoadShader::what() const throw()
{
    return ("Failed To Load Shader");
}

const char * Exceptions::EFailedToLinkShader::what() const throw()
{
    return ("Failed To Link Shader");
}

const char * Exceptions::EFailedToCompileShader::what() const throw()
{
    return ("Failed To Compile Shader");
}

const char * Exceptions::EFailedToGetUniformID::what() const throw()
{
    return ("Failed To Get Uniform ID");
}

const char * Exceptions::EFailedToLoadWAV::what() const throw()
{
    return ("Failed to load WAV files");
}


//Throwers
void Exceptions::throwMapSizeInvalid()
{
    throw EMapSize;
}

void Exceptions::throwNoMap()
{
    throw ENoMap;
}

void Exceptions::throwMapInvalid()
{
    throw EMapInvalid;
}

void Exceptions::throwInvalidFile()
{
    throw EInvalidFile;
}

void Exceptions::throwNoFile()
{
   throw ENoFile;
}

void Exceptions::throwEmptyFile()
{
    throw EEmptyFile;
}

void Exceptions::throwInvalidPlayer()
{
    throw EPlayer;
}

void Exceptions::throwInvalidGates()
{
    throw EGates;
}

void Exceptions::throwInvalidSyntax()
{
    throw EISyn;
}

void Exceptions::throwFileFailedDelete()
{
    throw EFFDel;
}

//Graphics Lib Throwers
void Exceptions::throwLoadTextures()
{
    throw EFLTex;
}

void Exceptions::throwLoadCubemap()
{
    throw EFLCube;
}

void Exceptions::throwCreateIndices()
{
    throw EFCIndices;
}

void Exceptions::throwCreateVAO()
{
    throw EFCVao;
}

void Exceptions::throwCreateVBO()
{
    throw EFCVbo;
}

void Exceptions::throwStoreObjectData()
{
    throw EFSOData;
}

void Exceptions::throwLoadModel()
{
    throw EFLModel;
}

void Exceptions::throwMissingVertices()
{
    throw EMVertices;
}

void Exceptions::throwInitGLFW()
{
    throw ECNIGLFW;
}

void Exceptions::throwGLFWWindow()
{
    throw ECNCGWindow;
}

void Exceptions::throwInitGLEW()
{
    throw ECNIGlew;
}

void Exceptions::throwVertexShader()
{
    throw EFTCVShader;
}

void Exceptions::throwFragmentShader()
{
    throw EFTCFShader;
}

void Exceptions::throwLoadShader()
{
    throw EFTLShader;
}

void Exceptions::throwLinkShader()
{
    throw EFTLinkShader;
}

void Exceptions::throwCompileShader()
{
    throw EFTCShader;
}

void Exceptions::throwGetUniformID()
{
    throw EFTGUID;
}

void Exceptions::throwLoadWAV()
{
    throw EFTLWav;
}
