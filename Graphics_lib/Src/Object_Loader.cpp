#include "../Inc/Object_Loader.hpp"


std::string Object_Loader::trim( std::string line )
{
    std::string tmp;
    int is_front = 1;

    for (unsigned int count = 0; count < line.length(); count++)
    {
        if (line[count] != ' ')
            is_front = 0;
        else if (is_front)
            continue ;

        if (line[count] == ' ' && line[count + 1] == ' ' && is_front == 0)
            continue ;
        else
            tmp = tmp + line[count];
    }

    if (tmp[tmp.size() - 1] == ' ')
        tmp.pop_back();

    return (tmp);
}

void Object_Loader::fill_data( std::vector < std::string > &data, const std::string &line)
{
    std::string line_tmp = "";
    int pos = 0;

    size_t tmp = line.find(" ");

    if ( tmp > line.length() )
        return ;

    line_tmp += line.substr( tmp + 1);
    //std::cout << line_tmp << std::endl;

    while (line_tmp.length())
    {
        tmp = line_tmp.find(" ");

        if (tmp > line_tmp.length())
        {
            data.push_back(line_tmp);
            break ;
        }

        data.push_back( line_tmp.substr( pos, tmp + 1) );
        line_tmp = line_tmp.substr( tmp + 1);
    }
}

void Object_Loader::seperate_face_data( std::vector < std::string > &data, const std::string &line)
{
    std::string line_tmp = "";
    std::string place_holder = "";
    int val = 0;

    size_t tmp = line.find(" ");

    if ( tmp > line.length() )
        return ;

    line_tmp += line.substr( tmp + 1);

    while(!line_tmp.empty())
    {
        val = atoi(line_tmp.c_str());

        if (val != 0 && strncmp(line_tmp.c_str(), " ", 1) != 0)
        {
            place_holder = std::to_string(val);
            data.push_back(place_holder);
            line_tmp.erase(0, place_holder.length() );
            val = 0;
        }
        else
            line_tmp.erase(line_tmp.begin());
    }
}

Model *Object_Loader::Load_Object( const std::string &obj_path )
{
    std::ifstream file(obj_path);

    if (file.fail())
	{
		std::cerr << "Error Help" << std::endl;
        exit (8);
        //return NULL ;
	}

	//Debug
	std::string line = "";
    std::vector < std::string > gen;
    std::vector < std::string > faces;

    std::vector < glm::vec3 > vertices;
    std::vector < glm::vec2 > texture_coordinates;
    std::vector < glm::vec3 > normals;
    std::vector < int > indices;

    GLfloat *Vertices_Array = NULL;
    GLfloat *Normals_Array = NULL;
    GLfloat *Texture_Array = NULL;
    GLuint *Indicies_Array = NULL;

	while (getline(file, line))
	{
        line = trim( line );
        fill_data( gen, line);

        if (strncmp(line.c_str(), "v ", 2) == 0)
            vertices.push_back( glm::vec3( stof(gen[0]), stof(gen[1]), stof(gen[2]) ) );
        else if (strncmp(line.c_str(), "vt ", 3) == 0)
            texture_coordinates.push_back( glm::vec2( stof(gen[0]), stof(gen[1]) ) );
        else if (strncmp(line.c_str(), "vn ", 3) == 0)
            normals.push_back( glm::vec3( stof(gen[0]), stof(gen[1]), stof(gen[2]) ) );
        else if (strncmp(line.c_str(), "f ", 2) == 0)
            faces.push_back( line );
        gen.clear();
	}

    if (texture_coordinates.size() > 0 && Texture_Array == NULL)
        Texture_Array = new GLfloat[vertices.size() * 2];
    if (normals.size() > 0 && Normals_Array == NULL)
        Normals_Array = new GLfloat[vertices.size() * 3];

    file.close();

    //for (unsigned int tmp = 0; tmp < vertices.size(); tmp++)
    //{
    //    std::cout << " X " << vertices[tmp].x << " Y " << vertices[tmp].y << " Z " << vertices[tmp].z << std::endl;
    //}

    /*for (unsigned int tmp = 0; tmp < texture_coordinates.size(); tmp++)
    {
        std::cout << " X " << texture_coordinates[tmp].x << " Y " << texture_coordinates[tmp].y << std::endl;
    }

    for (unsigned int tmp = 0; tmp < normals.size(); tmp++)
    {
        std::cout << " X " << normals[tmp].x << " Y " << normals[tmp].y << " Z " << normals[tmp].z << std::endl;
    }*/

    int vertex_point = 0;
    for (unsigned int val = 0; val < faces.size(); val++)
    {
        line = trim(faces[val]);
        seperate_face_data( gen, line);

        for (int count = 0; count < gen.size();)
        {
            vertex_point = stoi(gen[count]) - 1;
            //std::cout << "V " << stoi(gen[count]) << std::endl;
            indices.push_back( vertex_point );

            if (texture_coordinates.size() > 0)
            {
                glm::vec2 tex = texture_coordinates[ stoi(gen[++count]) - 1];
                Texture_Array[ vertex_point * 2] = tex.x;
                Texture_Array[ vertex_point * 2 + 1] = 1 - tex.y;
            }

            if (normals.size() > 0)
            {
                glm::vec3 norms = normals[ stoi(gen[++count]) - 1 ];
                //std::cout << "N " << stoi(gen[count]) << std::endl;
                Normals_Array[ vertex_point * 3 ] = norms.x;
                Normals_Array[ vertex_point * 3 + 1 ] = norms.y;
                Normals_Array[ vertex_point * 3 + 2 ] = norms.z;
            }

            count++;
        }

        gen.clear();
    }


    Vertices_Array = new GLfloat[vertices.size() * 3];
    Indicies_Array = new GLuint[indices.size()];

    //std::cout << "VEEEEEEERRRRRRTTTTT " << indices.size() << std::endl;

    vertex_point = 0;
    for (unsigned int tmp = 0; tmp < vertices.size(); tmp++)
    {
        Vertices_Array[vertex_point++] = vertices[tmp].x;
        Vertices_Array[vertex_point++] = vertices[tmp].y;
        Vertices_Array[vertex_point++] = vertices[tmp].z;
    }

    for (unsigned int tmp = 0; tmp < indices.size(); tmp++)
    {
        Indicies_Array[tmp] = indices[tmp];
    }

    return ( this->loader.Load_VAO( Vertices_Array, ((vertices.size() * 3) * sizeof(GLfloat)), indices.size() , Indicies_Array, (indices.size() * sizeof(GLuint)) , Texture_Array, ( (texture_coordinates.size() * 2 ) * sizeof(GLfloat) ), Normals_Array, (normals.size() * 3) * sizeof(GLfloat) ));
}
