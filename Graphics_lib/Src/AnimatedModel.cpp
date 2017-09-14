#include "../Inc/AnimatedModel.hpp"

AnimatedModel::AnimatedModel( VAO const &tmp_model, Texture const &tmp_texture, bone const &tmp_rootbone, int const &tmp_bone_count )
{
    this->model = tmp_model;
    this->texture = tmp_texture;
    this->root_bone = tmp_rootbone;
    this->bone_count = tmp_bone_count;
    this->animator = new Animator( this );

    this->root_bone.calcInverseBindTransform( glm::vec4( 0.0f ) );
}

~AnimatedModel()
{
    return ;
}

VAO GetModel() const
{
    return (this->model);
}

Texture GetTexture() const
{
    return (this->texture);
}

bone GetRootbone() const
{
    return (this->root_bone);
}

int GetBoneCount() const
{
    return (this->bone_count);
}

void doAnimation( Animation tmp_animation )
{
    this->animator.doAnimation( tmp_animation );
}

void update()
{
    this->animator.update();
}

std::vector< glm::vec4 > getboneTransforms()
{
    
}

void addbonestoarray( bone headbone, std::vector< glm::vec4 > bonematrices )
{

}
