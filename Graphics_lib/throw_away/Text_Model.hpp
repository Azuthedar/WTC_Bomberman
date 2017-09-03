#pragma once

#include "Base.hpp"
#include "Model.hpp"
#include "Model_Text.hpp"

class Text_Model
{
    private:
        Model model;
        Model_Text texture;

    public:

        Text_Model();
        Text_Model( Model &tmp_model, Model_Text &tmp_texture );

        Model GetModel() const;
        Model_Text GetModelText() const;

        Text_Model &operator=(Text_Model const &obj);
};
