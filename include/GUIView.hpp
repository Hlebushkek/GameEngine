#pragma once

#include <vector>
#include <string>
#include "GUIObject.hpp"

namespace Engine
{

class ENGINE_API GUIView : public GUIObject
{
public:
    GUIView(std::string title, ImVec2 size, bool border = true, bool visible = true)
        : GUIObject(), m_title(title), m_size(size), m_border(border), m_visible(visible) {}

    virtual void Render() override;

    void AddSubObject(GUIObject* object) { m_subviews.push_back(object);}

protected:
    std::string m_title;
    ImVec2 m_size;
    bool m_border;
    bool m_visible;

    std::vector<GUIObject*> m_subviews;

};

}