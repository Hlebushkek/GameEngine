#pragma once

#include <imgui.h>
#include "Core.hpp"

namespace Engine
{

class GUIObject
{
public:
    virtual void Render()
    {
        if (!isVisible) return;
        this->PreRenderSetup();

        InnerRender();
    }

public:
    bool isVisible = true;

protected:
    virtual void InnerRender() = 0;
    virtual void PreRenderSetup() {}

};

}