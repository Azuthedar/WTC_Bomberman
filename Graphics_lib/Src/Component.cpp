#include "../Inc/Component.hpp"

Component::Component()
{
    return ;
}

Component::~Component()
{
    return ;
}

void Component::SetDegres( GLfloat const &tmp_degres)
{
    this->Degres = tmp_degres;
}

GLfloat Component::GetDegres() const
{
    return (this->Degres);
}

Component::Component( const std::string &tmp_Name, Model *tmp_model, GLfloat const &Degres, GLint const &tmp_dir, GLfloat const &tmp_scale, glm::vec3 const &tmp_pos, int tmp_textureIndex )
{
    this->model = tmp_model;
    this->Scale = tmp_scale;
    this->direction = tmp_dir;
    this->position = tmp_pos;
    this->Degres = Degres;
    this->Name = tmp_Name;
    this->texture_index = tmp_textureIndex;

    Calculate_Offset( tmp_model->GetNumRows() );
}

glm::vec2 Component::GetOffsets() const
{
    return (this->Offsets);
}

std::string Component::GetName() const
{
  return (this->Name);
}

void Component::Calculate_Offset( int const &total_rows )
{
    int column = 0;
    int row = 0;

    column = this->texture_index % total_rows;
    this->Offsets.x = static_cast<float>(column) / static_cast<float>(total_rows);

    row = this->texture_index / total_rows;
    this->Offsets.y = static_cast<float>(row) / static_cast<float>(total_rows);


}

void Component::inc_position( GLfloat const &tmp_x, GLfloat const &tmp_y, GLfloat const &tmp_z )
{
    this->position.x += tmp_x;
    this->position.y += tmp_y;
    this->position.z += tmp_z;
}

void Component::dec_position( GLfloat const &tmp_x, GLfloat const &tmp_y, GLfloat const &tmp_z )
{
    this->position.x -= tmp_x;
    this->position.y -= tmp_y;
    this->position.z -= tmp_z;
}

void Component::SetModel( Model *tmp_model )
{
    this->model = tmp_model;
}


void Component::SetTextureIndex( int const &tmp_textureIndex )
{
    this->texture_index = tmp_textureIndex;
}

void Component::SetDirection( GLint &tmp_dir)
{
    this->direction = tmp_dir;
}

void Component::SetScale( GLfloat const &tmp_scale )
{
    this->Scale = tmp_scale;
}

void Component::SetPosition( glm::vec3 const &tmp_position )
{
    this->position = tmp_position;
}

Model *Component::GetModel( ) const
{
    return (this->model);
}

int Component::GetTextureIndex() const
{
    return (this->texture_index);
}

GLint Component::GetDirection() const
{
    return (this->direction);
}

GLfloat Component::GetScale( ) const
{
    return (this->Scale);
}

glm::vec3 Component::GetPosition( )
{
    return (this->position);
}

Component::Component(Component const &src) {
    *this = src;
    return;
}

Component &Component::operator=(Component const &rhs) {
    this->model = rhs.GetModel();
    this->direction = rhs.GetDirection();
    this->Degres = rhs.GetDegres();
    this->Scale = rhs.GetScale();
    this->Name = rhs.GetName();
    this->texture_index = rhs.GetTextureIndex();
    this->Offsets = rhs.GetOffsets();

    return *this;
}
