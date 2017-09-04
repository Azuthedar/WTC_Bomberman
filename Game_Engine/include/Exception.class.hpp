#pragma once

#include "exception"

class Exceptions
{
	public:
		class EMapSizeInvalid : public std::exception
		{
			virtual const char * what() const throw();
		} EMapSize;
		class ENoMap : public std::exception
		{
			virtual const char * what() const throw();
		} ENoMap;
		class EMapInvalid : public std::exception
		{
			virtual const char * what() const throw();
		} EMapInvalid;

		class EInvalidFile : public std::exception
		{
			virtual const char * what() const throw();
		} EInvalidFile;
		class ENoFile : public std::exception
		{
			virtual const char * what() const throw();
		} ENoFile;
		class EEmptyFile : public std::exception
		{
			virtual const char * what() const throw();
		} EEmptyFile;

		class EInvalidPlayer : public std::exception
		{
			virtual const char * what() const throw();
		} EPlayer;
		class EInvalidGates : public std::exception
		{
			virtual const char * what() const throw();
		} EGates;

		void throwMapSizeInvalid();
		void throwNoMap();
		void throwMapInvalid();

		void throwInvalidFile();
		void throwNoFile();
		void throwEmptyFile();

		void throwInvalidPlayer();
		void throwInvalidGates();

};
