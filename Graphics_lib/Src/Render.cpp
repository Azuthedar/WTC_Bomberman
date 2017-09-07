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

        //std::cout << "GFDGDGGDGD " << std::endl;

        glm::vec3 tmp_light_pos = glm::vec3(0.0f);
        if (count == 0)
        {
          tmp_light_pos = tmp[count]->GetPosition();
          tmp_light_pos.y = 5.0f;
        }

        shader.load_float( this->shineLoc, 0.5f);
        shader.load_float( this->reflectionLoc, 0.5f);

        shader.load_matrix( this->projLoc, this->projection );
        shader.load_matrix( this->viewLoc, this->view_matrix );


        shader.load_vect( this->lightLoc, tmp_light_pos );
        shader.load_vect( this->colourLoc, this->light->GetColour() );

        glm::mat4 model = glm::mat4(1.0);
        glm::mat4 model_matrix;

        model = glm::translate( model, tmp[count]->GetPosition() );

        //if (tmp[count]->GetName().compare(""))
          model = glm::rotate( model, (GLfloat)glfwGetTime() * tmp[count]->GetDegres(), glm::vec3( 0.5f, 1.0f, 0.0f ) );
        //else if ()
        //  model = glm::rotate( model, tmp[count]->GetDegres(), glm::vec3( 0.5f, 1.0f, 0.0f ) );
        //else
        //  model = glm::rotate( model, (GLfloat)glfwGetTime() * tmp[count]->GetDegres(), glm::vec3( 0.5f, 1.0f, 0.0f ) );

        model_matrix = glm::scale( model , glm::vec3(tmp[count]->GetScale()) );

        //model_matrix = model * rot;
        shader.load_matrix( this->modelLoc, model_matrix );
        //shader.load_matrix( this->ScaleLoc, scel );

        ip.Draw( shader );

        /*glBindVertexArray( ip.GetModel().GetVAO() );

        glEnableVertexAttribArray( 0 );
        glEnableVertexAttribArray( 1 );
        glEnableVertexAttribArray( 2 );

        //glActiveTexture( GL_TEXTURE0 );

        //std::cout << ip.GetModelText().GetTextureID() << std::endl;
        glBindTexture(GL_TEXTURE_2D, ip.GetModelText().GetTextureID());
        glUniform1i( glGetUniformLocation( shader.GetProgramID(), "Texture_"), 0.0f );

        //std::cout << "GFDGDGGDGD 3" <<  ip.GetModel().GetVertexCount() << std::endl;

        glDrawElements( GL_TRIANGLES, ip.GetModel().GetVertexCount(), GL_UNSIGNED_INT, 0);

        //std::cout << "GFDGDGGDGD 4" << std::endl;

        glDisableVertexAttribArray( 0 );
        glDisableVertexAttribArray( 1 );
        glEnableVertexAttribArray( 2 );

        glBindVertexArray( 0 );*/
    }

    for ( unsigned int count = 0; count < tmp.size(); count++)
    {
        delete tmp[count];
    }

    tmp.clear();
}
