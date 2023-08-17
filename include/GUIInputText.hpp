#pragma once

#include <string>
#include "GUIObject.hpp"

namespace Engine
{

class ENGINE_API GUIInputText : public GUIObject
{
public:
    GUIInputText(std::string title, size_t bufSize, ImGuiInputTextFlags inputTextFlags = 0)
        : GUIObject(), m_title(title), m_inputTextFlags(inputTextFlags)
    {
        m_buffer.resize(bufSize);
    }

    void SetTitle(std::string title) { m_title = title; }
    const std::string& GetTitle() const { return m_title; }

    void SetText(std::string text) { m_buffer = text; }
    const std::string& GetText() const { return m_buffer; }

    size_t GetBufferSize() { return m_buffer.size(); }

    void InnerRender() override;

public:
    bool hideInput = false;
    bool readOnly = false;

protected:
    std::string m_title;
    std::string m_buffer;
    ImGuiInputTextFlags m_inputTextFlags;

};

}