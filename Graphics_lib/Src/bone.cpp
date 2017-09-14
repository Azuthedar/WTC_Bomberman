#include "../Inc/bone.hpp"

bone::bone( int const &tmp_joint_ID, std::string const &tmp_joint_name, glm::mat4 const &tmp_bindlocaltransform )
{
    this->joint_ID = tmp_joint_ID;
    this->joint_Name = tmp_joint_name;
    this->localbindTransform = tmp_bindlocaltransform;
}

bone::~bone()
{
    return ;
}

void bone::addChild( bone const &child )
{
    this->child_nodes.push_back( &child )
}

glm::mat4 bone::GetAnimatedTransform() const
{
    return (this->animated_transform);
}

void bone::SetAnimationTransform( glm::mat4 const &tmp_animationtransform )
{
    this->animated_transform = tmp_animationtransform;
}

glm::mat4 bone::GetInverseBindTransform() const
{
    return (this->inversebindtransform);
}

void bone::CalculateInverseBindTransform( glm::mat4 tmp_parentbindtransform )
{
    glm::mat4 bindtransform = glm::matrixCompMult( tmp_parentbindtransform, this->localbindTransform );
    this->inversebindtransform = glm::inverse( bindtransform );

    for (int count = 0; count < this->child_nodes.size(); count++)
    {
        this->child_nodes.CalculateInverseBindTransform( bindtransform );
    }
}
