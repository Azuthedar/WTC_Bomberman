#include "../Inc/Particles.hpp"

Particles::Particles()
{
    return ;
}

Particles::Particles(  Texture const &tmp_texture, glm::vec3 const &tmp_Position, glm::vec3 const &tmp_Velocity, GLfloat const &tmp_gravity, GLfloat const &tmp_LifeLength, GLfloat const &tmp_Rotation, GLfloat const &tmp_Scale  )
{
    this->Position = tmp_Position;
    this->Velocity = tmp_Velocity;
    this->gravity = tmp_gravity;
    this->LifeLength = tmp_LifeLength;
    this->Rotation = tmp_Rotation;
    this->Scale = tmp_Scale;
    this->ElapsedTime = 0.0f;
    this->texture = tmp_texture;
}

Particles::~Particles()
{
    return ;
}

bool Particles::UpdateParticle( const GLfloat &DeltaTime )
{
    Velocity.y += -50 * this->gravity * DeltaTime;
    glm::vec3 change = this->Velocity;

    change.x *= DeltaTime;
    change.y *= DeltaTime;
    change.z *= DeltaTime;

    this->Position.x += change.x;
    this->Position.y += change.y;
    this->Position.z += change.z;

    UpdateOffsetInfo();

    this->ElapsedTime += DeltaTime;
    return (ElapsedTime < LifeLength);
}

void Particles::UpdateOffsetInfo()
{
    float life_val = this->ElapsedTime / this->LifeLength;
    int stagecount = this->texture.num_rows * this->texture.num_columns;
    float atlas_prog = life_val * stagecount;

    int index1 = static_cast<int>( floor(atlas_prog) );
    int index2 = (index1 < stagecount - 1) ? index1 + 1 : index1;

    this->Blend_Val = fmod(atlas_prog, 1);

    Calculate_Offset( index1, index2 );
}

void Particles::Calculate_Offset( int const &index_one, int const &index_two )
{
    int column = 0;
    int row = 0;

    column = index_one % this->texture.num_rows;
    this->Current_Offset.x = static_cast<float>(column) / static_cast<float>(this->texture.num_rows);
    row = index_one / this->texture.num_rows;
    this->Current_Offset.y = static_cast<float>(row) / static_cast<float>(this->texture.num_rows);

    column = 0;
    row = 0;

    column = index_two % this->texture.num_rows;
    this->Next_Offset.x = static_cast<float>(column) / static_cast<float>(this->texture.num_rows);
    row = index_two / this->texture.num_rows;
    this->Next_Offset.y = static_cast<float>(row) / static_cast<float>(this->texture.num_rows);
}

int Particles::GetNumRows() const
{
    return (this->texture.num_rows);
}

glm::vec2 Particles::GetCurrentOffset() const
{
    return (this->Current_Offset);
}

glm::vec2 Particles::GetNextOffset() const
{
    return (this->Next_Offset);
}

GLfloat Particles::GetBlendValue() const
{
    return (this->Blend_Val);
}

glm::vec3 Particles::GetPosition() const
{
    return (this->Position);
}

GLfloat Particles::GetRotation() const
{
    return (this->Rotation);
}

GLfloat Particles::GetScale() const
{
    return (this->Scale);
}
