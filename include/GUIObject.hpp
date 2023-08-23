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
        if (!visible) return;
        PreRenderSetup();
        InnerRender();
        AfterRenderSetup();
    }

public:
    bool visible = true;

protected:
    virtual void InnerRender() = 0;
    virtual void PreRenderSetup() {}
    virtual void AfterRenderSetup() {}

};

}