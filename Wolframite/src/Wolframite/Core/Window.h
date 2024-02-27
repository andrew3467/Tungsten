//
// Created by Andrew Graser on 2/26/2024.
//

#ifndef SANDBOX_WINDOW_H
#define SANDBOX_WINDOW_H


#include "Wolframite/Events/Event.h"

#include <string>
#include <cstdint>

namespace Tungsten {
    struct WindowProps {
        uint32_t Width, Height;
        const char* Title;

        WindowProps(unsigned int w, unsigned int h, const char* t)
                : Width(w), Height(h), Title(t){

        }

        WindowProps()
                : Width(1280), Height(720), Title("Tungsten Engine") {

        }
    };

    class Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() = default;

        virtual void OnUpdate() = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual void SetEventCallback(const EventCallbackFn &callback) = 0;

        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;


        static Window* Create(const WindowProps& props = WindowProps());

    private:
        WindowProps mProps;
    };
}


#endif //SANDBOX_WINDOW_H
