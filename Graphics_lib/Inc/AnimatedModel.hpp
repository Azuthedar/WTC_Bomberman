#pragma once

#include "base.hpp"
#include "bone.hpp"

class AnimatedModel
{
    private:
        VAO model;
        Texture texture;

        bone root_bone;
        int bone_count;

        Animator *animator;

    public:

        AnimatedModel( VAO const &tmp_model, Texture const &tmp_texture, bone const &tmp_rootbone, int const &tmp_bone_count );
        ~AnimatedModel();

        VAO GetModel() const;
        Texture GetTexture() const;
        bone GetRootbone() const;
        int GetBoneCount() const;

        void doAnimation( Animation tmp_animation );
        void update();
        std::vector< glm::vec4 > getboneTransforms();
        void addbonestoarray( bone headbone, std::vector< glm::vec4 > bonematrices );
};
