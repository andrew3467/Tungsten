//
// Created by Andrew Graser on 8/28/2024.
//

#ifndef OPENGL_ENGINE_TIME_H
#define OPENGL_ENGINE_TIME_H


namespace Tungsten {
    class Time {
    public:
        static void Init();

        static void Update();


        static const float GetTime() {return mTime;}


    private:
        static float mTime;
        static float mLastFrame;
    };

    class ScopedTimer {
    public:
        ScopedTimer(const std::string& name) : mName(name), mStart(std::chrono::high_resolution_clock::now()) {

        }

        ~ScopedTimer() {
            auto end = std::chrono::high_resolution_clock::now();
            auto timeMS = std::chrono::duration<double, std::milli>(end - mStart) * 1000;

            TUNGSTEN_INFO("{0}: {1} ms", mName, timeMS.count());

        }

    private:
        std::string mName;
        std::chrono::high_resolution_clock::time_point mStart;
    };
}

#endif //OPENGL_ENGINE_TIME_H
