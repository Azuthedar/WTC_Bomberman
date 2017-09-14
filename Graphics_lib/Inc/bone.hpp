#pragma once

#include "Base.hpp"

class bone
{
    private:

        int joint_ID;
        std::string joint_Name;
        std::vector< bone * > child_nodes;
        glm::mat4 animated_transform;
        glm::mat4 localbindTransform;
        glm::mat4 inversebindtransform;

    public:

        bone( int const &tmp_joint_ID, std::string const &tmp_joint_name, glm::mat4 const &tmp_bindlocaltransform );
        ~bone();

        void addChild( bone const &child );
        glm::mat4 GetAnimatedTransform() const;
        void SetAnimationTransform( glm::mat4 const &tmp_animationtransform );
        glm::mat4 GetInverseBindTransform() const;
        void CalculateInverseBindTransform( glm::mat4 tmp_parentbindtransform );
};
