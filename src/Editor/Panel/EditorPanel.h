//
// Created by Andrew Graser on 11/24/2026.
//


#pragma once
#include <string>

namespace TungstenEditor
{
    class EditorPanel
    {
    public:
        virtual ~EditorPanel() = default;

        virtual void OnRender() const = 0;
        virtual std::string GetName() const = 0;
    };
}
