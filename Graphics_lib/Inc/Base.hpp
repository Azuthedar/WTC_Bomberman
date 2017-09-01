#pragma once

#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <istream>
#include <fstream>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Soil/SOIL2/SOIL2.h"


struct Image_data
{
	GLuint Texture_ID;
	unsigned int height;
	unsigned int width;
};
