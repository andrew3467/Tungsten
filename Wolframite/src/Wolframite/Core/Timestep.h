//
// Created by Andrew Graser on 2/25/2024.
//

#ifndef TUNGSTEN_TIMESTEP_H
#define TUNGSTEN_TIMESTEP_H


namespace Tungsten {
    class Timestep {
    public:
        Timestep(float time = 0.0f)
            : mTime(time)
        {

        }

        operator float() const {return mTime;}

        float GetSeconds() const {return mTime;}
        float GetMilliseconds() const {return mTime * 1000.0f;}


    private:
        float mTime;
    };
}


#endif //TUNGSTEN_TIMESTEP_H
