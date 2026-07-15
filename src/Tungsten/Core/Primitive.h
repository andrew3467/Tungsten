//
// Created by Andrew Graser on 7/7/2026.
//


#pragma once

#include "Mesh.h"

namespace Tungsten {
    class Primitive {
    public:
        static void Init();

    private:
        static void CreateQuad();
        static void CreateCube();


    public:
        static std::shared_ptr<Mesh> Quad() {return mQuadMesh;}
        static std::shared_ptr<Mesh> Cube() {return mCubeMesh;}

        static std::shared_ptr<Mesh> Sphere(int stacks, int sectors);


    private:
        static std::shared_ptr<Mesh> mQuadMesh;
        static std::shared_ptr<Mesh> mCubeMesh;
    };
}
