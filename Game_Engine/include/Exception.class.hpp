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

		class EInvalidSyntax : public std::exception
		{
			virtual const char * what() const throw();
		}EISyn;

		class EFileFailedDelete : public std::exception
		{
			virtual const char * what() const throw();
		}EFFDel;




		//Exceptions For Graphics Lib
		class EFailedLoadTextures : public std::exception
		{
			virtual const char * what() const throw();
		}EFLTex;

		class EFailedLoadCubemap : public std::exception
		{
			virtual const char * what() const throw();
		}EFLCube;

		class EFailedCreateIndices : public std::exception
		{
			virtual const char * what() const throw();
		}EFCIndices;

		class EFailedCreateVao : public std::exception
		{
			virtual const char * what() const throw();
		}EFCVao;

		class EFailedStoreObjectData : public std::exception
		{
			virtual const char * what() const throw();
		}EFSOData;

		class EFailedLoadModel : public std::exception
		{
			virtual const char * what() const throw();
		}EFLModel;

		class EMissingVertices : public std::exception
		{
			virtual const char * what() const throw();
		}EMVertices;

		class ECouldNotInitGLFW : public std::exception
		{
			virtual const char * what() const throw();
		}ECNIGLFW;

		class ECouldNotMakeGLFWWindow : public std::exception
		{
			virtual const char * what() const throw();
		}ECNCGWindow;

		class ECouldNotInitGlew : public std::exception
		{
			virtual const char * what() const throw();
		}ECNIGlew;

		class EFailedToCreateVertexShader : public std::exception
		{
			virtual const char * what() const throw();
		}EFTCVShader;

		class EFailedToCreateFragmentShader : public std::exception
		{
			virtual const char * what() const throw();
		}EFTCFShader;

		class EFailedToLoadShader : public std::exception
		{
			virtual const char * what() const throw();
		}EFTLShader;

		class EFailedToLinkShader : public std::exception
		{
			virtual const char * what() const throw();
		}EFTLinkShader;

		class EFailedToCompileShader : public std::exception
		{
			virtual const char * what() const throw();
		}EFTCShader;

		class EFailedToGetUniformID : public std::exception
		{
			virtual const char * what() const throw();
		}EFTGUID;

		

		void throwMapSizeInvalid();
		void throwNoMap();
		void throwMapInvalid();

		void throwInvalidFile();
		void throwNoFile();
		void throwEmptyFile();

		void throwInvalidPlayer();
		void throwInvalidGates();

		void throwInvalidSyntax();
		void throwFileFailedDelete();

		//Exceptions For Graphics Lib
		void throwLoadTextures();
		void throwLoadCubemap();
		void throwCreateIndices();
		void throwCreateVAO();
		void throwStoreObjectData();
		void throwLoadModel();
		void throwMissingVertices();
		void throwInitGLFW();
		void throwGLFWWindow();
		void throwInitGLEW();
		void throwVertexShader();
		void throwFragmentShader();
		void throwLoadShader();
		void throwLinkShader();
		void throwCompileShader();
		void throwGetUniformID();

};
