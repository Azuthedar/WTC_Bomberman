#include "../Inc/Render.hpp"

Render::Render()
{
    return ;
}

Render::~Render()
{
    return ;
}

void Render::Prep()
{
    glClearColor( 0.3f, 0.6f, 0.8f, 1.0f);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void Render::Load_Uniform( Shaders &shader )
{
    this->modelLoc = shader.GetUniformLocation( "model" );
    this->projLoc = shader.GetUniformLocation( "projection" );
    this->viewLoc = shader.GetUniformLocation( "view" );
    this->lightLoc = shader.GetUniformLocation( "light_pos" );
    this->colourLoc = shader.GetUniformLocation( "light_colour" );
    this->shineLoc = shader.GetUniformLocation( "shine_damper" );
    this->reflectionLoc = shader.GetUniformLocation( "reflection" );
    //this->ScaleLoc = shader.GetUniformLocation( "scale" );
}

void Render::SetProjection( GLfloat const &tmp_zoom )
{
    this->projection = glm::perspective( tmp_zoom, 1280.0f / 720.0f, 1.0f, 10000.0f);
}

void Render::SetViewMatrix( glm::mat4 const &tmp_matrix )
{
    this->view_matrix = tmp_matrix;
}

void Render::Render_( std::vector < Component * > &tmp, Shaders &shader )
{
    Model ip;

    for ( unsigned int count = 0; count < tmp.size(); count++)
    {
        ip = tmp[count]->GetModel();

        shader.load_float( this->shineLoc, 0.5f);
        shader.load_float( this->reflectionLoc, 0.5f);

        shader.load_matrix( this->projLoc, this->projection );
        shader.load_matrix( this->viewLoc, this->view_matrix );

        shader.load_vect( this->lightLoc, tmp[0]->GetPosition() );
        shader.load_vect( this->colourLoc, this->light->GetColour() );

        glm::mat4 model = glm::mat4(1.0);
        glm::mat4 model_matrix;

        model = glm::translate( model, tmp[count]->GetPosition() );
        model = glm::rotate( model, (GLfloat)glfwGetTime() * tmp[count]->GetDegres(), glm::vec3( 0.5f, 1.0f, 0.0f ) );
        model_matrix = glm::scale( model , glm::vec3(tmp[count]->GetScale()) );
        //std::cout << "GFDGDGGDGD 2" << ip.GetModel().GetVAO() << std::endl;

        //model_matrix = model * rot;
        shader.load_matrix( this->modelLoc, model_matrix );
        //shader.load_matrix( this->ScaleLoc, scel );

        ip.Draw( shader );
    }

    for ( unsigned int count = 0; count < tmp.size(); count++)
    {
        delete tmp[count];
    }

    tmp.clear();
}
