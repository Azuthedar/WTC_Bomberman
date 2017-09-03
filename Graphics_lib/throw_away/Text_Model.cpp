#include "../Inc/Text_Model.hpp"

Text_Model::Text_Model()
{
    return ;
}

Text_Model::Text_Model( Model &tmp_model, Model_Text &tmp_texture )
{
    this->model = tmp_model;
    this->texture = tmp_texture;
}

Model Text_Model::GetModel() const
{
    return ( this->model );
}

Model_Text Text_Model::GetModelText() const
{
    return  ( this->texture );
}

Text_Model &Text_Model::operator=(Text_Model const &obj)
{
    this->model = obj.GetModel();
    this->texture = obj.GetModelText();

    return (*this);
}
