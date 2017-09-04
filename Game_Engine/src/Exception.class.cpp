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
